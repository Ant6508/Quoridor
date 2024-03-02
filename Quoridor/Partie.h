

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


        /*fonctions pour les murs*/
        Mur* getMursbyDir(const Direction dir) const;
        bool murValide(const Mur& m) const;
        bool rencontreMur(const Pion& joueur, const Mur& m, const vec2<int> newpos) const;

        /*fonctions pour les deplacements*/
        bool deplacementValide(const Pion& joueur,const vec2<int> pos) const;
        void deplacerPion(Pion& joueur, const vec2<int> pos); /*fonction type setter donc pa de const*/

 
        /*fonctions pour les coups*/
        coup coupofString(const string s) const;
        void afficherCoup(const coup& c) const;

        //bool coupValide(coup c, const Pion& joueur) const;
        void jouerCoup(const coup& c);
        void annulerCoup(coup c);
        
        bool partieTerminee() const;
        bool gagnant(const TypeOccupant joueur) const;


};