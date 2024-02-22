
#include "TableauDynamiqueMur.h"
#include "MatriceCases.h"

struct Board{
    TableauDynamiqueMur MurH;
    MatriceCases Cases;
};

enum typeCoup {DEPLACEMENT, MUR, RIEN};

struct coup{
    typeCoup type;
    vec2<int> pos;
    Mur mur;

};

class Partie
{
    public:
        Board board;
        Pion J1;
        Pion J2;
        int coupCourant;


        Partie(int taille);
        ~Partie();

        bool coupValide(coup c);
        void jouerCoup(coup c);
        void annulerCoup(coup c);

        bool partieTerminee();
        bool gagnant(TypeOccupant joueur);



};