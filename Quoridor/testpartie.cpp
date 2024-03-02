
#include <iostream>
#include <stdlib.h>
#include "Partie.cpp"

#include <assert.h>

using namespace std;


int main(){


    /*Partie p(9); test de la creation de la partie et de concatenation de mur si possible

    Mur m1;
    Mur m2;

    m2.Tail = vec2<int>(1,1);
    m2.Head = vec2<int>(1,3);
    m2.dir = VERTICAL;

    p.board.tabdMur->ajouterElement(m2);

    m1.Tail = vec2<int>(0,0);
    m1.Head = vec2<int>(2,0 );
    m1.dir = HORIZONTAL;

    bool valide = p.murValide(m1);
    
    printf(valide ? "true\n" : "false\n");

    p.board.tabdMur->concatenerMur(m1);
    p.board.tabdMur->afficher();

    return 0;*/


    /*test de la creation dune partieest deplacement de pions sur le board
    printf("t");
    Partie p(8);
     
    p.initPions();
    p.deplacerPion(p.joueur1, vec2<int>(1,4));
    p.deplacerPion(p.joueur2, vec2<int>(7,4));
    p.board.Cases->afficher();
    printf(p.joueur1.caseCourrante.position.x == 1 ? "true\n" : "false\n");*/
   


    /*test de la creation dune partie et deplacement de pions sur le board et regardant si c est possible
    Partie p(5);
    p.initPions();
    p.board.Cases->afficher();
    
    p.deplacerPion(p.joueur1, vec2<int>(1,2));


    Mur m1;
    m1.Tail = vec2<int>(1,0);
    m1.Head = vec2<int>(1,2);
    m1.dir = VERTICAL;

    p.board.tabdMur->ajouterElement(m1);
    p.board.tabdMur->afficher();

    bool rencontre = p.rencontreMur(p.joueur1, m1, vec2<int>(0,3));
    printf(rencontre ? "true\n" : "false\n");*/


    /*test coupfostring
    Partie p(5);
    
    string s = "D12";
    string s2 = "M1012";
    string s3 = "M0121";

    coup c = p.coupofString(s);
    coup c2 = p.coupofString(s2);
    coup c3 = p.coupofString(s3);

    p.afficherCoup(c);
    p.afficherCoup(c2);
    p.afficherCoup(c3);

    p.board.tabdMur->ajouterElement(c2.mur);
    bool valide = p.murValide(c3.mur);
    printf(valide ? "true\n" : "false\n");
    p.board.tabdMur->ajouterElement(c3.mur);
    p.board.tabdMur->afficher();
    
    return 0;*/

    /*test rencontre mur*/
    Partie p(5);
    
    

}