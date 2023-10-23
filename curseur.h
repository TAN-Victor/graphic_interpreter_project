/*  
    FICHIER: curseur.h
    
    DESCRIPTION: Interface déclarant les fonctions et structures de donnees sur les positions et les directions
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#ifndef CURSEUR_H
#define CURSEUR_H
#include <stdlib.h>

struct _position {
    int abscisse;
    int ordonnee;
};
typedef struct _position position;

enum _direction {nord, est, sud, ouest};
typedef enum _direction direction;

typedef struct _cellule_position *cellule_position;
struct _cellule_position{
    position position_attente;
    cellule_position suivant;
    cellule_position precedent;
};

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie une position initialisée en (0, 0)
*/
position initialiser_position();

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie une direction initialisée vers l'est
*/
direction initialiser_direction();

/*
@requires: Un entier 'cote' strictement positif et une position telle que l'abscisse et l'ordonnée soient entre [0; cote - 1] 
@assigns:  NEANT
@ensures: Renvoie la nouvelle position après avancée d'un pixel selon la direction
*/
position avancer(position pos, direction dir, int cote);

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie la nouvelle direction après rotation horaire
*/
direction tourner_horaire(direction dir);

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Renvoie la nouvelle direction après rotation anti-horaire
*/
direction tourner_antihoraire(direction dir);

/*
@requires: Un pointeur valide vers le maillon le plus récent d'une liste chaînée de position
            Attention, il n'y a pas de vérification sur la position, donc la fonction  qui utilisera 'cons'
             (pour ce projet, uniquement 'remplissage') devra s'assurer que la position soit valide (pour la taille du côté de l'image)
@assigns:  La liste chaînée pointée
@ensures: Ajoute en en-tête de la liste chaînée la nouvelle position;
*/
void cons(position position_attente, cellule_position *suivant);

/*
@requires: Un pointeur valide vers le maillon le plus ancien d'une liste chaînée de position
@assigns:  La liste chaînée pointée
@ensures: Retire le plus ancien maillon de la liste chaînée et décale le curseur d'entrée vers le nouveau maillon le plus ancien.
*/
void retirer(cellule_position *curseur);

#endif