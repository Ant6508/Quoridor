#include <iostream>
#include <stdlib.h>
#include "MatriceCases.cpp"

#include <assert.h>

using namespace std;

int main(){

    MatriceCases mc(9);
    
    vec2<int> pos(0,1);
    mc.SetCaseOccupant(pos,TypeOccupant::J1);
    Case c = mc.getCase(pos);
    mc.printCase(c);

    Case *listevoisins;
    listevoisins = mc.GetVoisins(c);

    for (int i = 0; i < 4; i++)
    {
        mc.printCase(listevoisins[i]);
    }
    return 0;
}