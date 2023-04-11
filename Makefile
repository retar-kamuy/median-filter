CC  	 = clang++
CFLAGS   = -g -std=c++17
CFLAGS  +=`pkg-config --cflags opencv`
TARGET   = main
SRCS	 = main.cpp medianFilter.cpp

OBJS     = $(SRCS:.cpp=.o)

INCDIR   =
LIBDIR   =

LIBS     = `pkg-config --libs opencv`

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

all: clean $(OBJS) $(TARGET)

clean:
	-rm -f $(OBJS) $(TARGET) *.d

gtest:
	clang++ bubbleSort.cpp test/bubbleSort_test.cpp -I. -I/opt/googletest/include -L/opt/googletest/lib64 -lgtest -lgtest_main

bazel_test:
	bazel build --config=clang_config :bubbleSort_test

cmake_test:
	cmake -S . -B build && cmake --build build && cd build && ctest
