/*  
    FICHIER: curseur.c
    
    DESCRIPTION: Implémentation des fonctions et structures de données sur les positions et les directions
            Nécessite l'interface 'curseur.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#include "curseur.h"

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie une position initialisée en (0, 0)
*/
position initialiser_position() {
    position pos;
    pos.abscisse = 0;
    pos.ordonnee = 0;
    return pos;
}

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie une direction initialisée vers l'est
*/
direction initialiser_direction() {
    direction dir;
    dir = est;
    return dir;
}

/*
@requires: Un entier 'cote' strictement positif et une position telle que l'abscisse et l'ordonnée soient entre [0; cote - 1] 
@assigns:  NEANT
@ensures: Renvoie la nouvelle position après avancée d'un pixel selon la direction
*/
position avancer(position pos, direction dir, int cote) {
    switch(dir) {
        case nord: pos.ordonnee = (pos.ordonnee - 1 + cote) % cote; break;
        case est: pos.abscisse = (pos.abscisse + 1) % cote; break;
        case sud: pos.ordonnee = (pos.ordonnee + 1) % cote; break;
        case ouest: pos.abscisse = (pos.abscisse - 1 + cote) % cote; break;
        /* Nous remarquons que A % B renvoie l'entier entre [-B; B], donc pour avoir le reste de la division euclidienne, 
        il faut se placer entre [0; B], donc nous ajoutons '+ cote' quand une coordonnée peut être négative.*/
        default: exit(1); // En théorie, exit n'arrive jamais
    }
    return pos;
}

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie la nouvelle direction après rotation horaire
*/
direction tourner_horaire(direction dir) {
    switch(dir) {
        case nord: return est;
        case est: return sud;
        case sud: return ouest;
        case ouest: return nord;
        default: exit(1);
    }
}

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie la nouvelle direction après rotation anti-horaire
*/
direction tourner_antihoraire(direction dir) {
    switch(dir) {
        case nord: return ouest;
        case est: return nord;
        case sud: return est;
        case ouest: return sud;
        default: exit(1);
    }
}

/*
@requires: Un pointeur valide vers le maillon le plus récent d'une liste chaînée de position
            Attention, il n'y a pas de vérification sur la position, donc la fonction  qui utilisera 'cons'
             (pour ce projet, uniquement 'remplissage') devra s'assurer que la position soit valide (pour la taille du côté de l'image)
@assigns:  La liste chaînée pointée
@ensures: Ajoute en en-tête de la liste chaînée la nouvelle position;
*/
void cons(position position_attente, cellule_position *premier) {
    cellule_position nouveau = malloc(sizeof(struct _cellule_position));
    nouveau->position_attente = position_attente;
    nouveau->suivant = (*premier);
    nouveau->precedent = NULL;
    if ((*premier) != NULL) {
        (*premier)->precedent = nouveau;
    }
    (*premier) = nouveau;
    return;
}

/*
@requires: Un pointeur valide vers le maillon le plus ancien d'une liste chaînée de position
@assigns:  La liste chaînée pointée
@ensures: Retire le plus ancien maillon de la liste chaînée et décale le curseur d'entrée vers le nouveau maillon le plus ancien.
*/
void retirer(cellule_position *curseur) {
    cellule_position tmp = *curseur;
    if ((*curseur)->precedent == NULL) {
        (*curseur) = tmp->precedent;
        free(tmp);
        return;
    }
    (*curseur) = tmp->precedent;
    (*curseur)->suivant = NULL;
    free(tmp);
    return;



}