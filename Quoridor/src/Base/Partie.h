

#ifndef __PARTIE_H__
#define __PARTIE_H__

#include "MatriceCases.h"
#include "TableauDynamiqueMur.h"
struct Board{
    TableauDynamiqueMur* tabdMur;
    MatriceCases* Cases;
};
struct Pion{
    Case caseCourante; 
    TypeOccupant ID = TypeOccupant::Vide;
    int nbMur = 5;
};

enum class typeCoup {DEPLACEMENT, MUR, RIEN};

struct coup{
    typeCoup type = typeCoup::RIEN;
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
        bool murValide(const Mur& m) const;
        bool rencontreMur(const Pion& joueur, const Mur& m, const vec2<int> newpos) const;

        /*fonctions pour les deplacements*/
        bool deplacementValide(const Pion& joueur,const vec2<int> pos) const;
        void deplacerPion(Pion& joueur, const vec2<int> pos); /*fonction type setter donc pas de const*/

 
        /*fonctions pour les coups*/
        bool stringValide(const string s) const;
        coup coupofString(const string s) const;
        void afficherCoup(const coup& c) const;

        bool coupValide(coup c, const Pion& joueur) const;
        void jouerCoup(const coup& c, Pion& joueur) ;
        
        void afficherJoueur(const Pion& joueur) const;
        void afficherPartie(const bool verboseCases) const; /*VerboseCases permet d'afficher les cases du board ou non*/

        /*fonctions pour la fin de partie*/
        bool partieTerminee() const;
        bool gagnant(const TypeOccupant joueur) const;

        void jouerConsole();


};

#endif