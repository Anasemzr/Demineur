/**
* @file Demineur.h
* @author Anase MEZOUARI et ADEL SABAA Ashraf
* @version 1.0 20/12/2021
*/



#ifndef _DEMINEUR_H
#define _DEMINEUR_H


/* @brief structure qui habritera toute les données traitées pendant le fonctionnement du programme */

struct demineur {

    int* probleme; //  pointeur qui stockera l'adresse d'un tableau de type int pour enrengistrer le probleme

    char* historiqueChar; // pointeur qui stockera l'adresse d'un tableau de type char pour enrengister les lettres de
                            // l'historique de coup

    int* historiqueInt; // pointeur qui stockera l'adresse d'un tableau de type int pour enrengister les nombres de
                        // l'historique de coup

    int nb_coup; // variable qui enrengistrera le nombre de coup dans l'historique de coup

    char* grilleMine;//pointeur qui stockera l'adresse d'un tableau char, pour enrengistrer toute les cases de la grille


};


void probleme(demineur& d, bool aleatoire); // affiche un probleme
void grille(demineur& d); // affiche une grille
void win_game(demineur& d); // affiche "game won" ou "game not won"
void lose_game(demineur& d);// affiche "game lose" ou "game not lose"
void nouveau_coup(demineur& d);// affiche un nouveau coup

int emplacement_aleatoire(demineur& d, int& taille_tableau); // créer et renvoie une case de bombe qui n'existe pas déjà
void historique_de_coup(demineur& d); // Lit et enrengistre un historique de coup
void barre(int& colonne);// affiche une barre de tiret dont la longueur depend du nombre de colonne (exemple=  '_____' )
char caractere(demineur& d, int& num_case);// renvoie le caractere a afficher dans une case pour une grille
char nombre_mine(demineur& d, int num_case);// renvoie le nombre de mine a proximité
bool partie_perdu(demineur& d);// Booléen qui renvoie vrai ou faux si la partie est perdu


void detruire(demineur& d);// désalloue toutes les structures allouées dynamiquement

#endif //_DEMINEUR_H
