# README
## AUTEUR: TAN Victor - 1A - ENSIIE


\
Description: Vous trouverez dans l'archive __victor_tan.tgz__ :
* le rapport *rapport.pdf*,
* l'exécutable *prog*, 
* les différents fichiers **.c* et **.h*,
* le Makefile,
* ce fichier *readme.md*.


***

## Execution du programme

### Sans argument:

1.     sh> ./prog
    Permet d'entrer __au clavier__ le contenu d'un *fichier.ipi* et retourne sur la sortie standard stdout le contenu d'un *fichier.ppm*.

    Entrée (exemple):
    
        20 <ENTRER>
        rfi <ENTRER>
        <CTL + D>

2.     sh> ./prog < in.ipi
    Permet de lire le contenu du fichier *in.ipi* et retourne sur la sortie standard stdout le contenu d'un *fichier.ppm*.


3.     sh> ./prog > out.ppm
    Permet d'entrer __au clavier__ le contenu d'un *fichier.ipi* et écrit dans le fichier *out.ppm* le contenu d'un *fichier.ppm*.


4.     sh> ./prog < in.ipi > out.ppm
    Permet de lire le contenu du fichier *in.ipi* et écrit dans le fichier *out.ppm* le contenu d'un *fichier.ppm*.


5.     sh> ./prog |display
    Permet d'entrer __au clavier__ le contenu d'un *fichier.ipi* et affiche l'image grâce à la visionneuse **display**.


6.     sh> ./prog < in.ipi |display
    Permet de lire le contenu du fichier *in.ipi* et affiche l'image grâce à la visionneuse **display**.




### Avec 1 argument:

7.     sh> ./prog in.ipi
    Permet de lire le contenu du fichier *in.ipi* et retourne sur la sortie standard stdout le contenu d'un *fichier.ppm*.


8.     sh> ./prog in.ipi > out.ppm
    Permet de lire le contenu du fichier *in.ipi* et écrit dans le fichier *out.ppm* le contenu d'un *fichier.ppm*.


9.     sh> ./prog in.ipi |display
    Permet de lire le contenu du fichier *in.ipi* et affiche l'image grâce à la visionneuse **display**.



### Avec 2 arguments:

10.     sh> ./prog in.ipi out.ppm
    Permet de lire le contenu du fichier *in.ipi* et écrit dans le fichier *out.ppm* le contenu d'un *fichier.ppm*.




### Avec 3 ou plus arguments:

11.     sh> ./prog in.ipi out.ppm autres1 autres2....
    Permet de lire le contenu du fichier *in.ipi* et écrit dans le fichier *out.ppm* le contenu d'un *fichier.ppm*. Tous les autres arguments sont ignorés.


***

## Composition d'un fichier .ipi

En première ligne: la taille du côté de l'image (carré) en pixel, doit être entre 1 et 2<sup>32</sup> - 1. Des messages d'erreurs existent le cas échéant.

Puis, un ensemble de caractères.

