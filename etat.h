/*  
    FICHIER: etat.h
    
    DESCRIPTION: Interface déclarant les fonctions et structures de données sur << l'état de la machine >> décrite dans l'enoncé
            Nécessite les interfaces 'calques.h', 'seaux.h', 'curseur.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#ifndef ETAT_H
#define ETAT_H
#include "calques.h"
#include "seaux.h"
#include "curseur.h"
#define MAX_QUEUE 50000

struct _etat {
    position courant;
    position marque;
    direction direction;
    seau_couleur seau_coul;
    seau_opacite seau_opac;
    pile pile_calques;
    int cote;
};
typedef struct _etat etat;

/*
@requires: 'cote' strictement positif
@assigns: NEANT
@ensures: Renvoie un état de la machine initialisé
*/
etat initialiser_etat(int cote);

/*
@requires: Un pointeur valide
@assigns: L'état pointé
@ensures: Libère l'état
*/
void liberer_etat(etat *e);

/*
@requires: Un pointeur valide
@assigns: L'état plointé
@ensures: Inscrit la position courante dans la position marquée
*/
void marque_position(etat *e);

/*
@requires: Un état initialisé
@assigns: NEANT
@ensures: Affiche toutes les informations de l'état
*/
void print_etat(etat e);

/*
@requires: Un pointeur valide, une position valide (coordonnées comprises entre [0; cote - 1] où cote est membre de l'état)
@assigns: Le pixel du sommet de la pile de calques correspondant à la position courante
@ensures: Modifie le-dit pixel selon le contenu des seaux
*/
void poser_pixel(etat *e, position pos);

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Retourne le plus grand entier entre a et b
*/
int max(int a, int b);

/*
@requires: Un pointeur valide
@assigns: Les pixels du sommet de la pile de calques selon la position actuelle et la position marquee
@ensures: Modifie les pixels du sommet de la pile de calques entre la position actuelle et la position marquee; selon le contenu des seaux
*/
void tracer_ligne(etat *e);

/*
@requires: Pixels initialisés
@assigns: NEANT
@ensures: Teste si deux pixels sont égaux en couleurs et en opacité
*/
int are_pixels_equal(pixel a, pixel b);


/*
@requires: Un pointeur valide
@assigns: Les pixels du sommet de la pile de calques
@ensures: Transforme le pixel de la position actuelle ('ancien') si différent de la couleur qu'il faut déposer ('courant'). Puis, répétition sur le voisinage.
        Pas de récurrence; la fonction a été réadaptée. 
        Au lieu d'une pile d'appels, nous avons une liste chaînée des positions qu'il faut modifier.
        A chaque passage, nous regardons la plus ancienne position non-verifiée et nous ajoutons ou non ses voisins; la chaîne 'se vide' et 'se remplie' en 
        même temps. Une matrice des positions déjà vérifiée 'mat' est présente pour éviter de rajouter un voisin déjà présent dans la chaîne. 
*/
void remplissage(etat *etat_m);

/*
@requires: 'cote' strictement positif et calques initialisés
@assigns: Le calque 'cb'
@ensures: Modifie le calque cb selon la formule cb[i][j].composante_x = cb[i][j].composante_x * (255 - ca[i][j].opacite) / 255 + ca[i][j].composante_x
         tel que i et j décrivent [0; cote - 1] et composante_x décrit les composantes de RGBA, pour fusioner les deux calques
         Le calque 'ca' n'est plus utile, nous nous assurerons qu'il soit libéré après l'exécution de cette fonction
*/
void fusion_calques(calque ca, calque cb, int cote);

/*
@requires: 'cote' strictement positif et calques initialisés 
@assigns: Le calque 'cb'
@ensures: Modifie le calque cb selon la formule cb[i][j].composante_x = cb[i][j].composante_x * ca[i][j].opacite / 255
        tel que i et j décrivent [0; cote - 1] et composante_x décrit les composantes de RGBA, pour découper le calque 'cb' selon 'ca'
         Le calque 'ca' n'est plus utile, nous nous assurerons qu'il soit libéré après l'exécution de cette fonction
*/
void decoupe_calques(calque ca, calque cb, int cote);


#endif