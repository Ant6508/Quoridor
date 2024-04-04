#include <iostream>
#include <stdlib.h>
#include "Partie.cpp"

#include <assert.h>
#include <regex>
#include <string>

#include "TableauDynamiqueMur.cpp"
#include "Partie.cpp"

using namespace std;

int main()
{
    Partie p(9);
    
    assert(p.JoueurOfTour().ID == TypeOccupant::J1);
    assert(p.taille == 9);
    assert(p.nbJoueurs == 2);
    assert(p.joueurs[0].caseCourante.position.x == 0);
    assert(p.joueurs[0].caseCourante.position.y == 4);
    assert(p.joueurs[1].caseCourante.position.x == 8);
    assert(p.joueurs[1].caseCourante.position.y == 4);

    assert(p.idOfPos(vec2<int>(0,4)) == TypeOccupant::J1);
    assert(p.idOfPos(vec2<int>(8,4)) == TypeOccupant::J2);
    assert(p.idOfPos(vec2<int>(4,4)) == TypeOccupant::Vide);

    string s = "D03";
    assert(p.stringValide(s));
    coup c = p.coupofString(s);
    assert(c.type == typeCoup::DEPLACEMENT);
    assert(c.newpos.x == 0);
    assert(c.newpos.y == 3);

    s = "M1213";
    assert(p.stringValide(s));
    c = p.coupofString(s);
    p.jouerCoup(c, p.JoueurOfTour());
    assert(c.type == typeCoup::MUR);
    assert(c.mur.dir == Direction::VERTICAL);

    string s2="M1315";
    coup c2=p.coupofString(s2);
    assert(c2.type == typeCoup::MUR);
    assert(p.board.tabdMur.concatenerMur(c2.mur));





}