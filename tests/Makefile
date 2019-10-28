EXES_TEST_Functional = swxJsonFunctionalTest
EXES_TEST_Advanced_Fetch = swxJsonAdvancedTest_fetch
EXES_TEST_Advanced_Fetch_2 = swxJsonAdvancedTest_fetch_v2
EXES_TEST_Advanced_Modify = swxJsonAdvancedTest_modify
EXES_TEST_Parse = swxJsonParseTest


OPTIMIZE = -O2

CXXFLAGS = -std=c++11
CPPFLAGS = -g -Wall -rdynamic -Werror -fPIC $(OPTIMIZE) -I../src
LIBS += $(OPTIMIZE) -L../src -lswxjson

all: $(EXES_TEST_Functional) $(EXES_TEST_Advanced_Fetch) $(EXES_TEST_Advanced_Fetch_2) $(EXES_TEST_Advanced_Modify) $(EXES_TEST_Parse)

clean:
	$(RM) -rf *.dSYM
	$(RM) $(EXES_TEST_Functional) $(EXES_TEST_Advanced_Fetch) $(EXES_TEST_Advanced_Fetch_2) $(EXES_TEST_Advanced_Modify) $(EXES_TEST_Parse)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.cpp:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LIBS)
