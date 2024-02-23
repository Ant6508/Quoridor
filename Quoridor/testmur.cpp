/*
benchtest pour la classe TableauDynamiqueMur
*/


#include <iostream>
#include <stdlib.h>
#include "TableauDynamiqueMur.cpp"

#include <assert.h>

using namespace std;

int main(){

    TableauDynamiqueMur tdm;
    Mur m1;
    m1.Tail = vec2<int>(1,1);
    m1.Head = vec2<int>(1,2);
    m1.dir = VERTICAL;
    tdm.ajouterElement(m1);

    Mur m2;
    m2.Tail = vec2<int>(1,2);
    m2.Head = vec2<int>(2,2);
    m2.dir = HORIZONTAL;

    tdm.concatenerMur(m2);
   

    tdm.afficher(); 

    //faire une pause pour voir le resultat
    cout << "Appuyez sur une touche pour continuer" << endl;
    cin.get();



    return 0;


};