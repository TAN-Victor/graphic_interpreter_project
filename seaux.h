/*  
    FICHIER: seaux.h
    
    DESCRIPTION: Interface déclarant les fonctions et structures de donnees sur les seaux
            Necessite l'interface 'couleur.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#ifndef SEAUX_H
#define SEAUX_H

#include "couleur.h"

typedef struct _seau_couleur *seau_couleur;
struct _seau_couleur {
    couleur contenu;
    seau_couleur suivant;
};

typedef struct _seau_opacite *seau_opacite;
struct _seau_opacite {
    opacite contenu;
    seau_opacite suivant;
};


/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne un seau de couleur contenant en premier élement la couleur 'ajout' suivi du seau de couleur 'c' par liste chaînée
*/
seau_couleur cons_seau_c(couleur ajout, seau_couleur c);

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne un seau d'opacité contenant en premier élement l'opacité 'ajout' suivi du seau d'opacité'o' par liste chaînée
*/
seau_opacite cons_seau_o(opacite ajout, seau_opacite o);

/*
@requires: Les deux pointeurs valides
@assigns: Les deux seaux
@ensures: Libère les seaux
*/
void free_seaux(seau_couleur *c, seau_opacite *o);

/*
@requires: NEANT
@assigns: NEANT
@ensures: Affiche le contenu d'un seau de couleur
*/
void print_seau_couleur(seau_couleur c);

/*
@requires: NEANT
@assigns: NEANT
@ensures: Affiche le contenu d'un seau d'opacité
*/
void print_seau_opacite(seau_opacite o);

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne la couleur courante d'un seau, obtenu en faisant la moyenne des couleurs du seau
*/
couleur couleur_courante(seau_couleur c);

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne l'opacité courante d'un seau, obtenu en faisant la moyenne des opacités du seau
*/
opacite opacite_courante(seau_opacite o);

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne le pixel courant d'un seau de couleur et d'opacité
*/
pixel pixel_courant_futur(seau_couleur c, seau_opacite o);

#endif