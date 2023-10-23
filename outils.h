/*  
    FICHIER: outils.h
    
    DESCRIPTION: Implémentation des fonctions de modification de << l'état de la machine >>
            Nécessite l'interface 'etat.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#ifndef OUTILS_H
#define OUTILS_H
#include "etat.h"

/*
@requires: Un etat initialisé, un buffer 'buf' de taille 512 accessible 
@assigns: L'état pointé
@ensures: Pour chaque lettre dans le buffer, une action est realisée sur l'état de la machine
*/
void modification(etat *etat_m, char buf[]);


#endif