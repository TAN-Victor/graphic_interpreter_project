/*  
    FICHIER: outils.c
    
    DESCRIPTION: Implémentation des fonctions de modification de << l'état de la machine >>
            Nécessite l'interface 'outils.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#include "outils.h"

/*
@requires: Un etat initialisé, un buffer 'buf' de taille 512 accessible 
@assigns: L'état pointé
@ensures: Pour chaque lettre dans le buffer, une action est realisée sur l'état de la machine
*/
void modification(etat *etat_m, char buf[]) {
    calque ca;
    calque cb;
    int cote = etat_m->cote;
    for (int z = 0; z < 512; z += 1) {
        switch(buf[z]) {
            case 'n': etat_m->seau_coul = cons_seau_c(init_couleur(0, 0, 0), etat_m->seau_coul); break;
            case 'r': etat_m->seau_coul = cons_seau_c(init_couleur(255, 0, 0), etat_m->seau_coul); break;
            case 'g': etat_m->seau_coul = cons_seau_c(init_couleur(0, 255, 0), etat_m->seau_coul); break;
            case 'b': etat_m->seau_coul = cons_seau_c(init_couleur(0, 0, 255), etat_m->seau_coul); break;
            case 'y': etat_m->seau_coul = cons_seau_c(init_couleur(255, 255, 0), etat_m->seau_coul); break;
            case 'm': etat_m->seau_coul = cons_seau_c(init_couleur(255, 0, 255), etat_m->seau_coul); break;
            case 'c': etat_m->seau_coul = cons_seau_c(init_couleur(0, 255, 255), etat_m->seau_coul); break;
            case 'w': etat_m->seau_coul = cons_seau_c(init_couleur(255, 255, 255), etat_m->seau_coul); break;
            
            case 't': etat_m->seau_opac = cons_seau_o(0, etat_m->seau_opac); break;
            case 'o': etat_m->seau_opac = cons_seau_o(255, etat_m->seau_opac); break;
            
            case 'i': free_seaux(&(etat_m->seau_coul), &(etat_m->seau_opac)); break;
            
            case 'v': etat_m->courant = avancer(etat_m->courant, etat_m->direction, etat_m->cote); break;
            case 'h': etat_m->direction = tourner_horaire(etat_m->direction); break;
            case 'a': etat_m->direction = tourner_antihoraire(etat_m->direction); break;
            
            case 'p': marque_position(etat_m); break;
            case 'l': tracer_ligne(etat_m); break;
            case 'f': remplissage(etat_m); break;
            
            case 's': new_calque(&(etat_m->pile_calques)); break;
            
            case 'e':  if (etat_m->pile_calques.taille < 2) {break;} // Ne fait rien s'il n'y a pas au moins 2 calques    
                       ca = etat_m->pile_calques.calque[etat_m->pile_calques.taille - 1];
                       cb = etat_m->pile_calques.calque[etat_m->pile_calques.taille - 2];
                       fusion_calques(ca, cb, cote);
                       liberer_calque_top(&(etat_m->pile_calques)); break;
            
            case 'j':  if (etat_m->pile_calques.taille < 2) {break;} // Ne fait rien s'il n'y a pas au moins 2 calques
                       ca = etat_m->pile_calques.calque[etat_m->pile_calques.taille - 1];
                       cb = etat_m->pile_calques.calque[etat_m->pile_calques.taille - 2];
                       decoupe_calques(ca, cb, cote);
                       liberer_calque_top(&(etat_m->pile_calques)); break;
            
            default: break;
        }
    }
}

