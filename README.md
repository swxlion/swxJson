# swxJson

A easy to use &amp; convenient JSON library for C++11.

**Caution: Only support UTF-8**.

[简体中文](README.zh-cn.md)


## 0. The Goal of Birth

At first, nobody want to reinvent the wheel. We know the [RapidJson](https://github.com/miloyip/rapidjson/) has the best performances, so we adopt RapidJson in our projects. But after some codings, we feeling it **readlly** inconvenient. So, the swxJson is created.

**Any operation, only one line of code!!!**

* **Prase**, only one line of code;
* **Stringify**, only one line of code;
* **Get & set value of any node**, only one line of code;
* **Pack any structure consist of STL containers**, only one line of code.

Finally, the goal of swxJson are **convenience** and **ease of use**, not performance. About performance, please refer to the section "3. Performance". If you need high performance, please use RapidJson.


## 1. Basic usage

* The following examples are assumed the statement <br>**`using namespace swxJson;`**<br>has declared.

### 1.1. Parse

```
JsonPtr json = Json::parse(const char* json);
```

"json" is an object holding the DOM.

### 1.2. Stringify

Assume `JsonPtr jsonNode` is an available object of swxJson:

```
std::string jsonString = jsonNode->str();
```

Or print to screen:

```
std::cout<<jsonNode<<std::endl;
```

Or

```
std::cout<<(*jsonNode)<<std::endl;
```

### 1.3. Get value of any node

Assume the following JSON structure:

```
{
	"status": {
		"server": {
			"base": {
				"startTimeStr":"2017-07-31 07:34:45",
				"listenIP":"",
				"listenPort":12345,
				"httpSupported":true
			}
		},
		"client": {
			"base": {
				"questTimeout":5
			}
		}
	},
	"threads": {
		"workThreads": {
			"min":4,
			"max":4,
			"busyCount":1
		},
		"ioThreads": {
			"min":4,
			"max":4,
			"busyCount":0
		}
	}
}
```

Assume we want to fetch the value of the node "status/server/base/startTimeStr":

```
std::string startTime = (std::string)jsonNode["status.server.base.startTimeStr"];
```

Or


```
std::string startTime = (std::string)jsonNode["status/server/base/startTimeStr"];
```

Or


```
std::string startTime = (std::string)jsonNode["status"]["server"]["base"]["startTimeStr"];
```

The operations for other values' type are similar:

```
bool httpSupported = jsonNode["status.server.base.httpSupported"];
```

```
int workBusyCount = jsonNode["threads.workThreads.busyCount"];
```


### 1.4. Pack data

#### 1.4.1. Pack structure consist of STL containers

Assume the following composite structure:

```
std::map<std::string, std::list<std::vector<std::map<std::string, std::set<int>>>>> demo;

std::set<int> setA{1, 2, 3}, setB{4, 5, 6}, setC{7, 8, 9};
std::map<std::string, std::set<int>> m1, m2, m3;
m1["a"] = setA;
m1["b"] = setB;
m2["c"] = setC;
m3["d"] = setA;
m3["e"] = setB;
m3["f"] = setC;

std::vector<std::map<std::string, std::set<int>>> v1{m1, m2, m3}, v2{m2, m3};
demo["No1"].push_back(v1);
demo["No1"].push_back(v2);
demo["No2"].push_back(v2);
demo["No2"].push_back(v2); //-- second push
demo["No2"].push_back(v1);
```

Packing:

```
Json json;
json = demo;
```

Output:

```
cout<<json<<endl;
```

Result: (Formated. swxJson whitout the format feature.)

```
{
	"No1":[
		[
			{
				"a":[1, 2, 3],
				"b":[4, 5, 6]
			},
			{
				"c":[7, 8, 9]
			},
			{
				"d":[1, 2, 3],
				"e":[4, 5, 6],
				"f":[7, 8, 9]
			}
		],
		[
			{
				"c":[7, 8, 9]
			},
			{
				"d":[1, 2, 3], 
				"e":[4, 5, 6], 
				"f":[7, 8, 9]
			}
		]
	], 
	"No2":[
		[
			{
				"c":[7, 8, 9]
			},
			{
				"d":[1, 2, 3],
				"e":[4, 5, 6],
				"f":[7, 8, 9]
			}
		], 
		[
			{
				"c":[7, 8, 9]
			},
			{
				"d":[1, 2, 3],
				"e":[4, 5, 6],
				"f":[7, 8, 9]
			}
		],
		[
			{
				"a":[1, 2, 3],
				"b":[4, 5, 6]
			},
			{
				"c":[7, 8, 9]
			}, 
			{
				"d":[1, 2, 3], 
				"e":[4, 5, 6], 
				"f":[7, 8, 9]
			}
		]
	]
}
```


#### 1.4.2. Pack multiple structures in once

Assume the following instances of STL containers:

```
vector<bool> boolvec{true, false, true};
vector<int> intvec{23, 232, 33, 34};
vector<double> doublevec{23.3, 23e2, 3e3, .34};
vector<string> stringvec{"wewe", "dsd", "efs", "dd"};
map<string, bool> boolmap{{"bool1", false}, {"bool2", true}, {"bool3",     false}};
map<string, int> intmap{{"int1", 232}, {"int2", 121}, {"int3", 2323}};
map<string, double> doublemap{{"double1", 23.2}, {"double2", 12e1}, {"double3", 2.32e3}};
map<string, string> stringmap{{"string1", "dwed"}, {"string2", "ddsd"}, {"string3", "dwee"}};
auto tupleDemo = std::make_tuple(10,"a", "sdsd", 232, .34);
deque<int> dequeDemo{23, 23,43};
list<int> listDemo{2563, 2783,483};
set<int> setDemo{223, 2322, 323, 324};
unordered_set<int> usetDemo{2123, 23212, 3213, 3114};
unordered_map<string, int> umapDemo{{"uint1", 232}, {"uint2", 121}, {"uint3", 2323}};
```

##### 1.4.2.1. Pack all structures into current array node in once:

```
Json json;
json.fill(12, 32., 34e5, "sas", intvec, "sas", listDemo, stringmap, tupleDemo, dequeDemo, setDemo, usetDemo, umapDemo);
```

Output:

```
cout<<json<<endl;
```

Result: (Formated. swxJson whitout the format feature.)

```
[
    12,
    32,
    3400000,
    "sas",
    [
        23,
        232,
        33,
        34
    ],
    "sas",
    [
        2563,
        2783,
        483
    ],
    {
        "string1":"dwed",
        "string2":"ddsd",
        "string3":"dwee"
    },
    [
        10,
        "a",
        "sdsd",
        232,
        0.34
    ],
    [
        23,
        23,
        43
    ],
    [
        223,
        323,
        324,
        2322
    ],
    [
        3114,
        23212,
        3213,
        2123
    ],
    {
        "uint1":232,
        "uint2":121,
        "uint3":2323
    }
]
```

##### 1.4.2.1. Pack all structures into an array node  at the designated path ("aaa.bbb."):

```
Json json;
json.fillTo("aaa.bbb.", 12, 32., 34e5, "sas", intvec, "sas", listDemo, stringmap, tupleDemo, dequeDemo, setDemo, usetDemo, umapDemo);
```

Output:

```
cout<<json<<endl;
```

Result: (Formated. swxJson whitout the format feature.)


```
{
    "aaa":{
        "bbb":{
            "":[
                12,
                32,
                3400000,
                "sas",
                [
                    23,
                    232,
                    33,
                    34
                ],
                "sas",
                [
                    2563,
                    2783,
                    483
                ],
                {
                    "string1":"dwed",
                    "string2":"ddsd",
                    "string3":"dwee"
                },
                [
                    10,
                    "a",
                    "sdsd",
                    232,
                    0.34
                ],
                [
                    23,
                    23,
                    43
                ],
                [
                    223,
                    323,
                    324,
                    2322
                ],
                [
                    3114,
                    23212,
                    3213,
                    2123
                ],
                {
                    "uint1":232,
                    "uint2":121,
                    "uint3":2323
                }
            ]
        }
    }
}
```


#### 1.4.3. Pack basic types & structures

```
Json json;
json = true;
```

```
Json json;
json = 234.56;
```

```
Json json;
json = std::string("abc");
```

```
std::map<std::string, std::list<std::vector<std::map<std::string, std::set<int>>>>> demo;

... //-- Fill the demo object.

Json json;
json = demo;
```

```
Json json;
json.push(1);
json.push(false);
json.push("abc");
json.push(std::vector{1, 2, 3});
```

```
Json json;
json.add("aaa.bbb", 12);
json.add("aaa.zzz", "abc");
json.add("aaa.ccc", true);
```

Please see the section "2. Detail of swxJson" for more details.<br>More examples: <br>[swxJsonFunctionalTest.cpp](/tests/swxJsonFunctionalTest.cpp)<br>[swxJsonAdvancedTest.cpp](/tests/swxJsonAdvancedTest.cpp)


## 2. Detail of swxJson

### 2.1. Packing data

swxJson has 5 series packing APIs, and two independent functions: `fill()` & `fillTo()`.

For following API functions:

* **If the function without the 'path' parameter, the current node will be operated.**
* **If the function with the 'path' parameter, the node pointed by the path will be operated.**
* If the nodes in path are not exist, swxJson will automatically create the lost nodes.
* If the type of any existed intermediate node is NOT Object/Dict, functions will throw an exception.
* For the functions with 'path' parameter, the 'delim' parameter decides which characters are used as path separators. The default is '.' And '/', which are used as the path separators at the same time.


1. **Assign operations**

	The series operations overloaded the assignment operator "=" for basic types and most STL containers (except for stack, forward_list, queue. Because data members contained in those containers can not be visited without changing the original object).
	
	The assign operations will **ignore** and **reset** the current node's type.
	
	These operations will not throw any exception.
	
	Interfaces & APIs:<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 

2. **set functions**

	Completely equivalent to assignment operations.
	
	The set functions will **ignore** and **reset** the current node's type.
	
	These functions will not throw any exception.
	
	Interfaces & APIs:<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


3. **add functions**

	The add functions add data to Object/Dict node as a new child node. If the added object is an Object/Dict, the added object **WILL NOT** be merged with the operared node. If want them merged, please using the merge functions.
	
	If type of the operated node is not Object/Dict, these functions will throw an exception.
	
	Interfaces & APIs:<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


4. **push functions**
	
	The push functions push data to array node as a new child node. If the pushed object is an Array, the added array **WILL NOT** be merged with the operared node. If want them merged, please using the merge functions.
	
	If type of the operated node is not Array, these functions will throw an exception.

	Interfaces & APIs:<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


5. **merge functions**

	If the merged object and the operated node have the same type which is one of Object/Dict/Array, the merge functions will merge the object's data to the operated node. If want added or pushed the object to the operated node, please using add or push functions.
	
	If types of the merged object and the operated node dismatch, or is not one of Object/Dict/Array, these functions will throw an exception.

	Interfaces & APIs:<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


6. **fill function**

	Similar with the push functions. Push multiple different data with different types into current array node as children nodes at one time.

	Interfaces & APIs:<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


7. **fillTo function**

	Similar with the push functions. Push multiple different data with different types into the 'path' parameter pointed array node as children nodes at one time.

	Interfaces & APIs:<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


### 2.2. Fetch data

1. **[ ] operator**

	The parameter can be index of array or node name for object/dict or path for [] operator.
	
	The obtained node can be cast to the basic types or std::string type by implicit conversion or explicit conversion.

	Interfaces & APIs:<br>[swxJson.h](/src/swxJson.h)


2. **get function**

	If the target operated node does not exist, or if the type does not match, the get functions will return the default parameter (dft parameter). Otherwise the data of opreated node will be returned.

	The get functions will not throw any exception. The corresponding functions with the path parameter also will not throw any exception.
	
	**NOTE**:
	Because all the parameters of getString function are string type, so the compiler will confound the getString function without the path parameter and the overloaded version with path patameter when using default parameters. So, the version of getString function with the path parameter is renamed **getStringAt**, not the same as the getString function.
	
	Interfaces & APIs:<br>[swxJson.h](/src/swxJson.h)
	
3. **want functions**

	If the operated node does not exist, or if the type does not match, the want functions will throw an exception. Otherwise the data of opreated node will be returned.

	Interfaces & APIs:<br>[swxJson.h](/src/swxJson.h)

### 2.3. Notes

* **Path**

	* swxJson uses "." and "/" as path separators at the same time by default.
		It means that "aaa.bbb.ccc", "aaa/bbb/ccc", "aaa/bbb.ccc" have the same meaning and behavior.

	* The special path consisting of pure separators
		swxJson supports a special path consisting of pure path separators. <br>Please refer to "3. Differences from ECMA-404 & RFC-7159", section "Object's key" for more detail.

* **Null & nullptr**

	* swxJson can recognize nullptr, which is equivalent to empty string.
	* Because the NULL is defined as a macro, so when used with swxJson, may need to be explicitly converted to the target type. Otherwise, there may be unpredictable behavior.

* **Index of array**

	For an index of an array node, when the previous nodes' values are not specified:
	* All the previous nodes are created with Json::JSON_Uninit type when the indexed node operated.
	* For stringify, all Json::JSON_Uninit type nodes are treated as the null type nodes.


## 3. Differences from ECMA-404 & RFC-7159

* **Range of characterset**

	Currently, this version **only** supports utf-8, and **DO NOT** support **BOM**.
	
* **Whitespace**

	ECMA-404 & RFC7159 provide four whitespaces: U+0009、U+000A、U+000D、U+0020.
	
	Since swxJson using isspace() function, swxJson support 6 whitespaces. Added the vertical tab \v U+000B & form feed \f U+000C base on ECMA-404 & RFC-7159.


* **Numbers**

	1. ECMA-404 & RFC-7159 do not allow the leading zeros, but in order to facilitate the convenience, swxJson allows the extra 0;
	2. ECM-404 & RFC-7159 do not permit NaN and Infinity, but in order to facilitate the convenience, swxJson allows NaN and Infinity (inf) as numeric value without case sensitive.

* **Key of object**

	* ECMA-404 does not specify whether an object key is unique, and RFC 7159 requires it as an unique key. swxJson follows the order of RFC 7159.
	* ECMA-404 & RFC 7159 do not specify whether the key can be empty. For the path of swxJson, assuming the '.' as path separator, the following paths in an object mean:

		1. "": the node which name is empty. e.g. {"":Target, ...}
		2. ".": the node with empty name in a sub-node which name is empty. e.g. {"":{"":Target, ...}, ...}
		3. "..": the node with empty name in a sub-node which name is empty, and the name of the super-node of the sub-node is empty. e.g. {"":{"":{"":Target, ...}, ...}, ...}
		4. "...": the node with empty name in a sub-node which name is empty, and the name of the super-node of the sub-node is empty. And the name of the super-node of the first super-node is empty. e.g. {"":{"":{"":{"":Target, ...}, ...}, ...}, ...}
		
* **Escape characters & control characters**

	In the actual business of industries, JSON plays the role of data exchanging format, which can be transmitted between different languages ​​and business modules. For engineering convenience, swxJson decides that "any valid characters are treated equally" and does not make any changes to the original strings. So:
	
	* swxJson can recognize the escape characters, but not escaped them, just keeping them as original;
	* Do not require the control of characters escaped.


## 4. Performances

**Reaffirm:**

swxJson is designed for **convenience** and **easy to use**, not consider the performance.

Following comparing data generated by project [nativejson-benchmark](https://github.com/miloyip/nativejson-benchmark).

Codes for performance testing can be refered at: [swxjsontest.cpp](/performances/nativejson-benchmark/swxjsontest.cpp)

### 4.1. Performance comparing

#### 4.1.1. Prase

* **Prase Time**

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ@2.50GHz_mac64_clang8.1_1. Parse_Time (ms).png)

* **Prase Memory**

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ@2.50GHz_mac64_clang8.1_1. Parse_Memory (byte).png)

* **Prase Memory Peak**

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ@2.50GHz_mac64_clang8.1_1. Parse_MemoryPeak (byte).png)

* **Prase Alloc Count**

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ@2.50GHz_mac64_clang8.1_1. Parse_AllocCount.png)

#### 4.1.2. Stringify

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ@2.50GHz_mac64_clang8.1_2. Stringify_Time (ms).png)


#### 4.1.3. Statistics

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ@2.50GHz_mac64_clang8.1_4. Statistics_Time (ms).png)


### 4.2. Conformance

The results of failed cases for conformance: <br>
[conformance_swxJson (C++).md](/performances/nativejson-benchmark/results/conformance_swxJson (C++).md)

Analysis:

* Parse Validation

	Consider the compatibility and codes complexity, swxJson is compatible with the recoverable inaccurate json format.
	* Array missing the "]"
	* Object missing the "}"
	* Extra commas in the tail
	* Leading zeros for number fields

	Therefore, swxJson will fail with relevant cases in conformance testing.


	For engineering convenience, swxJson decides that "any valid characters are treated equally" and does not make any changes to the original strings. So:
	
	* swxJson can recognize the escape characters, but not escaped them, just keeping them as original;
	* Do not require the control of characters escaped.

	So, swxJson will fail with relevant cases in conformance testing.
	

* Parse Double

	swxJson currently uses **double** type rather than long double to store the floating data. Use strtod() to convert data from string.
	
	For some ​​testing cases, such as 2.22507e-308, strtod() & atof() both return a failure with errno 34: Math result not representable (numerical result out of range).

	So, swxJson will fail for these cases that the strtod() or atoi() function can not convert the numerical value.
	
	BTW, because most of procedures using strtod() or atoi() to convert the float data, so swxJson currently does not consider implement IEEE 754/854 standard for self.

	In addition, for these failed cases:
	
	| float | expect (Standard Answer) | actual (swxJson output) |
	|-------|-----------------|----------------|
	| 1e-214748363 | 0 (0x0160) | 0 (0x0160) |
	| 1e-214748364 | 0 (0x0160) | 0 (0x0160) |
	
	I think it must be a joke! :)

* Parse String

	For engineering convenience, swxJson decides that "any valid characters are treated equally" and does not make any changes to the original strings. So:
	
	* swxJson can recognize the escape characters, but not escaped them, just keeping them as original;
	* Do not require the control of characters escaped.

	So, swxJson will fail with relevant cases.

* Roundtrip

	For the following cases:
	
	| Standard Answer | swxJson output |
	|-----------------|----------------|
	| [0,1] | [0, 1] |
	| {"a":null,"foo":"bar"} | {"a":null, "foo":"bar"} |
	
	Issue with output format. swxJson will not be modified to meet the testing cases.
	
	For the following cases:
	
	| Standard Answer | swxJson output |
	|-----------------|----------------|
	| 0.0 | 0 |
	| -0.0 | -0 |
	
	Since the serialization is using the C++ std::ostream object, swxJson considers improving in the future in the right way. JSON does not treat **integer** and **float** in different way, so it does not affect the use and correctness.
	
	
	For the following cases:
	
	| Standard Answer | swxJson output |
	|-----------------|----------------|
	| 2.2250738585072014e-308 | 2.22507e-308 |
	| 1.7976931348623157e308 | 1.79769e+308 |
	
	Precision issue. Consider improving in the future in the right way.


## 5. Future

* Change the double type to long type for float data. <br> This requirement maybe not urgent.

* Improve performance and efficiency. <br> There is a plan ready, but it will lead to a sharp increase in code length. The total length of src is 2942 lines currently, I don't hope it increasing more.

Plan:<br>Currently busy in other projects, maybe improve them in future.