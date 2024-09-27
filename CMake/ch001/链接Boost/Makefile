# 自行构建的Boost库

BOOST_DIR = $${HOME}/boost
BOOST_LIB_DIR = ${BOOST_DIR}/stage/lib

CXXFLAGS = -I $(BOOST_DIR)
LDFLAGS = -L $(BOOST_LIB_DIR) -Wl,-R$(BOOST_LIB_DIR)

# 将以上几行全部注释，即可使用安装的预编译Boost库

all: static_boost shared_boost

static_boost: main.cpp
	g++ main.cpp $(CXXFLAGS) $(LDFLAGS) -l:libboost_regex.a -o static_boost

shared_boost: main.cpp
	g++ main.cpp $(CXXFLAGS) $(LDFLAGS) -lboost_regex -o shared_boost

clean:
	rm *_boost