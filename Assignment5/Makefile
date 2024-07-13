OBJ = main.o connect.o spectator.o view.o flyer.o escape.o hero.o
EXE = a5
CC = gcc -Wall 

$(EXE):	$(OBJ)
	$(CC) -o $(EXE) $(OBJ)

main.o:		main.c defs.h
	$(CC) -c main.c

connect.o:	connect.c defs.h
	$(CC) -c connect.c

spectator.o:	spectator.c defs.h
	$(CC) -c spectator.c

view.o:		view.c defs.h
	$(CC) -c view.c

flyer.o:	flyer.c defs.h
	$(CC) -c flyer.c

escape.o:	escape.c defs.h
	$(CC) -c escape.c

hero.o:		hero.c defs.h
	$(CC) -c hero.c

clean:
	rm -f $(EXE) $(OBJ)
