#include "MatriceCases.h"
#include "TableauDynamiqueMur.h"

struct Board{
    TableauDynamiqueMur* tabdMur;
    MatriceCases* Cases;
};
struct Pion{
    Case caseCourrante; //pointe vers la case du tableau de cases
    TypeOccupant ID = TypeOccupant::Vide;
    int nbMur = 5;
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

        void initPions();/*Déclare et positionne sur le board les 2 pions*/

        /*fonctions pour les murs*/
        Mur* getMursbyDir(const Direction dir) const;
        Mur* getMursbyX(const int x) const;
        Mur* getMursbyY(const int y) const;
        bool murValide(const Mur& m) const;
        bool rencontreMur(const Pion& joueur, const Mur& m, const vec2<int> newpos) const;

        /*fonctions pour les deplacements*/
        bool deplacementValide(const Pion& joueur,const vec2<int> pos) const;
        void deplacerPion(Pion& joueur, const vec2<int> pos); /*fonction type setter donc pa de const*/

 
        /*fonctions pour les coups*/
        coup coupofString(const string s) const;
        void afficherCoup(const coup& c) const;

        //bool coupValide(coup c, const Pion& joueur) const;
        void jouerCoup(const coup& c, Pion& joueur) ;
        void annulerCoup(coup c);
        
        void afficherJoueur(const Pion& joueur) const;
        void afficherPartie(const bool verboseCases) const; /*VerboseCases permet d'afficher les cases du board ou non*/

        /*fonctions pour la fin de partie*/
        bool partieTerminee() const;
        bool gagnant(const TypeOccupant joueur) const;

        void jouerConsole();


};