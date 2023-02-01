/**
* @file main.cpp
* @author Anase MEZOUARI et ADEL SABAA Ashraf
* @version 1.0 20/12/2021
*/


#include <iostream>
#include "Demineur.h"

using namespace std;

/** @brief fonction principale*/
int main() {

    unsigned int commande; // création de la variable pour determiner quelle commande executer
    demineur d; // création de la structure qui abritera toutes les données


    cin >> commande; // on recupere le numero de la commande a éxécuté à travers un fichier ou du cmd

    switch (commande) { // on regarde la valeur de la variable commande pour savoir qu'elle fonction lancé

        case 1:probleme(d, true); break; // si la variable nombre vaut 1, on lance la fonction probleme

        case 2:grille(d); break; // si la variable nombre vaut 2, on lance la fonction grille

        case 3:win_game(d); break; // si la variable nombre vaut 3, on lance la fonction win_game

        case 4:lose_game(d); break; // si la variable nombre vaut 4, on lance la fonction lose_game

        case 5:nouveau_coup(d); break; // si la variable nombre vaut 5, on lance la fonction nouveau_coup

        default:break; // sinon on sort du switch directement

    }
    detruire(d);// on désalloue toutes les données allouées dynamiquement
}