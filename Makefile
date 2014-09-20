FILES   =       i2c lcd
EXAMPLES=       example
DEPS    =       Makefile i2c.h lcd.h

AR      =       ar
CC	=	gcc
CFLAGS	=	-g -O2 -Wall -W -ggdb
LDLIBS  =	
LIBNAME =       liblcm1602

LIBAR   =       $(addsuffix .a, $(LIBNAME))
LIBOBJS	=       $(addsuffix .o, $(FILES))
OBJS    =       $(addsuffix .o, $(EXAMPLES))

all: $(LIBOBJS) $(OBJS) $(LIBAR) $(EXAMPLES)
	@echo "done"

$(EXAMPLES): %: %.o $(DEPS) $(LIBAR)
	$(CC) $(CFLAGS) -o $@ $< $(LIBAR) $(LDLIBS)

$(LIBAR):
	$(AR) rcs $(LIBAR) $(LIBOBJS)

$(LIBOBJS): %.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJS): %.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(LIBAR) $(OBJS) $(LIBOBJS) $(EXAMPLES)

