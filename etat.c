/*  
    FICHIER: etat.c
    
    DESCRIPTION: Implémentation des fonctions et structures de données sur << l'état de la machine >> décrite dans l'enoncé
            Nécessite l'interface 'etat.h'
    
    AUTEUR: TAN Victor - 1A - ENSIIE
    
    DATE: 08/01/2023
*/

#include "etat.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
@requires: 'cote' strictement positif
@assigns: NEANT
@ensures: Renvoie un état de la machine initialisé
        Nous appelerons 'état' la structure de donnée composée:
            - d'une position courante
            - d'une position marquée
            - d'une direction
            - d'un seau de couleurs
            - d'un seau d'opacité
            - d'une pile de calques
            - d'un côté (taille en pixel du côté de l'image) 
*/
etat initialiser_etat(int cote) {
    etat tmp;
    tmp.courant = initialiser_position();
    tmp.marque = initialiser_position();
    tmp.direction = initialiser_direction();
    tmp.seau_coul = NULL;
    tmp.seau_opac = NULL;
    tmp.pile_calques = initialiser_pile(cote);
    tmp.cote = cote; // Déjà présent dans tmp.pile_calques mais plus lisible pour plus tard
    return tmp;
}

/*
@requires: Un pointeur valide
@assigns: L'état pointé
@ensures: Libère l'état
*/
void liberer_etat(etat *e) {
    int taille = e->pile_calques.taille;
    for (int i = 0; i < taille; i += 1) {
        liberer_calque_top(&(e->pile_calques));
    }
    free_seaux(&(e->seau_coul), &(e->seau_opac));
}

/*
@requires: Un pointeur valide
@assigns: L'état plointé
@ensures: Inscrit la position courante dans la position marquée
*/
void marque_position(etat *e) {
    e->marque = e->courant;
}

/*
@requires: Un état initialisé
@assigns: NEANT
@ensures: Affiche toutes les informations de l'état
*/
void print_etat(etat e) {
    printf("\n#######################\n");
    printf("Position: (%d, %d)\n", e.courant.abscisse, e.courant.ordonnee);
    printf("Marque: (%d, %d)\n", e.marque.abscisse, e.marque.ordonnee);
    printf("Taille pile: %d\n", e.pile_calques.taille);
    print_pile(e.pile_calques);
    print_seau_couleur(e.seau_coul);
    print_seau_opacite(e.seau_opac);
    fflush(stdout);
}

/*
@requires: Un pointeur valide, une position valide (coordonnées comprises entre [0; cote - 1] où cote est membre de l'état)
@assigns: Le pixel du sommet de la pile de calques correspondant à la position courante
@ensures: Modifie le-dit pixel selon le contenu des seaux
*/
void poser_pixel(etat *e, position pos) {
    pixel pixel_pose = pixel_courant_futur(e->seau_coul, e->seau_opac);
    int sommet = e->pile_calques.taille - 1;
    int i = pos.abscisse;
    int j = pos.ordonnee;
    e->pile_calques.calque[sommet][j][i] = pixel_pose;
}

/*
@requires: NEANT
@assigns:  NEANT
@ensures: Retourne le plus grand entier entre a et b
*/
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

/*
@requires: Un pointeur valide
@assigns: Les pixels du sommet de la pile de calques selon la position actuelle et la position marquee
@ensures: Modifie les pixels du sommet de la pile de calques entre la position actuelle et la position marquee; selon le contenu des seaux
*/
void tracer_ligne(etat *e) {
    int distance_absc = e->courant.abscisse - e->marque.abscisse;
    int distance_ord = e->courant.ordonnee - e->marque.ordonnee;
    int dist = max(abs(distance_absc), abs(distance_ord));
    int s = 1;
    if (distance_absc * distance_ord > 0 ) {
        s = 0;
    }
    int x = e->marque.abscisse * dist + (dist - s) / 2;
    int y = e->marque.ordonnee * dist + (dist - s) / 2;
    pixel futur = pixel_courant_futur(e->seau_coul, e->seau_opac);
    for (int i = 0; i < dist; i += 1) {
        e->pile_calques.calque[e->pile_calques.taille - 1][y/dist][x/dist] = futur;
        x += distance_absc;
        y += distance_ord;
    }
    poser_pixel(e, e->courant);
}

/*
@requires: Pixels initialisés
@assigns: NEANT
@ensures: Teste si deux pixels sont égaux en couleurs et en opacité
*/
int are_pixels_equal(pixel a, pixel b) {
    return (a.p_couleur.rouge == b.p_couleur.rouge && a.p_couleur.vert == b.p_couleur.vert && a.p_couleur.bleu == b.p_couleur.bleu && a.p_opacite == b.p_opacite);
}

/*
@requires: Un pointeur valide
@assigns: Les pixels du sommet de la pile de calques
@ensures: Transforme le pixel de la position actuelle ('ancien') si différent de la couleur qu'il faut déposer ('courant'). Puis, répétition sur le voisinage.
        Pas de récurrence; la fonction a été réadaptée. 
        Au lieu d'une pile d'appels, nous avons une liste chaînée des positions qu'il faut modifier.
        A chaque passage, nous regardons la plus ancienne position non-verifiée et nous ajoutons ou non ses voisins; la chaîne 'se vide' et 'se remplie' en 
        même temps. Une matrice des positions déjà vérifiée 'mat' est présente pour éviter de rajouter un voisin déjà présent dans la chaîne. 
*/
void remplissage(etat *etat_m) {
    int x = etat_m->courant.abscisse;
    int y = etat_m->courant.ordonnee;
    pixel ancien = etat_m->pile_calques.calque[etat_m->pile_calques.taille - 1][y][x];
    pixel courant = pixel_courant_futur(etat_m->seau_coul, etat_m->seau_opac);
    calque calq = etat_m->pile_calques.calque[etat_m->pile_calques.taille - 1];
    int cote = etat_m->cote;

    if (!are_pixels_equal(calq[y][x], courant)) {
        cellule_position pile = NULL;
        cons((position){x, y}, &pile);
        cellule_position dernier = pile;
        int **mat = calloc(cote, sizeof(int *));
        for (int i = 0; i < cote; i += 1) {
            mat[i] = calloc(cote, sizeof(int));
        }
        mat[y][x] = 1;


        while (dernier != NULL) {
            /*
                'dernier' est un pointeur vers le plus vieux maillon de la chaîne. La boucle s'arrête ssi la chaîne est vide, ie ssi 'dernier' pointe vers NULL;
                La fonction 'retirer' permet de retirer le plus vieux maillon et de modifier la position de 'dernier';
                Or, si aucun voisin ne peut être rajouté, la chaîne se réduira à ce moment, ce qui assure l'arrêt de la boucle.
            */
            int xm = dernier->position_attente.abscisse;
            int ym = dernier->position_attente.ordonnee;
            calq[ym][xm] = courant; // aurait pu être écrite après la vérification de ses voisins

            if (xm > 0 && are_pixels_equal(calq[ym][xm - 1], ancien) && mat[ym][xm - 1] == 0) { // voisin à l'ouest
                cons((position){xm - 1, ym}, &pile);
                mat[ym][xm - 1] = 1;    
            }
            if (ym > 0 && are_pixels_equal(calq[ym - 1][xm], ancien) && mat[ym - 1][xm] == 0) { // voisin au nord
                cons((position){xm, ym - 1}, &pile);
                mat[ym - 1][xm] = 1;
            }
            if (xm < cote - 1 && are_pixels_equal(calq[ym][xm + 1], ancien) && mat[ym][xm + 1] == 0) { // voisin à l'est
                cons((position){xm + 1, ym}, &pile);
                mat[ym][xm + 1] = 1;
            }
            if (ym < cote - 1 && are_pixels_equal(calq[ym + 1][xm], ancien) && mat[ym + 1][xm] == 0) { // voisin au sud
                cons((position){xm, ym + 1}, &pile);
                mat[ym + 1][xm] = 1;
            }
            retirer(&dernier);

        }
        for (int i = 0; i < cote; i += 1) {
            free(mat[i]);
        }
        free(mat);
    }
}

/*
@requires: 'cote' strictement positif et calques initialisés
@assigns: Le calque 'cb'
@ensures: Modifie le calque cb selon la formule cb[i][j].composante_x = cb[i][j].composante_x * (255 - ca[i][j].opacite) / 255 + ca[i][j].composante_x
         tel que i et j décrivent [0; cote - 1] et composante_x décrit les composantes de RGBA, pour fusioner les deux calques
         Le calque 'ca' n'est plus utile, nous nous assurerons qu'il soit libéré après l'exécution de cette fonction
*/
void fusion_calques(calque ca, calque cb, int cote) {
    for (int i = 0; i < cote; i += 1) {
        for (int j = 0; j < cote; j += 1) {
            opacite opa_ca = ca[i][j].p_opacite;
            cb[i][j].p_couleur.rouge = cb[i][j].p_couleur.rouge * (255 - opa_ca) / 255 + ca[i][j].p_couleur.rouge;
            cb[i][j].p_couleur.vert = cb[i][j].p_couleur.vert * (255 - opa_ca) / 255 + ca[i][j].p_couleur.vert;
            cb[i][j].p_couleur.bleu = cb[i][j].p_couleur.bleu * (255 - opa_ca) / 255 + ca[i][j].p_couleur.bleu;
            cb[i][j].p_opacite = cb[i][j].p_opacite * (255 - opa_ca) / 255 + ca[i][j].p_opacite; 
        }
    }
}

/*
@requires: 'cote' strictement positif et calques initialisés 
@assigns: Le calque 'cb'
@ensures: Modifie le calque cb selon la formule cb[i][j].composante_x = cb[i][j].composante_x * ca[i][j].opacite / 255
        tel que i et j décrivent [0; cote - 1] et composante_x décrit les composantes de RGBA, pour découper le calque 'cb' selon 'ca'
         Le calque 'ca' n'est plus utile, nous nous assurerons qu'il soit libéré après l'exécution de cette fonction
*/
void decoupe_calques(calque ca, calque cb, int cote) {
    for (int i = 0; i < cote; i += 1) {
        for (int j = 0; j < cote; j += 1) {
            opacite opa_ca = ca[i][j].p_opacite;
            cb[i][j].p_couleur.rouge = cb[i][j].p_couleur.rouge * opa_ca / 255;
            cb[i][j].p_couleur.vert = cb[i][j].p_couleur.vert * opa_ca / 255;
            cb[i][j].p_couleur.bleu = cb[i][j].p_couleur.bleu * opa_ca / 255;
            cb[i][j].p_opacite = cb[i][j].p_opacite * opa_ca / 255; 
        }
    }
}
