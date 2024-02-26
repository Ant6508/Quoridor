

struct Board{
    TableauDynamiqueMur* MurH;
    MatriceCases* Cases;
};
struct Pion{
    Case caseCourrante; //pointe vers la case du tableau de cases
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
        //bool coupValide(coup c, const Pion& joueur) const;
        void jouerCoup(coup c);
        void annulerCoup(coup c);
        void deplacerPion(Pion& joueur, vec2<int> pos);
        bool partieTerminee();
        bool gagnant(TypeOccupant joueur);


};