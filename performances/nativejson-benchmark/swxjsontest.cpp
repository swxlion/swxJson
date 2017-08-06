#include "../test.h"

#include "swxJson/src/swxJson.cpp"
#include "swxJson/src/swxJsonParser.cpp"
#include "swxJson/src/swxJsonUtils.cpp"

using namespace swxJson;

class SWXJsonParseResult : public ParseResultBase {
public:
	JsonPtr root;
};

class SWXJsonStringResult : public StringResultBase {
	std::string s;
public:
	SWXJsonStringResult(const std::string& str): s(str) {}
	virtual const char* c_str() const { return s.c_str(); }
};

static void GenStat(Stat& stat, JsonPtr json) {
	switch (json->type()) {
		case Json::JSON_Array:
		{
			const std::list<JsonPtr> * const nlist = json->getList();
			for (const auto& node: *nlist)
				GenStat(stat, node);

				stat.arrayCount++;
				stat.elementCount += nlist->size();
			break;
		}

		case Json::JSON_Object:
		{
			const std::map<std::string, JsonPtr> * const ndict = json->getDict();
			for (const auto& jsonPair: *ndict)
			{
				GenStat(stat, jsonPair.second);
				stat.stringLength += jsonPair.first.length();
			}

			stat.objectCount++;
			stat.memberCount += ndict->size();
			stat.stringCount += ndict->size();   // member names
			break;
		}

		case Json::JSON_String:
		{
			std::string str = json->getString();

			stat.stringCount++;
			stat.stringLength += str.length();
			break;
		}

		case Json::JSON_Integer:
		case Json::JSON_Real:
			stat.numberCount++;
			break;

		case Json::JSON_Boolean:
		{
			if (json->getBool())
				stat.trueCount++;
			else
				stat.falseCount++;
			break;
		}

		case Json::JSON_Null:
			stat.nullCount++;
			break;
	}
}

class SWXJsonTest : public TestBase
{
public:
#if TEST_INFO
    virtual const char* GetName() const { return "swxJson (C++)"; }
    virtual const char* GetFilename() const { return __FILE__; }
#endif

#if TEST_PARSE
	virtual ParseResultBase* Parse(const char* json, size_t length) const {
		(void)length;
		try {
			SWXJsonParseResult* pr = new SWXJsonParseResult;
			pr->root = Json::parse(json);
			return pr;
		}
		catch (const JsonError& ex)
		{
			return 0;
		}
	}
#endif

#if TEST_STRINGIFY
	virtual StringResultBase* Stringify(const ParseResultBase* parseResult) const {
		const SWXJsonParseResult* pr = static_cast<const SWXJsonParseResult*>(parseResult);
		SWXJsonStringResult* sr = new SWXJsonStringResult(pr->root->str());
		return sr;
	}
#endif


#if TEST_STATISTICS
	virtual bool Statistics(const ParseResultBase* parseResult, Stat* stat) const {
		const SWXJsonParseResult* pr = static_cast<const SWXJsonParseResult*>(parseResult);
		memset(stat, 0, sizeof(Stat));
		GenStat(*stat, pr->root);
		return true;
	}
#endif

#if TEST_CONFORMANCE
	virtual bool ParseDouble(const char* json, double* d) const {
		try {
			JsonPtr root = Json::parse(json);
			*d = (*root)[0];
			return true;
		}
		catch (...) {
		}
		return false;
	}

	virtual bool ParseString(const char* json, std::string& s) const {
		try {
			JsonPtr root = Json::parse(json);
			s = (std::string)(*root)[0];
			return true;
		}
		catch (...) {
		}
		return false;
	}
#endif

};

REGISTER_TEST(SWXJsonTest);