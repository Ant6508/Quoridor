/*Module MatriceCases
Ce module permet de gérer le tableau 2D de cases du plateau de jeu
Il permet de visualiser les cases, de les modifier et de récupérer les voisins d'une case
*/

#ifndef MATRICECASES_H__
#define MATRICECASES_H__


#include <iostream>
#include <stdlib.h>
#include "vec2.h"
using namespace std;

enum class TypeOccupant
/*Permet de savoir quel joueur se trouve sur la case*/
{
    Vide=-1,J1=0,J2=1
     /*Pour jouer à 3/4 ou plus il faudra agrandir cette énumération*/
};

struct Case
/*Représente une case du board*/
{
    bool valide = true;
    vec2<int> position; 
    TypeOccupant Occupant = TypeOccupant::Vide ;
};

class MatriceCases
{
public:

    /* données membres */
    int Taille;
    Case **Cases; //Tableau carré 2D de cases de taille Taille

    /*constructeurs & destructeur*/
    MatriceCases(int taille); // Constructeur par défaut
    ~MatriceCases();

    /*fonctions membres*/

    /*Setters*/
    void SetCaseOccupant(vec2<int> pos, const TypeOccupant occupant);
    /*Précondition: la position ne sort pas du board*/
    /*Postcondition: la case à la position pos a pour occupant occupant*/

    /*Getters*/
    Case getCase(const vec2<int> pos) const; // Renvoie la case à la position pos
    /*Précondition: la position ne sort pas du board*/
    /*Postcondition: la case renvoyée est valide et est une copie de la case du board*/

    Case* GetVoisins(const Case &c) const; // Renvoie les voisins de la case c
    /*Précondition: la case c est valide*/
    /*Postcondition: le tableau renvoyé contient 4 cases, les cases non valides sont marquées comme telles*/

    /*Fonctions d'affichage text*/
    void afficherCase(const Case &c) const; // Affiche la case c
    void afficher() const; // Affiche la matrice de cases

};


#endif