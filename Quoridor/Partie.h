
#include "TableauDynamiqueMur.h"
#include "MatriceCases.h"

struct Board{
    TableauDynamiqueMur* MurH;
    MatriceCases* Cases;
};
struct Pion{
    Case* caseCourrante;
    TypeOccupant ID;
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
        Pion joueur1;
        Pion joueur2;
        int coupCourant;    
        int taille;


        Partie(int taille);
        ~Partie();

        void initPions();

        bool murValide(Mur m) const;
        bool coupValide(coup c, Pion joueur) const;
        void jouerCoup(coup c);
        void annulerCoup(coup c);

        bool partieTerminee();
        bool gagnant(TypeOccupant joueur);

        


};