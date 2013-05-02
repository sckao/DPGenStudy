CC=g++ -g -fPIC -Wall -O -ansi -D_GNU_SOURCE -g -O2 -m64
ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags`
LIB=`${ROOTSYS}/bin/root-config --libs`
GLIB=`${ROOTSYS}/bin/root-config --glibs`

OBJECTS=AnaInput.o hDraw.o Histogram.o Rtuple.o DPSelection.o TestGen.o Background.o BackgroundStudy.o Trigger.o Output.o Systematic.o

all:test.exe

AnaInput.o : AnaInput.cc AnaInput.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

hDraw.o : hDraw.cc hDraw.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

Histogram.o : Histogram.cc Histogram.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

Rtuple.o : Rtuple.cc Rtuple.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

DPSelection.o : DPSelection.cc DPSelection.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

#TestGen.o : TestGen.cc TestGen.h Histogram.h
TestGen.o : TestGen.cc TestGen.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

Background.o : Background.cc Background.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

BackgroundStudy.o : BackgroundStudy.cc BackgroundStudy.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

Trigger.o : Trigger.cc Trigger.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

Output.o : Output.cc Output.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

Systematic.o : Systematic.cc Systematic.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

test.exe : main.cc $(OBJECTS)
	$(CC) -o $@ $< $(OBJECTS) $(ROOTFLAG) $(LIB) $(GLIB)

clean : 
	rm -rf *.o test.exe
