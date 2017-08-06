EXES_TEST_Functional = swxJsonFunctionalTest
EXES_TEST_Advanced = swxJsonAdvancedTest
EXES_TEST_Parse = swxJsonParseTest

EXS_perTest = perTest

OPTIMIZE = -O2

CXXFLAGS = -std=c++11
CPPFLAGS = -g -Wall -rdynamic -Werror -fPIC $(OPTIMIZE) -I../src
LIBS += $(OPTIMIZE) -L../src -lswxjson

all: $(EXES_TEST_Functional) $(EXES_TEST_Advanced) $(EXES_TEST_Parse) $(EXS_perTest)

clean:
	$(RM) -rf *.dSYM
	$(RM) $(EXES_TEST_Functional) $(EXES_TEST_Advanced) $(EXES_TEST_Parse) $(EXS_perTest)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.cpp:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LIBS)
