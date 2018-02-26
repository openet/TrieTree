include ../make.make

NAME := gtest

EXECUTABLE := gtest

LDFLAGS := -lpthread -lgtest -lgtest_main -L/opt/gmock-1.6.0/gtest/lib/ -ltrietree -L../release/

INCLUDE := -I/opt/gmock-1.6.0/gtest/include/ -I../src/

CFLAGS := -c -Wall

SRCS := TrieTreeTest.cc main.cc

OBJECTS := $(SRCS:.cc=.o)

all: $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o: 
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

test:
	$(EXECUTABLE)


