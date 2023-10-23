/*  
    FICHIER: master.c
    
    DESCRIPTION: Fichier source avec le main
            Nécessite les interfaces 'lecteur.h' et 'outils.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#include <string.h>

#include "lecteur.h"
#include "outils.h"

int main(int argc, char *argv[]) {
    FILE *f1;
    FILE *f2;

    if (argc == 1) {
        f1 = stdin;
        f2 = stdout;
    }

    else if (argc == 2) {
        char *extension = strrchr(argv[1], '.');
        if (extension == NULL || strcmp(extension, ".ipi") < 0) {
            fprintf(stderr, "Attention, le fichier d'entrée n'est pas du bon format .ipi.\n");
            exit(1);
        }
        f1 = fopen(argv[1], "r");
        if (f1 == NULL) {
            perror("Erreur pour la lecture du 1er fichier.\n");
            exit(1);
        }
        f2 = stdout;
    }

    else if (argc > 2) {
        f1 = fopen(argv[1], "r");
        if (f1 == NULL) {
            perror("Erreur pour la lecture du 1er fichier.\n");
            exit(1);
        }
        f2 = fopen(argv[2], "w");
        if (f2 == NULL) {
            perror("Erreur pour l'ecriture du 2nd fichier.\n");
            exit(1);
        }
        if (argc > 3) {
            fprintf(stderr, "Attention, plus de 2 arguments. Les autres arguments ne sont pas pris en compte.\n");
        }
    }

    char buf[512] = {0};
    int cote;
    int test_entier;
    
    fgets(buf, 512, f1);
    test_entier = sscanf(buf, "%d", &cote);

    if (test_entier != 1) {
        fprintf(stderr, "Attention, la taille d'un côté de l'image doit être un entier strictement positif.\n");
        exit(1);
    }

    if (cote == 0) {
        fprintf(stderr, "Attention, une taille d'image de (0 x 0) pixel est impossible.\n");
        exit(1);
    }

    if (cote < 0) {
        fprintf(stderr, "Attention, la taille du côté de l'image doit être strictement positive.\n");
        exit(1);
    }

    if (cote > 50000) {
        fprintf(stderr, "Attention, la taille d'image est de (%d x %d) pixels, s'agit-il d'une erreur ?\n Si oui, veuillez arrêter le programme avec [CONTROL] + [c].\n", cote, cote);
    }

    etat etat_machine = initialiser_etat(cote);

    char *test = fgets(buf, 512, f1);
    couleur *image = initialiser_pix(cote);
    while (test != NULL) {
        /*
            La lecture de l'entrée se fait par bloc de 512 caractères, mis dans le buffer 'buf'.
            Le buffer est réintialisé durant chaque passage avec 'memset'.
            Lorsque la fin du fichier est atteint, fgets retourne 'NULL'.
        */
        modification(&etat_machine, buf);
        memset(buf, 0, 512); 
        test = fgets(buf, 512, f1);
    }
    fprintf(f2, "P6\n%d %d\n255\n", cote, cote);
    ecrire_image(image, etat_machine);
    fwrite(image, sizeof(couleur), cote * cote, f2);     
    fclose(f1);
    fclose(f2);
    
    return 0;
}