MAKE    =      gmake
C       =      gcc
CC      =      g++
SIZE	=      size

GENSEN_OBJ	= gensen.o tools.o
GENSEN		= gensen

FLAGS 		= -g -fno-inline

all: $(GENSEN)

gensen.o: gensen.cc gensen.h
	$(CC) $(FLAGS) -c gensen.cc

tools.o: tools.cc tools.hh
	$(CC) $(FLAGS) -c tools.cc

$(GENSEN): $(GENSEN_OBJ)
	$(CC) $(FLAGS) $(LIBOBJS) $(GENSEN_OBJ) -o $(GENSEN)
	@size $(GENSEN)

clean:
	rm -f *.o core *~ $(GENSEN)
