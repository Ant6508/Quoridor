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
    Mur m2;

    m2.Tail = vec2<int>(1,1);
    m2.Head = vec2<int>(1,3);
    
    m1.Tail = vec2<int>(0,2);
    m1.Head = vec2<int>(2,2);

    m2.dir = VERTICAL;
    m1.dir = HORIZONTAL;    

    tdm.ajouterElement(m1);
    tdm.ajouterElement(m2);

    if(m1/m2)
    {
        printf("Les murs se croisent\n");
    }
    else
    {
        printf("Les murs ne se croisent pas\n");
    }
   

    tdm.afficher(); 

    //faire une pause pour voir le resultat
    cout << "Appuyez sur une touche pour continuer" << endl;
    cin.get();



    return 0;


};