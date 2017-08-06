# Conformance of swxJson (C++)

## 1. Parse Validation

* `../data/jsonchecker/fail02.json` is invalid but was mistakenly deemed valid.
~~~js
["Unclosed array"
~~~

* `../data/jsonchecker/fail04.json` is invalid but was mistakenly deemed valid.
~~~js
["extra comma",]
~~~

* `../data/jsonchecker/fail09.json` is invalid but was mistakenly deemed valid.
~~~js
{"Extra comma": true,}
~~~

* `../data/jsonchecker/fail13.json` is invalid but was mistakenly deemed valid.
~~~js
{"Numbers cannot have leading zeroes": 013}
~~~

* `../data/jsonchecker/fail15.json` is invalid but was mistakenly deemed valid.
~~~js
["Illegal backslash escape: \x15"]
~~~

* `../data/jsonchecker/fail17.json` is invalid but was mistakenly deemed valid.
~~~js
["Illegal backslash escape: \017"]
~~~

* `../data/jsonchecker/fail25.json` is invalid but was mistakenly deemed valid.
~~~js
["	tab	character	in	string	"]
~~~

* `../data/jsonchecker/fail26.json` is invalid but was mistakenly deemed valid.
~~~js
["tab\   character\   in\  string\  "]
~~~

* `../data/jsonchecker/fail27.json` is invalid but was mistakenly deemed valid.
~~~js
["line
break"]
~~~

* `../data/jsonchecker/fail28.json` is invalid but was mistakenly deemed valid.
~~~js
["line\
break"]
~~~

* `../data/jsonchecker/fail32.json` is invalid but was mistakenly deemed valid.
~~~js
{"Comma instead if closing brace": true,
~~~


Summary: 23 of 34 are correct.

## 2. Parse Double

* `[2.22507e-308]`
  * expect: `2.2250699999999998e-308 (0x016FFFFE2E8159D0)`
  * actual: `0 (0x0160)`

* `[-2.22507e-308]`
  * expect: `-2.2250699999999998e-308 (0x016800FFFFE2E8159D0)`
  * actual: `0 (0x0160)`

* `[4.9406564584124654e-324]`
  * expect: `4.9406564584124654e-324 (0x0161)`
  * actual: `0 (0x0160)`

* `[2.2250738585072009e-308]`
  * expect: `2.2250738585072009e-308 (0x016FFFFFFFFFFFFF)`
  * actual: `0 (0x0160)`

* `[1e-10000]`
  * expect: `0 (0x0160)`
  * actual: `0 (0x0160)`

* `[18446744073709551616]`
  * expect: `1.8446744073709552e+19 (0x01643F0000000000000)`
  * actual: `0 (0x0160)`

* `[-9223372036854775809]`
  * expect: `-9.2233720368547758e+18 (0x016C3E0000000000000)`
  * actual: `0 (0x0160)`

* `[2.2250738585072011e-308]`
  * expect: `2.2250738585072009e-308 (0x016FFFFFFFFFFFFF)`
  * actual: `0 (0x0160)`

* `[1e-214748363]`
  * expect: `0 (0x0160)`
  * actual: `0 (0x0160)`

* `[1e-214748364]`
  * expect: `0 (0x0160)`
  * actual: `0 (0x0160)`

* `[2.22507385850720113605740979670913197593481954635164564e-308]`
  * expect: `2.2250738585072009e-308 (0x016FFFFFFFFFFFFF)`
  * actual: `0 (0x0160)`

* `[10141204801825834086073718800384]`
  * expect: `1.0141204801825834e+31 (0x016465FFFFFFFFFFFFF)`
  * actual: `0 (0x0160)`

* `[10141204801825835211973625643008]`
  * expect: `1.0141204801825835e+31 (0x0164660000000000000)`
  * actual: `0 (0x0160)`

* `[10141204801825834649023672221696]`
  * expect: `1.0141204801825835e+31 (0x0164660000000000000)`
  * actual: `0 (0x0160)`

* `[5708990770823838890407843763683279797179383808]`
  * expect: `5.7089907708238389e+45 (0x016496FFFFFFFFFFFFF)`
  * actual: `0 (0x0160)`

* `[5708990770823839524233143877797980545530986496]`
  * expect: `5.7089907708238395e+45 (0x0164970000000000000)`
  * actual: `0 (0x0160)`

* `[5708990770823839207320493820740630171355185152]`
  * expect: `5.7089907708238395e+45 (0x0164970000000000000)`
  * actual: `0 (0x0160)`

* `[100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000]`
  * expect: `1e+308 (0x0167FE1CCF385EBC8A0)`
  * actual: `0 (0x0160)`


Summary: 48 of 66 are correct.

## 3. Parse String

* `["Hello\nWorld"]`
  * expect: `"Hello
World"` (length: 11)
  * actual: `"Hello\nWorld"` (length: 12)

* `["Hello\u0000World"]`
  * expect: `"Hello\0World"` (length: 11)
  * actual: `"Hello\u0000World"` (length: 16)

* `["\"\\/\b\f\n\r\t"]`
  * expect: `""\/
	"` (length: 8)
  * actual: `"\"\\/\b\f\n\r\t"` (length: 15)

* `["\u0024"]`
  * expect: `"$"` (length: 1)
  * actual: `"\u0024"` (length: 6)

* `["\u00A2"]`
  * expect: `"¢"` (length: 2)
  * actual: `"\u00A2"` (length: 6)

* `["\u20AC"]`
  * expect: `"€"` (length: 3)
  * actual: `"\u20AC"` (length: 6)

* `["\uD834\uDD1E"]`
  * expect: `"𝄞"` (length: 4)
  * actual: `"\uD834\uDD1E"` (length: 12)


Summary: 2 of 9 are correct.

## 4. Roundtrip

* Fail:
~~~js
[0,1]
~~~

~~~js
[0, 1]
~~~

* Fail:
~~~js
{"a":null,"foo":"bar"}
~~~

~~~js
{"a":null, "foo":"bar"}
~~~

* Fail:
~~~js
[0.0]
~~~

~~~js
[0]
~~~

* Fail:
~~~js
[-0.0]
~~~

~~~js
[-0]
~~~

* Fail:
~~~js
[2.2250738585072014e-308]
~~~

~~~js
[2.22507e-308]
~~~

* Fail:
~~~js
[1.7976931348623157e308]
~~~

~~~js
[1.79769e+308]
~~~


Summary: 19 of 25 are correct.

