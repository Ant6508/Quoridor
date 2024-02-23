
#include <iostream>
#include <stdlib.h>
#include "vec2.h"
#include <assert.h>
#include "TableauDynamiqueMur.h"  
#include "MatriceCases.h"
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
    return true;
};


bool Partie::coupValide(coup c, Pion joueur) const{
    switch (c.type)
    {
    case DEPLACEMENT:
    //pos de la case d'arrivée
        vec2<int> newPos = c.pos;
        newPos = newPos + joueur.caseCourrante->position;
        // cas ou le joueur sort de la map

    }};

        