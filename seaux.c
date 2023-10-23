/*  
    FICHIER: seaux.c
    
    DESCRIPTION: Implémentation des fonctions et structures de données sur les seaux
            Nécessite l'interface 'seaux.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#include "seaux.h"

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne un seau de couleur contenant en premier élement la couleur 'ajout' suivi du seau de couleur 'c' par liste chaînée
*/
seau_couleur cons_seau_c(couleur ajout, seau_couleur c) {
    seau_couleur tmp = malloc(sizeof(seau_couleur));
    tmp->contenu = ajout;
    tmp->suivant = c;
    return tmp;
}

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne un seau d'opacité contenant en premier élement l'opacité 'ajout' suivi du seau d'opacité'o' par liste chaînée
*/
seau_opacite cons_seau_o(opacite ajout, seau_opacite o) {
    seau_opacite tmp = malloc(sizeof(seau_opacite));
    tmp->contenu = ajout;
    tmp->suivant = o;
    return tmp;
}

/*
@requires: Les deux pointeurs valides
@assigns: Les deux seaux
@ensures: Libère les seaux
*/
void free_seaux(seau_couleur *c, seau_opacite *o) {
    seau_couleur cur_c_actuel;
    seau_opacite cur_o_actuel;
    while ((*c) != NULL) {
        cur_c_actuel = *c;
        *c = (*c)->suivant;
        free(cur_c_actuel);
    }
    while ((*o) != NULL) {
        cur_o_actuel = *o;
        *o = (*o)->suivant;
        free(cur_o_actuel);
    }
}

/*
@requires: NEANT
@assigns: NEANT
@ensures: Affiche le contenu d'un seau de couleur
*/
void print_seau_couleur(seau_couleur c) {
    while (c != NULL) {
        printf("[%d, %d, %d]-> ", c->contenu.rouge, c->contenu.vert, c->contenu.bleu);
        c = c->suivant;
    }
    printf("[]\n");
}

/*
@requires: NEANT
@assigns: NEANT
@ensures: Affiche le contenu d'un seau d'opacité
*/
void print_seau_opacite(seau_opacite o) {
    while (o != NULL) {
        printf("[%d]-> ", o->contenu);
        o = o->suivant;
    }
    printf("[]\n");
}

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne la couleur courante d'un seau, obtenu en faisant la moyenne des couleurs du seau
*/
couleur couleur_courante(seau_couleur c) {
    if (c == NULL) {
        return init_couleur(0, 0, 0);
    }
    int courante[3] = {0}; // Passage par des entiers (8 octets) pour faire la moyenne, car la somme des 'char' dépassera probablement 256
    int nombre_couleur_rgb = 0;
    while (c != NULL) {
        courante[0] += c->contenu.rouge;
        courante[1] += c->contenu.vert;
        courante[2] += c->contenu.bleu;
        nombre_couleur_rgb += 1;
        c = c->suivant;
    }
    couleur cour = init_couleur(courante[0]/nombre_couleur_rgb, courante[1]/nombre_couleur_rgb, courante[2]/nombre_couleur_rgb);
    return cour;   
}

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne l'opacité courante d'un seau, obtenu en faisant la moyenne des opacités du seau
*/
opacite opacite_courante(seau_opacite o) {
    if (o == NULL) {
        return 255;
    }
    int courante = 0;
    int nombre_opacite = 0;
    while (o != NULL) {
        courante += o->contenu;
        nombre_opacite += 1;
        o = o->suivant;
    }
    opacite cour = courante/nombre_opacite;
    return cour;
}

/*
@requires: NEANT
@assigns: NEANT
@ensures: Retourne le pixel courant d'un seau de couleur et d'opacité
*/
pixel pixel_courant_futur(seau_couleur c, seau_opacite o) {
    pixel pix;
    pix.p_opacite = opacite_courante(o);
    pix.p_couleur = couleur_courante(c);
    pix.p_couleur.rouge = pix.p_couleur.rouge * pix.p_opacite / 255;
    pix.p_couleur.vert = pix.p_couleur.vert * pix.p_opacite / 255;
    pix.p_couleur.bleu = pix.p_couleur.bleu * pix.p_opacite / 255;
    return pix;
}
