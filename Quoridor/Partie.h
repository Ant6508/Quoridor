

struct Board{
    TableauDynamiqueMur* tabdMur;
    MatriceCases* Cases;
};
struct Pion{
    Case caseCourrante; //pointe vers la case du tableau de cases
    TypeOccupant ID;
};

enum typeCoup {DEPLACEMENT, MUR, RIEN};

struct coup{
    typeCoup type;
    vec2<int> newpos;
    Mur mur;

};

class Partie
{
    public:

        /*Données membres publiques*/
        Board board;
        Pion joueur1;
        Pion joueur2;
        int coupCourant;    
        int taille;


        /*Fonctions membres publiques*/
        Partie(int taille);
        ~Partie();

        void initPions();
 
        coup coupofString(string s) const;
        void afficherCoup(coup c) const;

        Mur* getMursbyDir(Direction dir) const;
        bool murValide(Mur m) const;
        bool rencontreMur(const Pion& joueur, Mur m, vec2<int> newpos) const;

        bool deplacementValide(Pion& joueur, vec2<int> pos) const;
        void deplacerPion(Pion& joueur, vec2<int> pos);

        //bool coupValide(coup c, const Pion& joueur) const;
        void jouerCoup(coup c);
        void annulerCoup(coup c);
        
        bool partieTerminee();
        bool gagnant(TypeOccupant joueur);


};