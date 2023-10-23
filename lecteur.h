/*  
    FICHIER: lecteur.h
    
    DESCRIPTION: Interface déclarant les fonctions de lecture et écriture des fichiers
            Nécessite l'interface 'etat.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#ifndef LECTEUR_H
#define LECTEUR_H
#include "etat.h"

/*
@requires: 'cote' strictement positif
@assigns: NEANT
@ensures: Initialise un tableau de couleur de taille 'cote' * 'cote'
*/
couleur *initialiser_pix(int cote);

/*
@requires: Un pointeur valide, un état initialisé
@assigns: Le tableau de couleur pointé
@ensures: Modifie le tableau de couleur pointé selon les pixels du calque au-dessus de la pile
*/
void ecrire_image(couleur *image, etat e);

#endif