TARGET = arguments
# CC     = colorgcc
CC     = gcc
CFILES = $(wildcard *.c)
OFILES = $(patsubst %.c, %.o, $(CFILES))
DFILES = $(patsubst %.c, .deps/%.d, $(CFILES))
WARN   = -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Waggregate-return \
	-Wpointer-arith -Wcast-qual -Wcast-align -Wmissing-declarations -pedantic \
	-Wnested-externs -Wredundant-decls -Wwrite-strings -Winline -Werror
CFLAGS = -std=c99 $(WARN) -g3
LDLIBS = -lm


all: $(TARGET)
	ctags *.c *.h

$(TARGET): $(OFILES)
	$(CC) -o $(TARGET) $(OFILES) $(LDLIBS)


.deps/%.d: %.c
	@mkdir -p .deps
	@$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; $(RM) -rf $@.$$$$


ifneq ($(MAKECMDGOALS),clean)
-include $(DFILES)
endif



.PHONY: clean nuke

clean:
	$(RM) -rf $(TARGET) *.o core .deps tags
