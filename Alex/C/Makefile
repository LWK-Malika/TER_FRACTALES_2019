CXX		= gcc #g++
CXX_FLAGS	= -g -O0 -ansi -pedantic -Wall 

LD_FLAGS 	=

PROGS		= itv

SOURCES		=  #simple.c

HEADERS		= 

DEPFILE		= .depend

ifeq ($(wildcard $(DEPFILE)), )

all: $(DEPFILE)
	make

else

all: $(PROGS)
include $(DEPFILE)

endif

include $(DEPFILE)

.SUFFIXES: .c .h .o #cpp

$(PROGS): $(SOURCES:.cpp=.o)
	$(CXX) $(LD_FLAGS) $^ -o $@

.cpp.o:
	$(CXX) $(CXX_FLAGS)$< -c

$(DEPFILE): $(SOURCES)
	$(CXX) -MM $^ > $@ 

clean:
	rm -f *~ $(SOURCES:.cpp=.o) $(PROGS)
