OPT=-Wall -lm

# Biblioteques

cues.o : cues.c
	gcc $(OPT) -c cues.c

llegirfitxers.o : llegirfitxers.c
	gcc $(OPT) -c llegirfitxers.c

# Utilitat

AEstrella : AEstrella.c llegirfitxers.o cues.o
	gcc $(OPT) -o AEstrella cues.o llegirfitxers.o AEstrella.c

# Neteja

clean :
	rm -f llegirfitxers.o cues.o

realclean : clean
	rm -f AEstrella
