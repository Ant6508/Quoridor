
#include <iostream>
#include <stdlib.h>
#include "vec2.h"
#include <assert.h>
#include "TableauDynamiqueMur.h"  
#include "MatriceCases.cpp"
#include "Partie.h"

using namespace std;

Partie::Partie(int taille)
{
    board.Cases = new MatriceCases(taille);
    board.MurH = new TableauDynamiqueMur();
    coupCourant = 0;
    taille = taille;
    initPions();
};

Partie::~Partie()
{
    delete board.Cases;
    delete board.MurH;
    board.Cases = NULL;
    board.MurH = NULL;
};

void Partie::initPions(){

    joueur1.ID = TypeOccupant::J1; /*On doit ici specifier typeoccupant::*/
    joueur2.ID = TypeOccupant::J2;

    joueur1.caseCourrante = board.Cases->GetCase(vec2<int>(0,4));
    joueur2.caseCourrante = board.Cases->GetCase(vec2<int>(8,4));

    board.Cases->SetCaseOccupant(vec2<int>(0,4),TypeOccupant::J1);
    board.Cases->SetCaseOccupant(vec2<int>(8,4),TypeOccupant::J2);

};

bool Partie::murValide(Mur m) const {
    
    /*un mur est valide ssi : il ne sort pas du board et qu il nest pas sur un autre mur et qu il ne bloque pas le chemin d un joueur*/

    /*1)verifier si il ne sort pas de du board*/
    if (m.Tail >= 0 || m.Head >= taille) 
    {printf("sort du board\n");
        return false;}

    /*2)verifier si il ne chevauche pas un autre mur*/
    for (int i = 0; i < board.MurH->taille_utilisee; i++)
    {
        Mur m2 = board.MurH->valeurIemeElement(i);
        if(m/m2) 
        {printf("mur chevauché: ");
            board.MurH->afficherElement(i);
            return false;}
    }
    /*3)verifier si il ne bloque pas le chemin d un joueur*/
    /*a coder*/
};


bool Partie::coupValide(coup c, const Pion& joueur) const{
    switch (c.type)
    {
    case DEPLACEMENT:
    //pos de la case d'arrivée
        vec2<int> newPos = c.pos;
        newPos = newPos + joueur.caseCourrante->position;
        // cas ou le joueur sort de la map

    }};

        