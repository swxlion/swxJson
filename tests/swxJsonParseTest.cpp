/*
	Linux:
	g++ --std=c++11 -lstdc++ -o swxJsonParseTest ../src/swxJson.cpp ../src/swxJsonParser.cpp  ../src/swxJsonUtils.cpp swxJsonParseTest.cpp

	Mac:
	g++ --std=c++11 -lstdc++ -o swxJsonParseTest ../src/swxJson.cpp ../src/swxJsonParser.cpp  ../src/swxJsonUtils.cpp swxJsonParseTest.cpp
*/

#include <fstream>
#include <iostream>
#include "swxJson.h"

using namespace std;
using namespace swxJson;

void parseTest(const char *filenme, const char *path)
{
	std::string content;
	std::ifstream in(filenme, std::ios::in);
	if (in.is_open())
	{
		std::istreambuf_iterator<char> beg(in), end;
		content = std::string(beg, end);
		in.close();
	}
	else
	{
		cout<<"[Error]: Cannot open the file "<<filenme<<endl;
		return;
	}

	try {
		JsonPtr json = Json::parse(content.c_str());
		cout<<"get json:"<<endl;
		cout<<json<<endl<<endl;
		cout<<"get value by path "<<path<<endl;
		cout<<(*json)[path]<<endl;
		cout<<json->getNode(path)->str()<<endl;
		cout<<json->wantString(path)<<endl;
	}
	catch (const JsonError &e)
	{
		cout<<"[Error]: "<<e.message()<<" line: "<<e.lineNumber()<<", fun: "<<e.function()<<endl;
	}
}

int main(int argc, const char** argv)
{
	if (argc < 3)
	{
		std::cout<<"Usage: "<<argv[0]<<" <json_filename> <fetch_path>"<<std::endl;
		return 0;
	}

	parseTest(argv[1], argv[2]);
	return 0;
}
