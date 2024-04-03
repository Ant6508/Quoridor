

#ifndef __PARTIE_H__
#define __PARTIE_H__

#include "MatriceCases.h"
#include "TableauDynamiqueMur.h"
struct Board{
    TableauDynamiqueMur* tabdMur = nullptr;
    MatriceCases* Cases = nullptr;
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
        Partie();
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
        /*fonction qui vérifie si le string est valide pour un coup avec regex*/

        coup coupofString(const string s) const;
        /*Précondition: le string représentant un coup est valide (le coup peut lui être injouable pour l'un des joueurs par contre)*/
        /*Postcondition: retourne le coup correspondant au string, de type RIEN si string invalide*/

        void afficherCoup(const coup& c) const;

        bool coupValide(const coup& c, const Pion& joueur) const;
        /*un coup est valide ssi : il est de type deplacement et que le deplacement est valide ou que c est un mur et que le mur est valide*/
        /*Résultat: True si valide false sinon*/

        void jouerCoup(const coup& c, Pion& joueur) ;
        /*Précondition: Le coup est valide*/
        
        void afficherJoueur(const Pion& joueur) const;

        void afficherPartie(const bool verboseCases) const; /*VerboseCases permet d'afficher les cases du board ou non*/

        /*fonctions pour la fin de partie*/
        bool partieTerminee() const;
        bool gagnant(const TypeOccupant joueur) const;

        void jouerConsole();


};

#endif