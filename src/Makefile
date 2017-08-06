OBJS_CXX = swxJson.o swxJsonParser.o swxJsonUtils.o

LIBSWXJSON_A = libswxjson.a

OPTIMIZE = -O2

CFLAGS =
CXXFLAGS = -std=c++11
CPPFLAGS = -g -Wall -Werror -fPIC $(OPTIMIZE)
LIBS = $(OPTIMIZE) -lstdc++

# target
all: $(LIBSWXJSON_A)

clean:
	rm -rf $(LIBSWXJSON_A)
	rm -rf *.o

# basic rules
$(LIBSWXJSON_A): $(OBJS_CXX)
	$(AR) -rcs $@ $(OBJS_CXX)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.cpp:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LIBS)
