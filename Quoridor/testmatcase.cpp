#include <iostream>
#include <stdlib.h>
#include "MatriceCases.cpp"

#include <assert.h>

using namespace std;

int main(){

    MatriceCases mc(9);


    vec2<int> pos(1,1);
    mc.SetCaseOccupant(pos,TypeOccupant::J1);
    Case *c = mc.GetCase(pos);
    mc.printCase(*c);
    mc.Print();
    return 0;
}