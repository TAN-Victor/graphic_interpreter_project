/*  
    FICHIER: couleur.h
    
    DESCRIPTION: Interface déclarant les fonctions et structures de données sur les composantes, les couleurs et les pixels
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#ifndef COULEUR_H
#define COULEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned char composante;

struct _couleur {
    composante rouge;
    composante vert;
    composante bleu;
};
typedef struct _couleur couleur;

typedef composante opacite;

struct pixel {
    couleur p_couleur;
    opacite p_opacite;
};
typedef struct pixel pixel;



/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie une couleur selon les composantes entrées
*/
couleur init_couleur(composante rouge, composante vert, composante bleu);

#endif