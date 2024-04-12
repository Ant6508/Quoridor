/*Comme Partie constitue la base du jeu: pas de printf hors des fonctions afficher...*/

#ifndef __PARTIE_H__
#define __PARTIE_H__

#include "TableauDynamiqueMur.h"

#include <string>
using namespace std;

enum class TypeOccupant
/*Permet de savoir quel joueur se trouve sur la case*/
{
    Vide=-1,J1=0,J2=1, J3=2, J4=3
};

struct Case
{/*Représente une case du board*/
    bool valide = true;
    vec2<int> position; 
};
struct Board{
    TableauDynamiqueMur tabdMur;
};
struct Pion{
    Case caseCourante; 
    TypeOccupant ID = TypeOccupant::Vide;
    int nbMur = 5;
};

enum class typeCoup {DEPLACEMENT, MUR, RIEN};

struct Coup{
    typeCoup type = typeCoup::RIEN;
    vec2<int> newpos;
    Mur mur;
};

class Partie
{
    public:

        /*Données membres publiques*/
        Board board;
        Pion* joueurs;
        int coupCourant;    
        int taille;
        int nbJoueurs=2;


        /*Fonctions membres publiques*/
        Partie();
        Partie(int taille);
        ~Partie();

        void initPions();/*Déclare et positionne sur le board les 2 pions*/
        TypeOccupant idOfPos(const vec2<int> pos) const;
        Pion& JoueurOfPos(const vec2<int> pos) const;
        /*Précondition: la position pos nest pas vide*/

        Pion& JoueurOfTour() const;

        /*fonctions pour les murs*/
        bool murValide(const Mur& m) const;
        bool rencontreMur(const Pion& joueur, const Mur& m, const vec2<int> newpos) const;

        /*fonctions pour les deplacements*/
        bool deplacementValide(const Pion& joueur,const vec2<int> pos) const;
        
        void deplacerPion(Pion& joueur, const vec2<int> pos); /*fonction type setter donc pas de const*/

        Case* GetVoisins(const Case &c) const; // Renvoie les voisins de la case c
        /*Précondition: la case c est valide*/
        /*Postcondition: le tableau renvoyé contient 4 cases, les cases non valides sont marquées comme telles*/

 
        /*fonctions pour les coups*/

        bool stringValide(const string coup_String) const;
        /*fonction qui vérifie si le string est valide pour un Coup avec regex*/

        Coup coupofString(const string coup_String) const;
        /*Précondition: le string représentant un Coup est valide (le Coup peut lui être injouable pour l'un des joueurs par contre)*/
        /*Postcondition: retourne le Coup correspondant au string, de type RIEN si string invalide*/

        void afficherCoup(const Coup& c) const;

        bool coupValide(const Coup& c, const Pion& joueur) const;
        /*un Coup est valide ssi : il est de type deplacement et que le deplacement est valide ou que c est un mur et que le mur est valide*/
        /*Résultat: True si valide false sinon*/

        void jouerCoup(const Coup& c, Pion& joueur) ;
        /*Précondition: Le Coup est valide*/
        
        void afficherJoueur(const Pion& joueur) const;

        void afficherPartie() const; 

        /*fonctions pour la fin de partie*/
        bool partieTerminee() const;
        bool gagnant(const TypeOccupant joueur) const;

        char * StringofPion(const Pion& p) const;

};

#endif