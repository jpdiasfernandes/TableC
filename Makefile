CC      := gcc
CCFLAGS := -O2 
LDFLAGS := 

TARGETS := main
MAINS   := main.o
OBJ     := table.o main.o helpers.o search.o generic.o memory.o
DEPS    := table.h helpers.h search.h generic.h memory.h

.PHONY: clean all 

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJ)

%.o : %.c
	$(CC) -c -DDEBUG -g $^  -o $@ `pkg-config --cflags --libs glib-2.0`

$(TARGETS): $(OBJ)
	$(CC) $^ -o $@  `pkg-config --cflags --libs glib-2.0`
