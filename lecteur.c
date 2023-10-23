/*  
    FICHIER: lecteur.c
    
    DESCRIPTION: Implémentation des fonctions de lecture et écriture des fichiers
            Nécessite l'interface 'lecteur.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#include "lecteur.h"


/*
@requires: 'cote' strictement positif
@assigns: NEANT
@ensures: Initialise un tableau de couleur de taille 'cote' * 'cote'
*/
couleur *initialiser_pix(int cote) {
    couleur *image = malloc(cote * cote * sizeof(couleur));
    return image;
}

/*
@requires: Un pointeur valide, un état initialisé
@assigns: Le tableau de couleur pointé
@ensures: Modifie le tableau de couleur pointé selon les pixels du calque au-dessus de la pile
*/
void ecrire_image(couleur *image, etat e) {
    int cote = e.pile_calques.cote;
    calque dernier_c = e.pile_calques.calque[e.pile_calques.taille - 1];
    for (int i = 0; i < cote * cote; i += 1) {
        image[i].rouge = dernier_c[i / cote][i % cote].p_couleur.rouge;
        image[i].vert = dernier_c[i / cote][i % cote].p_couleur.vert;
        image[i].bleu = dernier_c[i / cote][i % cote].p_couleur.bleu;
    }
}