ROSS_COMPILE_PREFIX = 
CROSS_COMPILE_PATH   = 
CC      =  $(CROSS_COMPILE_PREFIX)gcc
CFLAGS  = $(INCLUDES) -O0 -Wall -W -pedantic -std=c99
LDFLAGS = $(LIBS) 
LIBS=
INCLUDES= 
DFLAGS  =  -g -DDEBUG
CLINK  = -c -o
RM  = rm -f
GLIBCFLAGS = `pkg-config --cflags glib-2.0`
GLIBLFLAGS = `pkg-config --libs glib-2.0`
MAIN_SRC= console.c
NO_MAIN_SRC= guessnum.c
MAIN_OBJ  = $(patsubst %.c,%.o, $(MAIN_SRC))
NO_MAIN_OBJ  = $(patsubst %.c,%.o, $(NO_MAIN_SRC))
ALL_OBJ=$(MAIN_OBJ) $(NO_MAIN_OBJ)
EXECUTABLE =$(patsubst %.c,%, $(MAIN_SRC))
DEPENDENCY = $(patsubst %.c,%.d, $(ALL_SRC))

all: $(DEPENDENCY) $(EXECUTABLE)

include $(DEPENDENCY)
 
console:$(ALL_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)
    
%: %.o
	$(CC)  $<  -o $@ $(LDFLAGS) 
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)	$(DFLAGS)


%.d: %.c
	$(CC) -MM $(CFLAGS) $< >$@.$$$$;\
	sed 's,\($*\)\.o:,\1.o $@:,g' < $@.$$$$ > $@;\
	$(RM) $@.$$$$;

clean:
	$(RM) $(EXECUTABLE) *.o *.bak *.c~ *.h~ *.d
