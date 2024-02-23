
#include <iostream>
#include <stdlib.h>
#include "vec2.h"
using namespace std;

//operateur + pour vec2
vec2<int> operator+(const vec2<int> &v1, const vec2<int> &v2)
{
    return vec2<int>(v1.x + v2.x, v1.y + v2.y);
}

enum TypeOccupant
{
    Vide=-1,J1=0,J2=1
};

struct Case
{
    /* data */
    vec2<int> position; 
    TypeOccupant Occupant;

};



class MatriceCases
{
private:
    /* data */
public:

    /* données membres */
    int Taille;
    Case **Cases; //Tableau 2D de cases


    /* fonctions membres */
    MatriceCases(int taille); // Constructeur par défaut
    MatriceCases(); // Constructeur par défaut avec taille=8
    ~MatriceCases();


    void SetCaseOccupant(vec2<int> pos, TypeOccupant occupant); // Modifie l'occupant de la case à la position pos
    Case *GetCase(vec2<int> pos) const; // Renvoie la case* à la position pos
    Case** GetVoisins(const Case &) const; // Renvoie les voisins de la case c

    void Print() const; // Affiche la matrice de cases

};


