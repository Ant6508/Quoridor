
#include <iostream>
#include <stdlib.h>
#include "Partie.cpp"

#include <assert.h>

using namespace std;


int main(){


    Partie p(9);

    Mur m1;
    Mur m2;

    m2.Tail = vec2<int>(1,1);
    m2.Head = vec2<int>(1,3);

    p.board.MurH->ajouterElement(m2);

    m1.Tail = vec2<int>(0,2);
    m1.Head = vec2<int>(2,2);

    bool valide = p.murValide(m1);
    
    printf(valide ? "true\n" : "false\n");

}