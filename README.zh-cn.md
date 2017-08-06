# swxJson

方便易用的 C++11 JSON 库。

注意：**仅支持 UTF-8**

[English Version](README.md)


## 0. 诞生目标

最开始也没想重复再造轮子。[RapidJson](https://github.com/miloyip/rapidjson/) 的各项性能指标皆有口碑，于是一开始在项目中就采用了 RapidJson。但使用下来，感觉 **真的 真的** 很不方便。于是便诞生了 swxJson。

**任何操作，只需一行代码！！！**

* **解析**，只需一行代码；
* **序列化**，只需一行代码；
* **获取 & 修改 确定成员的值**，只需一行代码；
* **打包任意 STL 容器的组合结构**，只需一行代码。

最后，swxJson 的目标是 **便利性** 和 **易用性**，不是性能。性能请参见 “3. 性能” 章节。如果对性能有较高要求，请使用 RapidJson。


## 1. 简单使用

* 以下示例均假设已经使用<br>**`using namespace swxJson;`**

### 1.1. 解析

```
JsonPtr json = Json::parse(const char* json);
```
即可生成一个包含 DOM 结构的内存对象。

### 1.2. 序列化

假设 `JsonPtr jsonNode` 是一个有效的 swxJson 对象，序列化可采用以下方式：

```
std::string jsonString = jsonNode->str();
```

或者直接输出

```
std::cout<<jsonNode<<std::endl;
```

或者

```
std::cout<<(*jsonNode)<<std::endl;
```

### 1.3. 获取确定成员的值

假设有如下 Json 结构：

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

要获取 status/server/base/startTimeStr 的值，可采用：

```
std::string startTime = (std::string)jsonNode["status.server.base.startTimeStr"];
```

或者


```
std::string startTime = (std::string)jsonNode["status/server/base/startTimeStr"];
```

或者


```
std::string startTime = (std::string)jsonNode["status"]["server"]["base"]["startTimeStr"];
```

其他数据类型操作类似

```
bool httpSupported = jsonNode["status.server.base.httpSupported"];
```

```
int workBusyCount = jsonNode["threads.workThreads.busyCount"];
```


### 1.4. 打包数据

#### 1.4.1. 打包 STL 容器的组合结构

假设有如下组合结构

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

打包过程

```
Json json;
json = demo;
```

输出

```
cout<<json<<endl;
```

结果 (格式化之后，swxJson 不带格式化功能)

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


#### 1.4.2. 一次打包多个结构

假设有如下 STL 实例对象：

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

##### 1.4.2.1. 作为一个数组，打包到根目录下：

```
Json json;
json.fill(12, 32., 34e5, "sas", intvec, "sas", listDemo, stringmap, tupleDemo, dequeDemo, setDemo, usetDemo, umapDemo);
```

输出

```
cout<<json<<endl;
```

结果 (格式化之后，swxJson 不带格式化功能)

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

##### 1.4.2.1. 作为一个数组，打包到指定目录（“aaa.bbb.”）下：

```
Json json;
json.fillTo("aaa.bbb.", 12, 32., 34e5, "sas", intvec, "sas", listDemo, stringmap, tupleDemo, dequeDemo, setDemo, usetDemo, umapDemo);
```

输出

```
cout<<json<<endl;
```

结果 (格式化之后，swxJson 不带格式化功能)


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


#### 1.4.3. 打包基础结构

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

... //-- 填充 demo 对象

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

更多细节请参见 “2. swxJson 细节” 部分。<br>更多示例请参见: <br>[swxJsonFunctionalTest.cpp](/tests/swxJsonFunctionalTest.cpp)<br>[swxJsonAdvancedTest.cpp](/tests/swxJsonAdvancedTest.cpp)


## 2. swxJson 的细节

### 2.1. 打包数据

swxJson 的数据打包 API 一共有5个系列的函数，外加两个 fill() 和 fillTo() 函数。

以下函数中：

* **不含 path 参数的函数，对当前节点进行操作；**
* **含有 path 参数的函数，对以当前节点作为起始节点，path 作为路径，指向的子节点进行操作；**
* 如果 path 指定的路径中，中间路径不存在，swxJson 会自动创建中间节点；
* 如果 path 指定的路径中，中间路径存在，且不为 Object／Dict 类型，则函数会抛出异常；
* 含有 path 参数的函数中，delim 参数决定了使用那些字符为路径分隔符。默认为“.”与“/”同时作为路径分隔符使用。

为了方便，下文中，将当前节点，或者 path 指向的节点，统称为“**目标节点**”。


1. **赋值操作**

	该系列操作重载了赋值运算符“=”，适用于基本类型和大部分STL容器(stack 等除外，因为无法在不改变原始对象的情况下获取容器对象所包含的数据成员)。

	该系列操作将**忽略**并**重置**当前节点类型。

	该系列函数不会抛出异常。
	
	具体接口请参见：<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 

2. **set 系列函数**

	与赋值系列操作完全等价。
	
	该系列操作将**忽略**并**重置**当前节点类型。
	
	该系列函数不会抛出异常。
	
	具体接口请参见：<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


3. **add 系列函数**

	add 系列函数用于向 Object／Dict 中添加成员。
	
	add 操作中，如果被添加的对象是 Object／Dict，则被添加的对象会作为子节点，添加到目标节点中，不会和目标节点合并。如果需要与目标节点合并，请使用 merge 系列函数。
	
	如果目标节点不是 Object／Dict 类型，则会抛出异常。
	
	具体接口请参见：<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


4. **push 系列函数**

	push 系列函数用于向 Array 节点中添加成员。
	
	push 操作中，如果被添加的对象是 Array 类型，则被添加的对象会作为子节点，添加到目标节点中，不会和目标节点合并。如果需要与目标节点合并，请使用 merge 系列函数。
	
	如果目标节点不是 Array 类型，则会抛出异常。

	具体接口请参见：<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


5. **merge 系列函数**

	如果 merge 的对象是 Array／Object／Dict 类型，且与目标节点类型相同，则会与目标节点合并。如果希望作为目标节点的子节点添加，请使用 add 或者 push 系列函数。
	
	如果目标及诶单和对象类型节点不匹配，或者不是 Array／Object／Dict 类型，将会抛出异常。

	具体接口请参见：<br>[swxJson.h](/src/swxJson.h)<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


6. **fill 函数**

	类似于 push 系列函数。目标节点为当前节点，一次添加众多不同类型的成员节点。

	具体接口请参见：<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


7. **fillTo 函数**

	类似于 push 系列函数。目标节点为 path 参数指向的节点，一次添加众多不同类型的成员节点。

	具体接口请参见：<br>[swxJson.Enhancement.inc.h](/src/swxJson.Enhancement.inc.h) 


### 2.2. 获取数据

1. **[ ] 方法**

	[] 内为数组的下标，或者节点名称或者节点路径。
	
	获取到的节点，可通过隐式转换或显示强制转换，转换到基本类型，或者 std::string 类型。

	具体接口请参见：<br>[swxJson.h](/src/swxJson.h)


2. **get 系列函数**

	如果目标节点不存在，或者类型不匹配，get 系列函数将返回输入的默认参数(dft参数)，否则将返回对应类型的节点数据。
	
	该系列函数不抛出异常。带 path 参数的版本也不抛出异常。
	
	**注意**：
	因为 getString 的参数全是 string 类型，因此在含有默认参数的情况下，编译器会将非 path 版本和 path 版本混淆。因此 getString 的 path 版本为 **getStringAt**，而不是同名重载的 getString。

	具体接口请参见：<br>[swxJson.h](/src/swxJson.h)
	
3. **want 系列函数**

	如果目标节点不存在，或者类型不匹配，want 系列函数抛出异常，否则将返回对应类型的节点数据。

	具体接口请参见：<br>[swxJson.h](/src/swxJson.h)

### 2.3. 注意事项

* **路径**

	* path 默认同时使用 “.” 及 “/” 作为路径分隔符。
		即："aaa.bbb.ccc"、"aaa/bbb/ccc"、"aaa/bbb.ccc" 有相同的含义和行为。
		
	* 由纯分隔符组成的特殊路径
		<br>swxJson 支持由纯路径分隔符组成的特殊路径。<br>
		具体请参考 “3. 与 ECMA-404 & RFC7159 标准之间的差异” 中，“Object 的 key” 部分。

* **Null 与 nullptr 值**

	* swxJson 可以识别 nullptr，nullptr 值等价于空字符串。
	* 因为 NULL 是以宏的形式进行定义，所以与 swxJson 中使用时，需要显式进行强制类型转换，不然可能会有不可预料的行为。

* **数组下标**

	对于数组类型，如果只指定了某个下标节点的值，而之前的值没有被指定的话：
	* 对于查询而言，该下标节点的前续节点均已被创建，存在，type() 查询返回 Json::JSON_Uninit；
	* 对于输出、序列化而言，如果没有被赋值，均被序列化为 null 类型节点。

## 3. 与 ECMA-404 & RFC 7159 标准之间的差异

* **字符集范围**

	本版本暂时只支持 utf-8，且**不支持 BOM**。
	
* **Whitespace**

	ECMA-404 & RFC7159 指定的 whitespace 只有4个：U+0009、U+000A、U+000D、U+0020
	
	swxJson 因使用 isspace() 函数，whitespace 目前有6个。在 ECMA-404 & RFC7159 的基础上，增加 垂直制表符 \v U+000B 和 换页符 \f U+000C。


* **数字**

	1. ECMA-404 & RFC 7159 不允许数字前有多余的0；swxJson为了便于使用，允许有多余的0；
	2. ECMA-404 & RFC 7159 不允许 NaN 和 Infinity 出现；swxJson 为了工程需要，允许 NaN 和 Infinity(inf) 作为数字字段出现，且忽略大小写。

* **Object 的 key**

	* ECMA-404 没有规定一个 Object 内 key 是否唯一，RFC 7159 要求 key 唯一。swxJson 尊循 RFC 7159 的要求。
	* ECMA-404 & RFC 7159 没有规定 key 是否可以为空，因此在 swxJson 中，path 相关的部分，如果以 '.' 作为分隔符，则以下路径代表的含义为：
		1. ""：当前 Object 内，key 为空的元素。例：{"":Target, ...}
		2. "."：当前 Object 内，key 为空的 sub-object 的 key 为空的元素。例：{"":{"":Target, ...}, ...}
		3. ".."：当前 Object 内，key 为空的 sub-object 的 key 为空的 sub-object 的 key 为空的元素。例：{"":{"":{"":Target, ...}, ...}, ...}
		4. "..."：当前 Object 内，key 为空的 sub-object 的 key 为空的 sub-object 的 key 为空的 sub-object 的 key 为空的元素。例：{"":{"":{"":{"":Target, ...}, ...}, ...}, ...}
		
* **转义字符及控制字符**

	JSON 在实际工作中，更多地扮演是一种数据交换格式的作用，其中的字符串可能会在不同语言和业务间传来传去。出于工程便利性考虑，swxJson 决定“任何有效的字符都平等对待”，不对原始字符串做任何修改。所以：
	
	* 能识别转义字符，但不进行转义，而是原样保存；
	* 不强制控制字符转义。
		

## 4. 性能

**重申：**

swxJson 以 **便利性** 和 **易用性** 为第一要务，当前版本**不做**性能考虑。

以下对比数据来自于 [nativejson-benchmark](https://github.com/miloyip/nativejson-benchmark) 项目评测。

评测代码请参见 [swxjsontest.cpp](/performances/nativejson-benchmark/swxjsontest.cpp)

### 4.1. 性能对比

#### 4.1.1. Prase

* **Prase Time**

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ%402.50GHz_mac64_clang8.1_1.%20Parse_Time%20(ms).png)

* **Prase Memory**

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ%402.50GHz_mac64_clang8.1_1.%20Parse_Memory%20(byte).png)

* **Prase Memory Peak**

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ%402.50GHz_mac64_clang8.1_1.%20Parse_MemoryPeak%20(byte).png)

* **Prase Alloc Count**

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ%402.50GHz_mac64_clang8.1_1.%20Parse_AllocCount.png)

#### 4.1.2. Stringify

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ%402.50GHz_mac64_clang8.1_2.%20Stringify_Time%20(ms).png)


#### 4.1.3. Statistics

![Prase performance comparison](/performances/nativejson-benchmark/results/performance_Corei7-4870HQ%402.50GHz_mac64_clang8.1_4.%20Statistics_Time%20(ms).png)


### 4.2. 一致性测试

一致性测试，未通过部分的结果请参见：<br>
[conformance_swxJson (C++).md](/performances/nativejson-benchmark/results/conformance_swxJson%20(C%2B%2B).md)

分析：

* Parse Validation 部分

	swxJson 基于兼容性和代码复杂度考虑，兼容部分可复原的错误格式。
	* 缺失 "]" 的 Array 对象
	* 缺失 "}" 的 Object/Dict 对象
	* 尾部多余的逗号
	* 数字前方的0

	因此，在一致性测试中，将无法通过相关测试。
	
	另外，swxJson 因工程便利性考虑，swxJson 决定“任何有效的字符都平等对待”，不对原始字符串做任何修改。所以：
	
	* 能识别转义字符，但不进行转义，而是原样保存；
	* 不强制控制字符转义。

	所以在测试中，将无法通过相关测试。
	

* Parse Double 部分

	swxJson 目前用 double 而非 long double 存储浮点数。使用 strtod() 来转换。因此对于测试用例中的某些数值，比如 2.22507e-308 这个数值，strtod() &  atof() 均返回失败，errno 为 34：Math result not representable (Numerical result out of range).
	
	所以 swxJson 将无法通过 strtod()／atoi() 处理不了的数值的数值测试。
	
	另外，因大部分程序都会用到 strtod()／atoi()，所以 swxJson 暂不考虑自己实现 IEEE 754／854 标准。
	
	另外，对于没有通过如下的测试，
	
	| float | expect (Standard Answer) | actual (swxJson output) |
	|-------|-----------------|----------------|
	| 1e-214748363 | 0 (0x0160) | 0 (0x0160) |
	| 1e-214748364 | 0 (0x0160) | 0 (0x0160) |
	
	表示，情绪稳定。:)

* Parse String 部分

	swxJson 因工程便利性考虑，swxJson 决定“任何有效的字符都平等对待”，不对原始字符串做任何修改。所以：
	
	* 能识别转义字符，但不进行转义，而是原样保存；
	* 不强制控制字符转义。

	所以在测试中，将无法通过相关测试。

* Roundtrip 部分

	对于如下标准：
	
	| Standard Answer | swxJson output |
	|-----------------|----------------|
	| [0,1] | [0, 1] |
	| {"a":null,"foo":"bar"} | {"a":null, "foo":"bar"} |
	
	输出格式的问题。不会为了满足测试而修改。
	
	对于
	
	| Standard Answer | swxJson output |
	|-----------------|----------------|
	| 0.0 | 0 |
	| -0.0 | -0 |
	
	因为序列化用的是 C++ 的 std::ostream 对象，所以考虑在未来以合适的方式改进。但是 JSON 统一对待**整型**和**浮点型**，所以不会影响使用，和正确性。
	
	对于
	
	| Standard Answer | swxJson output |
	|-----------------|----------------|
	| 2.2250738585072014e-308 | 2.22507e-308 |
	| 1.7976931348623157e308 | 1.79769e+308 |
	
	浮点数精度问题。未来考虑以合适的方式修改。


## 5. 下一步

* 将内部浮点型由 double 改为 long double 保存。<br>感觉这个并不急迫，需求并不强烈。

* 提升性能和效率。<br>已经有方案，但会导致代码长度急剧增长。目前 src 一共 2942 行，不想变得更长…… :(

计划：
目前在忙其他的项目，有空再实现吧。
