##############################################
 #	Date: 05.11.2018
#	UE: HLIN302
 #    	Projet: fractale
#
 #
#
 #
#
##############################################

MSG=@
ECH=echo
CLR=clear
LIST=$(CLR) ls

##CC=gcc
CC=g++
DEBUG=
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -ansi -pedantic -g
	LDFLAGS= -lncurses
else
	CFLAGS=-W -Wall -ansi -pedantic
	LDFLAGS= -lglut -lGLU -lGL #-lncurses
endif

##SOURCES=$(wildcard *.c)
SOURCES=$(wildcard *.cpp)

OBJ=$(SOURCES:.cpp=.o)
EXE=main

RARROW="\n>>>>>>>>>>>>>"
#13 right arrow
LARROW="<<<<<<<<<<<<<\n"
#13 left  arrow


#Quand il y a une dépendance, $< donne une erreur, il faut alors utiliser $^
all: $(EXE)
ifeq ($(DEBUG),yes)
	$(MSG)$(ECH) "Compilation en mode Debug"
else
	$(MSG)$(ECH) "Compilation en mode Release"

endif
#	$(MSG)$(ECH) "SOURCES ["$(SOURCES)"] \nOBJETS ["$(OBJ)"]"
	$(MSG)$(ECH) "Le programme" $(EXE) "est compilé...\n"


#$(SOURCES): $(OBJ)
#	$(MSG)$(CC) -o $@ $< $(LDFLAGS)

	$(CLR)
	$(MSG)$(ECH) "Suppression des objets crées ..."
	$(MSG)rm -rf *.o
	$(MSG)$(ECH) $(RARROW)"Done"$(LARROW)

$(EXE): $(OBJ)
	$(MSG)$(ECH) "SOURCES ["$(SOURCES)"] \nOBJETS ["$(OBJ)"]"
	$(MSG)$(ECH) "Compilation de" $(EXE) "a partir des objets ... " 
	$(MSG)$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	$(MSG)$(ECH) $(RARROW)"Done"$(LARROW)

$(OBJ): $(SOURCES)
	$(MSG)$(ECH) "Les sources sont [" $(SOURCES) "]..."
	$(MSG)$(ECH) "Création des objets ..."
	$(MSG)$(CC) -c $^ $(LDFLAGS)
	$(MSG)$(ECH) $(RARROW)"Done"$(LARROW)

#%.o: %.c il faudrait tester la regle d'inférence
#	$(MSG)$(CC) -o $@ -c $< $(CFLAGS)

clean:
	$(CLR)
	$(MSG)$(ECH) "Suppression des objets crées ..."
	$(MSG)rm -rf *.o
	$(MSG)$(ECH) $(RARROW)"Done"$(LARROW)

mrproper: clean
	$(MSG)$(ECH) "Suppression des fichiers temporaires et du programme principal..."
	$(MSG)rm -rf $(EXE) *~ \#*#
	$(MSG)$(ECH) $(RARROW)"Done"$(LARROW)

