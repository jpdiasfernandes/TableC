CC      := gcc
CCFLAGS := -O2 
LDFLAGS := 

TARGETS := main table.so
MAINS   := main.o
OBJ     := table.o main.o
DEPS    := table.h

.PHONY: clean all 

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJ)

table.so: table.c table.h
	$(CC) $(CCFLAGS) -fPIC -shared -o $@ table.c -lc 

tablestaticcode.a: table.o
	ar rcs tablestaticcode.a table.o
%.o : %.c
	$(CC) -c -DDEBUG -g $^  -o $@ `pkg-config --cflags --libs glib-2.0`

$(TARGETS): $(OBJ)
	$(CC) $^ -o $@  `pkg-config --cflags --libs glib-2.0`
