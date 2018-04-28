CC=gcc
LD=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes 
LDFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes 
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
# files 

EXEC=puissance4
MODULES_P4=main.c GUI.c IA.c
OBJECTS_P4=main.o GUI.o IA.o

EXEC_GUI=test
MODULES_TEST=main_gui.c GUI.c
OBJECTS_TEST=main_gui.o GUI.o
#rules

all: $(EXEC)

puissance4: $(OBJECTS_P4)
	$(LD) -o $(EXEC) $(OBJECTS_P4) $(LDFLAGS)

test: $(OBJECTS_TEST)
	$(LD) -o $@ $^ $(LDFLAGS) $(GTKFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

main_gui.o: main_gui.c
	$(CC) -c main_gui.c -o main_gui.o $(CFLAGS) $(GTKFLAGS)

GUI.o: GUI.c GUI.h
	$(CC) -c GUI.c -o GUI.o $(CFLAGS) $(GTKFLAGS)

IA.o: IA.c IA.h
	$(CC) -c IA.c -o IA.o $(CFLAGS)

doc:
	$(DOXYGEN)