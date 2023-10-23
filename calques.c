/*  
    FICHIER: calques.c
    
    DESCRIPTION: Implémentation des fonctions et structures de données sur les calques et les piles
            Nécessite l'interface 'calques.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#include "calques.h"


/*
@requires: Un pointeur valide
@assigns:  La pile 'pile'
@ensures: Modification par effet de la pile si la taille est inférieure à 9, en ajoutant un calque au sommet de la pile
        Le nouveau calque est initialisé avec des pixels RGBA (0, 0, 0, 0)
*/
void new_calque(pile *pile) {
    if (pile->taille == 10) { // La fonction [new_calque] est la seule pouvant augmenter la taille de la pile, donc la pile n'aura jamais 11 calques
        fprintf(stderr, "[new_calque] du fichier calques.c - impossible d'avoir plus de 10 calques, aucune action effectuee.\n");
        return;
    }
    calque calq;
    int cote = pile->cote;
    calq = (pixel **)malloc(cote * sizeof(pixel *));
    for (int i = 0; i < cote; i += 1) {
        calq[i] = (pixel *)malloc(cote * sizeof(pixel));
        for (int j = 0; j < cote; j += 1) {
            calq[i][j].p_couleur.bleu = 0;
            calq[i][j].p_couleur.rouge = 0;
            calq[i][j].p_couleur.vert = 0;
            calq[i][j].p_opacite = 0;
        }
    }
    pile->taille += 1;
    pile->calque[pile->taille - 1] = calq;
}

/*
@requires: 'cote' strictement positif
@assigns:  NEANT
@ensures: Renvoie une pile composé d'un seul calque de taille cote * cote pixels
*/
pile initialiser_pile(int cote) {
    pile pile_calqs;
    pile_calqs.taille = 0;
    pile_calqs.cote = cote;
    new_calque(&pile_calqs);
    return pile_calqs;
}

/*
@requires: 'c' initialisée avec au moins 1 calque
@assigns:  NEANT
@ensures: Affiche tous les pixels des calques contenus dans la pile 'c' sous la forme RGBA
*/
void print_pile(pile c) {
    int cote = c.cote;
    int taille = c.taille;
    for (int i = 0; i < taille; i += 1) {
        printf("\n========== Calque n°%d: ========== \n", i);
        fflush(stdout);
        for (int j = 0; j < cote; j += 1) {
            for (int k = 0; k < cote; k += 1) {
                printf("(%3d, %3d, %3d, %3d)", c.calque[i][j][k].p_couleur.rouge, c.calque[i][j][k].p_couleur.vert, c.calque[i][j][k].p_couleur.bleu, c.calque[i][j][k].p_opacite);
                fflush(stdout);
            }
            printf("\n");
        }
        printf("========== ========== ========== \n"); 
        fflush(stdout);
    }
}

/*
@requires: Un pointeur valide
@assigns:  La pile pointée par 'c'
@ensures: Libère et renvoie le calque au-dessus de la pile
*/
calque liberer_calque_top(pile *c) {
    int cote = c->cote;
    int sommet = c->taille -1;
    for (int j = 0; j < cote; j += 1) {
        free(c->calque[sommet][j]);
    }
    free(c->calque[sommet]);
    c->taille -= 1;
    return c->calque[sommet];
}




