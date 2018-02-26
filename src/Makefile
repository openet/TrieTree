include ../make.make

NAME := libtrietree.so 

SHLIB := ../$(OUTPUT_ROOT)/$(NAME)

LDFLAGS := 

INCLUDE := 

CFLAGS := -fpic -c -Wall

SRCS := Trie.cc

OBJECTS := $(SRCS:.cc=.o)

all: $(OB_DIR) $(SRCS) $(SHLIB)

$(SHLIB): $(OBJECTS) 
	mkdir -p ../$(OUTPUT_ROOT)
	$(CC) $(LDFLAGS) -shared $(OBJECTS) -o $@

.cc.o: 
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJECTS) $(SHLIB)


