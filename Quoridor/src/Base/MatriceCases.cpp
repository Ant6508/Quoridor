#include "MatriceCases.h"

#include <iostream>
#include <stdlib.h>
#include "vec2.h"
#include <assert.h>

using namespace std;


MatriceCases::MatriceCases(int taille)
{
    assert(taille > 0);

    Taille = taille; //Taille par défaut
    Cases = new Case *[Taille];
    for (int i = 0; i < Taille; i++)
    {
        Cases[i] = new Case[Taille];
    }
    for (int i = 0; i < Taille; i++)
    {
        for (int j = 0; j < Taille; j++)
        {
            //creer le vec2 de coordonnées i,j sur la pile (renouvelé à chaque tour de boucle)
            vec2<int> pos(i, j);
            Cases[i][j].position = pos;
            Cases[i][j].Occupant = TypeOccupant::Vide;
        }
    }
}

MatriceCases::~MatriceCases()
{
    for (int i = 0; i < Taille; i++)
    {
        delete[] Cases[i];
        Cases[i] = NULL;
    }
    delete[] Cases;
    Cases = NULL;

}

void MatriceCases::SetCaseOccupant(const vec2<int> pos, const TypeOccupant occupant){
/*Fonction type setter qui change l'occupant d'une case*/
/*Précondition: la position ne sort pas du board*/

    assert(pos.max() < Taille && pos.min() >= 0);
    Cases[pos.x][pos.y].Occupant = occupant;
}

Case MatriceCases::getCase(const vec2<int> pos) const
{
    assert(pos.max() < Taille && pos.min() >= 0);
    return Cases[pos.x][pos.y];
}


Case* MatriceCases::GetVoisins(const Case &c) const 
{
    assert(c.valide);

    Case *voisins = new Case [4];
    Case CaseNonValide;
    CaseNonValide.valide = false;

    //Voisin de droite
    if (c.position.x < Taille - 1) voisins[0] = getCase(vec2<int>(1+ c.position.x, c.position.y));
    else (voisins[0] = CaseNonValide);

    //Voisin du haut
    if (c.position.y > 0) voisins[1] = getCase(vec2<int>(c.position.x, -1+ c.position.y));
    else (voisins[1] =CaseNonValide);

    //Voisin de gauche
    if (c.position.x > 0) voisins[2] = getCase(vec2<int>(-1+ c.position.x, c.position.y));
    else (voisins[2] = CaseNonValide);

    //Voisin du bas
    if (c.position.y < Taille - 1) voisins[3] = getCase(vec2<int>(c.position.x, 1+ c.position.y));
    else (voisins[3] = CaseNonValide);

    return voisins;

}
/*Fonctions d'affichage text*/

void MatriceCases::afficherCase(const Case &c) const
/*Fonction qui affiche les données d'une case*/
{
    if(!c.valide)
    {
        printf("Case : NULL\n");
        return;
    }
    printf("Case : (%d,%d) , Occupant : %d\n", c.position.x, c.position.y, c.Occupant);
}

void MatriceCases::afficher() const
/*Fonction qui affiche toutes les cases du board*/
{
    for (int i = 0; i < Taille; i++)
    {
        for (int j = 0; j < Taille; j++)
        {
            afficherCase(getCase(vec2<int>(i, j)));
        }
    }
}



