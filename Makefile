include make.make

NAME := trietree 

EXECUTABLE := $(OUTPUT_ROOT)/$(NAME)

LDFLAGS := -lpthread -lgtest -lgtest_main -L/opt/gmock-1.6.0/gtest/lib/

INCLUDE := -I/opt/gmock-1.6.0/gtest/include/

CFLAGS := -c -Wall

SRCS := src/Trie.cc

OBJECTS := $(SRCS:.cc=.o)

all: $(OB_DIR) $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	mkdir -p $(OUTPUT_ROOT)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o: 
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

test:
	$(EXECUTABLE)

install:
	echo "install?"
