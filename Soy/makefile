IDIR = ./lib
CC = gcc
CFLAGS = -I$(IDIR)

ODIR=./
LDIR =../lib

# math library -lm
LIBS=-lm 

_DEPS = person.h fields.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

IODIR = $(IDIR)/
_OBJ = soy.o $(IODIR)person.o $(IODIR)fields.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

soy: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(IODIR)/*.o *~ core $(INCDIR)/*~

