CC=gcc
LD=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes 
LDFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes 
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
# files 

EXEC=puissance4
MODULES_P4=main.c GUI.c IA.c back_office.c control.c
OBJECTS_P4=main.o GUI.o IA.o back_office.h control.h

EXEC_GUI=test
MODULES_TEST=main_gui.c GUI.c control.c back_office.c
OBJECTS_TEST=main_gui.o GUI.o control.o back_office.o
#rules

all: $(EXEC)

puissance4: $(OBJECTS_P4)
	$(LD) -o $(EXEC) $(OBJECTS_P4) $(LDFLAGS) $(GTKFLAGS)

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

control.o: control.c control.h
	$(CC) -c control.c -o control.o $(CFLAGS) $(GTKFLAGS)

back_office.o: back_office.c back_office.h
	$(CC) -c back_office.c -o back_office.o $(CFLAGS) $(GTKFLAGS)

doc:
	$(DOXYGEN)