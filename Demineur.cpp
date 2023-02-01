/**
* @file Demineur.cpp
* @author Anase MEZOUARI et ADEL SABAA Ashraf
* @version 1.0 20/12/2021
*/

#pragma warning(disable : 4996)
#include "Demineur.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define MIN_NOMBRE 3 // Constante qui donne la taille minimum d'élément que contiendra le tableau "probleme"
#define LIGNE 0 // indice ou sera stocker le nombre de ligne pour le demineur dans le tableau "probleme"
#define COLONNE 1 // indice ou sera stocker le nombre de colonne pour le demineur dans le tableau "probleme"
#define BOMBE 2 // indice ou sera stocker le nombre de bombe pour le demineur dans le tableau "probleme"
#define ZERO 0 // valeur d'initialisation
#define ECART 1 // indice valant 1

using namespace std;



/** @brief fonction qui crée un probleme à partir du nombre de ligne,colonne,bombe et l'affiche
* @param[in]  la structure démineur
* @param[in] un booléen "aleatoire" qui permet de savoir si les bombes sont déjà donner ou doivent être créer aléatoirement
*/

void probleme(demineur& d, bool aleatoire)
{
    srand((unsigned int)time(NULL));  //initialisation du générateur pseudo-aléatoire

    int ligne, colonne, bombe;  //variables qui vont habriter les données nécessaires à la création d'un probleme
    cin >> ligne >> colonne >> bombe; // récolte des données

    d.probleme = new int[MIN_NOMBRE + bombe];  //on alloue dynamiquement un tableau à travers le pointeur "probleme"

    if (d.probleme == nullptr) { // si allocation impossible
        cout<<"Allocation mémoire impossible."<<endl;
        exit(1); //sortie de programme avec statut d’erreur
    }


    for (int caseTableau = ZERO; caseTableau < MIN_NOMBRE + bombe; ++caseTableau) // boucle for qui va permettre de parcourir
                                                                                // toutes les cases du tableau
    {
        if (caseTableau == LIGNE)d.probleme[caseTableau] = ligne;// la premiere case correspond au nombre de ligne
        else if (caseTableau == COLONNE)d.probleme[caseTableau] = colonne;// la deuxieme au nombre de colonne
        else if (caseTableau == BOMBE)d.probleme[caseTableau] = bombe;// la troisiéme au nombre de bombe

        else {//puis si le booléen "aleatoire" est vrai alors on tire les cases des bombes aléatoirement
                //   sinon on lis les cases des bombes qui nous sont donné
            if (aleatoire)d.probleme[caseTableau] = emplacement_aleatoire(d, caseTableau);
            else cin >> d.probleme[caseTableau];
        }

        if (aleatoire)cout << d.probleme[caseTableau] << " ";// puis on affiche la case qui a été enrengistré dans probleme
    }
}





/** @brief fonction qui produit une grille à partir d'un probleme et d'un historique de coups
* @param[in] la structure demineur
*/
void grille(demineur& d) {

    probleme(d, false);// on récolte le problème donné avec le booléen false car les bombes nous sont déjà donné
    historique_de_coup(d);// on récolte l'historique de coup

    int ligne_tableau = d.probleme[LIGNE];// on récupére le nombre de ligne
    int colonne_tableau = d.probleme[COLONNE];// on récupére le nombre de colonne
    int case_actuel = ZERO; // represente le numero de la case qui sera traitéé

    d.grilleMine = new char[d.probleme[LIGNE] * d.probleme[COLONNE]];

    cout << ligne_tableau << " " << colonne_tableau << endl; // on affiche comme prescrit dans les consignes le nombre
                                                                // de ligne et de colonne du tableau

    // on affiche ensuite la grille selon le nombre de ligne et de colonne
    for (int ligne = ZERO; ligne < ligne_tableau; ++ligne)
    {
        barre(colonne_tableau);// barre horizontale de '_' en fonction du nombre de colonne

        cout << endl;
        cout << "|";

        for (int colonne = 0;  colonne < colonne_tableau; ++colonne)
        {
            if(colonne<colonne_tableau-1)nombre_mine(d, (case_actuel + 1));// on regarde la case colonne suivante
            cout << " " << nombre_mine(d, case_actuel); // on affiche le caractère de la case qui a été traité
            cout << " |";
            ++case_actuel;// on incremente pour pouvoir travailler sur la prochaine case
        }
        cout << endl;

    }
    barre(colonne_tableau);// barre horizontale de '_' en fonction du nombre de colonne
}




/** @brief fonction qui détermine si une partie est gagnée à partir d’un problème et d’un historique de coups
* @param[in] le démineur
*/
void win_game(demineur& d) {
    probleme(d, false);// on récolte le problème donné avec le booléen false car les bombes nous sont déjà donné
    historique_de_coup(d);// on récolte l'historique de coup
    d.grilleMine = new char[d.probleme[LIGNE] * d.probleme[COLONNE]];// on créer le tableau grille dynamiquement

    // si la partie est perdu ou que le nombre de coup est différent du nombre de case ou il n'y a pas de bombe
    // alors la partie n'est pas gagner
    if (partie_perdu(d) || d.nb_coup != ((d.probleme[LIGNE] * d.probleme[COLONNE]) - d.probleme[BOMBE]))cout << "game not won";
    //sinon elle est gagner
    else cout << "game won";

}







/** @brief fonction qui détermine si une partie est perdue à partir d’un problème et d’un historique de coups
* @param[in] le démineur
*/
void lose_game(demineur& d) {
    probleme(d, false);// on récolte le problème donné avec le booléen false car les bombes nous sont déjà donné
    historique_de_coup(d);// on récolte l'historique de coup
    d.grilleMine = new char[d.probleme[LIGNE] * d.probleme[COLONNE]];// on créer le tableau grille dynamiquement

    // si aucun coup ne touche de bombe ou que aucun coup marque une case ou il n'y a pas de bombe
    // alors la partie n'est pas perdu
    if (!partie_perdu(d))cout << "game not lost";
    //sinon elle est perdue
    else cout << "game lost";
}





/** @brief fonction qui produit un nouveau coup à partir d'une grille
* @param[in] le démineur
*/
void nouveau_coup(demineur& d) {

    int ligne, colonne;
    cin >>ligne >> colonne;// on récupére le nombre de ligne et colonne

    int num_case=ZERO;// variable qui stockera la case qui sera traité a chaque tour de boucle
    char caractere_case;// variable qui stockera le caractere de la case lu

    int num_case_possible=ZERO;// nombre de case ou il est possible de jouer un coup
    int* tableau_case_possible;
    tableau_case_possible= new int[ligne*colonne];// tableau qui repertorie l'indice des cases qui pourront être jouer

    int reglage=ECART;// afin de lire correctement l'indice de la case un ecart sera soustrait a la valeur num_case

    while(num_case<ligne*(colonne+ECART))// tant que l'indice de la case traité ne correpond pas a la dernière case
                                            // du tableau
    {

        cin>>caractere_case;// lecture de la case actuellement traité

        if (caractere_case=='.'){// si la case correspond à '.' alors c'est une case qui peut être jouer
            tableau_case_possible[num_case_possible]=num_case-reglage; // on la met dans dans le tableau
            ++num_case_possible;// on incremente l'indice
        }

        if (caractere_case == '|'){// si la case correspond à '|' alors ça veut dire qu'on change de case
            ++num_case;// on incremente l'indice de la case
            if(num_case%(colonne+1)==0)++reglage;// et si on passe à la ligne suivante alors on incremente l'ecart d'indice
        }

    }




    char coup[3]="MD";// "MD" correspond à "M" pour masquer et "D" pour démasquer
    srand((unsigned int)time(NULL));
    int nb_aleatoire = rand() % (num_case_possible);// on tire au hasard une case qui peut être jouer
    int lettre_aleatoire = rand() % 2; // on tire au hasard une lettre sois masquer ou démasquer

    cout<<coup[lettre_aleatoire]<<tableau_case_possible[nb_aleatoire];// on affiche le tirage aléatoire de la lettre et du nombre
    delete []tableau_case_possible; // enfin on désalloue le tableau qui stocker les cases potentiellement jouables

}


/** @brief fonction qui permet de ne pas avoir plusieurs mines à un même emplacement
* @param[in] le démineur
* @param[in] le tour
*/
int emplacement_aleatoire(demineur& d, int& taille_tableau) {

    bool emplacement_inconnu = false; // variable booléen qui determinera si le nouveau nombre crée est "inconnu" dans le probleme ou pas
    int emplacement_aleatoire; // la variable qui stockera le nouveau nombre créer aleatoirement

    while (!emplacement_inconnu) // boucle qui tant que (nombre_inconnu != false) continue de tourner donc tant qu'on a pas trouver une bombe a une place inexistante
    {
        emplacement_aleatoire = rand() % ((d.probleme[0]) * (d.probleme[1])); // tire au sort un nombre qui existe dans les bornes de la grille du demineur
        emplacement_inconnu = true;// on met la valeur true pour la variable car pour l'instant elle est nouvelle et inconnu

        for (int num_bombe = MIN_NOMBRE; num_bombe < taille_tableau; ++num_bombe)// boucle qui va commencer a partir de la place des bombe dans le tableau probleme et qui va s'incrementer au fur et a mesure du nombre de bombe
        {
            if (d.probleme[num_bombe] == emplacement_aleatoire) {
                emplacement_aleatoire = false; // si la place de la bombe creer existe deja  alors la valeur du booléen de nombre incconnu passe a false car le nombre n'est dopnc pas inconnu
            }
        }
    }
    return emplacement_aleatoire; // quand on sortira de la boucle on aura donc une nouvelle position ou il n'y a aucune bombe
}








/** @brief fonction qui stockera l'historique de coup
* @param[in] le démineur
*/
void historique_de_coup(demineur& d) {
    //variables qui vont habriter les données nécessaires à la création d'un probleme
    cin >> d.nb_coup;// on récolte le nombre de coup qui sera donné

    d.historiqueInt = new int[d.nb_coup];// on alloue dynamiquement le tableau qui stockera l'indice des cases qui devront être jouer
    d.historiqueChar = new char[d.nb_coup];// on alloue dynamiquement le tableau qui stockera la manière de jouer des cases qui devront être jouer

    if (d.historiqueChar == nullptr || d.historiqueInt == nullptr) { // si allocation impossible
        cout << "Allocation mémoire impossible" << endl;
        exit(1); //sortie de programme avec statut d’erreur
    }

    for (int nb_coup = ZERO; nb_coup < d.nb_coup; ++nb_coup)// boucle for qui stockera les données qui nou seront donner
    {
        cin >> d.historiqueChar[nb_coup];
        cin >> d.historiqueInt[nb_coup];
    }

}


/** @brief affiche une barre de '_'
* @param[in] la copie entier colonne
*/
void barre(int& colonne)
{
    cout << " ";

    for (int case_colonne = ZERO; case_colonne  < colonne; ++case_colonne )// boucle for qui va afficher le motif
                                                                            // "___ " x fois (ou x vaut la valeur de colonne)
    {
        cout << "___ ";

    }

}



/** @brief fonction qui
* @param[in] le démineur
* @param[in] un entier "y"
*/
char caractere(demineur& d, int& num_case)
{
    if (partie_perdu(d))// si la partie est perdu alors on affiche toute les bombes
    {
        for (int num_bombe = MIN_NOMBRE; num_bombe < MIN_NOMBRE + d.probleme[BOMBE]; ++num_bombe)
        {
            if (d.probleme[num_bombe] == num_case)return 'm';// si la case actuellement traité sois num_case
                                                                // correspond à l'emplacement d'une bombe alors on renvoie 'm'
        }
    }

    for (int j = ZERO; j < d.nb_coup; ++j)// on parcours ici les coups a jouer pour voir si la case actuel correspond à un des
                                        // coups de l'historique de coup
    {
        if (d.historiqueInt[j] == num_case && d.historiqueChar[j] == 'D')return d.grilleMine[num_case];// on affiche le nombre de mine à proximité


        else if (d.historiqueInt[j] == num_case && d.historiqueChar[j] == 'M')return 'x';// on affiche 'x' pour signifier que la case est marqué
    }

    // on retourne un espace si la prochaine case est vide
    if (d.grilleMine[num_case] == ' ')return d.grilleMine[num_case];

    if ((' ' == d.grilleMine[num_case - d.probleme[COLONNE]]) || (' ' == d.grilleMine[num_case + d.probleme[COLONNE]]) || (' ' == d.grilleMine[num_case + ECART]))return d.grilleMine[num_case];

    if (num_case % d.probleme[COLONNE] != ZERO)
    {
        if (' ' == d.grilleMine[num_case - ECART])return d.grilleMine[num_case];
    }

    // si aucune des conditions précédente est validé alors on retourne un '.' qui signifie que la case peut être jouer plus tard
    return '.';

}








/** @brief fonction qui
* @param[in] le démineur
* @param[in] un entier "y"
*/
char nombre_mine(demineur& d, int num_case)
{
    int compteur_bombe_proximite = ZERO;// compteur qui permettras de savoir si il y a une bombe a proximité
    char compteur[2] = ""; // variable qui nous permettras de transformer le compteur en caractere afin de le stocker et de l'écrire quand on le souhaite

    for (int num_bombe = MIN_NOMBRE; num_bombe < (MIN_NOMBRE + d.probleme[BOMBE]); ++num_bombe)// boucle for en fonction du nombre de bombe
    {
        if (d.probleme[num_bombe] == num_case - d.probleme[COLONNE]) { ++compteur_bombe_proximite; } // on verifie en haut de la case
        if (d.probleme[num_bombe] == num_case + d.probleme[COLONNE]) { ++compteur_bombe_proximite; }// on verifie a gauche de la case


        if (num_case % d.probleme[COLONNE] != ZERO)
        {
            if (d.probleme[num_bombe] == num_case - d.probleme[COLONNE] - ECART) { ++compteur_bombe_proximite; } // on verifie en haut à gauche de la case
            if (d.probleme[num_bombe] == num_case + d.probleme[COLONNE] - ECART) { ++compteur_bombe_proximite; } // on verifie en bas à gauche de la case
            if (d.probleme[num_bombe] == num_case - ECART) { ++compteur_bombe_proximite; }// on verifie à gauche de la case
        }

        if ((num_case + ECART) % d.probleme[COLONNE] != ZERO)
        {
            if (d.probleme[num_bombe] == num_case + ECART) { ++compteur_bombe_proximite; }// on verifie à droite de la case
            if (d.probleme[num_bombe] == num_case - d.probleme[COLONNE] + ECART) { ++compteur_bombe_proximite; }// on verifie en haut à droite de la case
            if (d.probleme[num_bombe] == num_case + d.probleme[COLONNE] + ECART) { ++compteur_bombe_proximite; }// on verifie en bas à droite de la case
        }

        sprintf(compteur, "%d", compteur_bombe_proximite);//on transforme le résultat int en char
        if (compteur[ZERO] == '0')d.grilleMine[num_case] = ' ';// si ce résultat vaut 0 alors on ajoute ' ' à la grille du démineur
        else d.grilleMine[num_case] = compteur[ZERO];// sinon on ajoute le nombre qu'on à trouver ( ici compteur[ZERO] car c'est une chaine de caractere est le nombre est stoker
                                                    // à la premiere place car le deuxieme élément est un '/0'
    }


    return caractere(d, num_case);// on renvoie le caractère qui sera afficher dans la fonction grille
}




/** @brief fonction qui détermine si une partie est perdu
* @param[in] le démineur
*/
bool partie_perdu(demineur& d)
{
    // initialisation des booléen
    bool mine_demasque = false;
    bool mine_masque = true;

    for (int num_coup = 0; num_coup < d.nb_coup; ++num_coup)// on parcourt tout l'historique de coup
    {
        if (d.historiqueChar[num_coup] == 'M' && !mine_masque)mine_masque = true;// on remet a chaque fois l'indice a true si il passe a false et
                                                                                    // si on rencontre un autre coup qui nous demande de masquer une case

        for (int case_probleme = MIN_NOMBRE; case_probleme < MIN_NOMBRE + d.probleme[2]; ++case_probleme)
        {
            if ((d.historiqueInt[num_coup] == d.probleme[case_probleme] && d.historiqueChar[num_coup] == 'D'))mine_demasque = true;// si on a demasquer une bombe
            if (d.historiqueChar[num_coup] == 'M' && d.historiqueInt[num_coup] == d.probleme[case_probleme]) mine_masque = false; // si la case masquer contenait bien une bombe
                                                                                                                                // alors met false et donc on a pas perdu
        }
    }
    return (mine_masque || mine_demasque);// retourne un ou logique  des 2 booléens qui represente chacun un type de coup
}




/** @brief fonction qui libère toute les données allouées dynamiquement
* @param[in] le démineur
*/
void detruire(demineur& d) {// on désalloue tout ce qui a été alloué durant le programme pour éviter les pertes de mémoires
    delete[]d.probleme;
    delete[]d.historiqueChar;
    delete[]d.historiqueInt;
    delete[]d.grilleMine;
}
