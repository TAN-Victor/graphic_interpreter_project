/*  
    FICHIER: calques.h
    
    DESCRIPTION: Interface déclarant les fonctions et structures de données sur les calques et les piles
            Nécessite l'interface 'couleur.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#ifndef CALQUES_H
#define MAX_pile 10
#include "couleur.h"
#define CALQUES_H


typedef pixel **calque;

struct _pile {
    unsigned int taille;
    unsigned int cote;
    calque calque[MAX_pile];
};
typedef struct _pile pile;



/*
@requires: Un pointeur valide
@assigns:  La pile 'pile'
@ensures: Modification par effet de la pile si la taille est inférieure à 9, en ajoutant un calque au sommet de la pile
        Le nouveau calque est initialisé avec des pixels RGBA (0, 0, 0, 0)
*/
void new_calque(pile *pile);

/*
@requires: 'cote' strictement positif
@assigns:  NEANT
@ensures: Renvoie une pile composé d'un seul calque de taille cote * cote pixels
*/
pile initialiser_pile(int cote);

/*
@requires: 'c' initialisée avec au moins 1 calque
@assigns:  NEANT
@ensures: Affiche tous les pixels des calques contenus dans la pile 'c' sous la forme RGBA
*/
void print_pile(pile c);

/*
@requires: Un pointeur valide
@assigns:  La pile pointée par 'c' est liberee
@ensures: Libère et renvoie le calque au-dessus de la pile
*/
calque liberer_calque_top(pile *c);

#endif