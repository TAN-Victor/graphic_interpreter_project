/*  
    FICHIER: couleur.c
    
    DESCRIPTION: Implémentation des fonctions et structures de données sur les composantes, les couleurs et les pixels
            Nécessite l'interface 'couleur.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#include "couleur.h"

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie une couleur selon les composantes entrées
*/
couleur init_couleur(composante rouge, composante vert, composante bleu) {
    couleur color;
    color.rouge = rouge;
    color.vert = vert;
    color.bleu = bleu;
    return color;
}


