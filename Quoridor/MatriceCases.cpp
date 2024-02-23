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

            Cases[i][j].Occupant = Vide;
        }
    }
}

MatriceCases::MatriceCases()
{
    Taille = 9; //Taille par défaut
    MatriceCases(Taille);
}

MatriceCases::~MatriceCases()
{
    for (int i = 0; i < Taille; i++)
    {
        delete[] Cases[i];
    }
    delete[] Cases;
    Cases = NULL;

}

void MatriceCases::SetCaseOccupant(vec2<int> pos, TypeOccupant occupant)
{
    Cases[pos.x][pos.y].Occupant = occupant;
}


Case *MatriceCases::GetCase(vec2<int> pos) const
{
    return &Cases[pos.x][pos.y];
}


Case** MatriceCases::GetVoisins(const Case & c) const { // 

    //Renvoie les voisins de la case c
    //On stock les voisins depuis la droite puis sens trigo
    //NULL si au bord

    Case **voisins = new Case *[4];

    //Voisin de droite
    if (c.position.x < Taille - 1)
    { voisins[0] = GetCase(c.position + vec2<int>(1, 0));}
    else
    {voisins[0] = NULL;}     

    //Voisin du bas
    if (c.position.y > 0)
    { voisins[1] = GetCase(c.position + vec2<int>(0, -1));}
    else
    {voisins[1] = NULL;}

    //Voisin de gauche
    if (c.position.x > 0)
    { voisins[2] = GetCase(c.position + vec2<int>(-1, 0));}
    else
    {voisins[2] = NULL;}

    //Voisin du haut
    if (c.position.y < Taille - 1)
    { voisins[3] = GetCase(c.position + vec2<int>(0, 1));}
    else
    {voisins[3] = NULL;}

    return voisins;

}


void MatriceCases::Print() const
{
    for (int i = 0; i < Taille; i++)
    {
        for (int j = 0; j < Taille; j++)
        {
            cout << Cases[i][j].Occupant << " ";
        }
        cout << endl;
    }
}



