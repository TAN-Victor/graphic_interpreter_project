prog: couleur.o calques.o seaux.o curseur.o etat.o outils.o lecteur.o main.o
	gcc -Wall -Wextra -g couleur.o calques.o seaux.o curseur.o etat.o outils.o lecteur.o main.o -o prog

couleur.o: couleur.c couleur.h
	gcc -Wall -Wextra -c couleur.c

calques.o: calques.c calques.h
	gcc -Wall -Wextra -c calques.c 

seaux.o: seaux.c seaux.h
	gcc -Wall -Wextra -c seaux.c

curseur.o: curseur.c curseur.h
	gcc -Wall -Wextra -c curseur.c

etat.o: etat.c etat.h
	gcc -Wall -Wextra -c etat.c

outils.o: outils.c outils.h
	gcc -Wall -Wextra -c outils.c

lecteur.o: lecteur.c lecteur.h
	gcc -Wall -Wextra -c lecteur.c

main.o: main.c lecteur.h outils.h
	gcc -Wall -Wextra -c main.c

