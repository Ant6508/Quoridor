
#include <stdlib.h>
#include <assert.h>
#include <regex>
#include "TableauDynamiqueMur.cpp"  
#include "Partie.h"

using namespace std;

Partie::Partie(){};

Partie::Partie(int Taille)
{
    taille = Taille;
    initPions();
};

Partie::~Partie()
{
    delete [] joueurs;
    joueurs = nullptr;
};

void Partie::initPions(){

    int milieu = taille/2;

    joueurs = new Pion[nbJoueurs];
    for(int i = 0; i < nbJoueurs; i++){
        joueurs[i].caseCourante.position = vec2<int>(milieu*(i==2||i==3)+(taille-1)*(i==1),milieu*(i==0||i==1) + (taille-1)*(i==3));
        joueurs[i].ID = (TypeOccupant)i;
    }
};

TypeOccupant Partie::idOfPos(const vec2<int> pos) const
{
    for(int i = 0; i < nbJoueurs; i++){
        if(joueurs[i].caseCourante.position == pos) return joueurs[i].ID;
    }
    return TypeOccupant::Vide;
};

Pion& Partie::JoueurOfPos(const vec2<int> pos) const
{
    assert(idOfPos(pos) != TypeOccupant::Vide);
    for(int i = 0; i < nbJoueurs; i++){
        if(joueurs[i].caseCourante.position == pos) return joueurs[i];
    }
};

Pion& Partie::JoueurOfTour() const
{
    return joueurs[coupCourant % nbJoueurs];
};

bool Partie::stringValide(const string s) const
{
    std::regex patternDeplacement ("^D\\d\\d$"); //D01
    std::regex patternMur ("^M\\d\\d\\d\\d$"); //M1213

    return std::regex_match(s, patternDeplacement) || std::regex_match(s, patternMur);
}

Coup Partie::coupofString(const string s) const{
    /*fonction qui renvoie un Coup a partir d une chaine de caractere*/
    Coup c;

    if(!stringValide(s)){
        c.type = typeCoup::RIEN;
        return c;
    }
    
    if(s[0] == 'D'){
        c.type = typeCoup::DEPLACEMENT;
        int nposx = stoi(s.substr(1,1));
        int nposy = stoi(s.substr(2,1));
        c.newpos = vec2<int>(nposx,nposy);
    }
    else if(s[0] == 'M'){
        c.type = typeCoup::MUR;
        Mur m;
        
        int Tailx = stoi(s.substr(1,1));
        int Taily = stoi(s.substr(2,1));
        int Headx = stoi(s.substr(3,1));
        int Heady = stoi(s.substr(4,1));

        m.Tail = vec2<int>(Tailx,Taily);
        m.Head = vec2<int>(Headx,Heady);
        m.dir = (m.Tail.x == m.Head.x) ? Direction::VERTICAL : Direction::HORIZONTAL; /*on determine la direction du mur*/
        c.mur = m;
    }
    else c.type = typeCoup::RIEN;
        
    return c;
};

void Partie::afficherCoup(const Coup& c) const{
    /*fonction qui affiche un Coup*/
    if(c.type == typeCoup::DEPLACEMENT){
        printf("Deplacement en %d %d\n", c.newpos.x, c.newpos.y);
    }
    else if(c.type == typeCoup::MUR){
        printf("Mur de %d %d a %d %d\n", c.mur.Tail.x, c.mur.Tail.y, c.mur.Head.x, c.mur.Head.y);
    }
    else{
        printf("Coup Rien\n");
    }
};

bool Partie::murValide(const Mur& m) const 
{
    /*un mur est valide ssi : il ne sort pas du board et qu il nest pas sur un autre mur et qu il ne bloque pas le chemin d un joueur
                            et que tx = hx ou ty=hy */

    /*1)verifier si il ne sort pas de du board*/
    if ( m.Head.max() > taille) return false;

    /*2)tx = hx ou ty=hy*/
    if(m.Tail.x != m.Head.x && m.Tail.y != m.Head.y) return false ;

    /*3)verifier si il ne chevauche pas un autre mur*/
    for (int unsigned i = 0; i < board.tabdMur.taille_utilisee; i++)
    {
        Mur m2 = board.tabdMur.valeurIemeElement(i);
        if(m/m2 || m2/m) return false;
    };
    
    return true;
};

bool Partie::rencontreMur(const Pion& joueur, const Mur& m, const vec2<int> newpos) const{
    
    if(m.dir == Direction::VERTICAL){
        bool b1 = joueur.caseCourante.position.x+1 == m.Tail.x && m.Tail.x == newpos.x;
        bool b2 = joueur.caseCourante.position.x == m.Tail.x  && m.Tail.x == newpos.x+1;
        bool adj = b1 || b2;

        bool ycompri = m.Tail.y <= joueur.caseCourante.position.y && joueur.caseCourante.position.y < m.Head.y;
       
        if(adj && ycompri) return true;
    }
    else if(m.dir == Direction::HORIZONTAL){
        bool b1 = joueur.caseCourante.position.y+1 == m.Tail.y && m.Tail.y == newpos.y;
        bool b2 = joueur.caseCourante.position.y == m.Tail.y && m.Tail.y == newpos.y+1;
        bool adj = b1 || b2;

        bool xcompri = m.Tail.x <= joueur.caseCourante.position.x && joueur.caseCourante.position.x < m.Head.x;
        
        if(adj && xcompri) return true;
    }
   

    return false;
};

bool Partie::deplacementValide(const Pion& joueur, vec2<int> newpos) const{
    /*precondition : newpos est une case adjacente a la poistion du joueur*/
    /*un deplacement est valide ssi : il ne sort pas du board et qu il ne rencontre pas un mur et qu un autre joeuur est sur newpos*/

    if( ( abs(joueur.caseCourante.position.x - newpos.x) + abs(joueur.caseCourante.position.y - newpos.y) ) != 1) return false; /*on verifie que newpos est bien une case adjacente a la position du joueur (distance de manhattan = 1)*/

    Direction dirDeplacement = (newpos.x == joueur.caseCourante.position.x) ? Direction::VERTICAL : Direction::HORIZONTAL;

    /* 0)verifier si il ne sort pas du board*/
    if(newpos.max() >= taille || newpos.min() < 0) return false;

    /* 1)verifier si un autre joueur est sur newpos donc newpos ne peut pas etre lancienne case*/
    if(idOfPos(newpos) != TypeOccupant::Vide) return false;

    /*3)verifier si il ne rencontre pas un mur : si dir == VERTICAL on regarde seulement les murs horizontaux et vice versa*/
    for(unsigned int i = 0; i < board.tabdMur.taille_utilisee; i++){
        Mur m = board.tabdMur.valeurIemeElement(i);
        if(m.dir == dirDeplacement) continue;
        if(rencontreMur(joueur,m,newpos)) return false;
    }

    return true;
};

bool Partie::coupValide(const Coup &c, const Pion& joueur) const
{
    /*un Coup est valide ssi : il est de type deplacement et que le deplacement est valide ou que c est un mur et que le mur est valide*/
    if(c.type == typeCoup::DEPLACEMENT){
        return deplacementValide(joueur, c.newpos);
    }
    else if(c.type == typeCoup::MUR){
        return murValide(c.mur);
    }
    else{
        return false;
    }
};

void Partie::deplacerPion (Pion& joueur, const vec2<int> newpos)
{
    joueur.caseCourante.position = newpos;
};

Case* Partie::GetVoisins(const Case &c) const
{
    if(!c.valide) return nullptr;

    Case *voisins = new Case [4];

    //Voisin de droite
    vec2<int> tempPos = vec2<int>(1+ c.position.x, c.position.y);

    if (c.position.x < taille - 1) voisins[0].position = tempPos;
    else voisins[0].valide = false;
    
    //Voisin du haut
    tempPos = vec2<int>(c.position.x, -1+ c.position.y);

    if (c.position.y > 0) voisins[1].position = tempPos;
    else voisins[1].valide = false;

    //Voisin de gauche
    tempPos = vec2<int>(c.position.x-1, c.position.y);
    
    if (c.position.x > 0) voisins[2].position = tempPos;
    else voisins[2].valide = false;

    //Voisin du bas
    tempPos = vec2<int>(c.position.x, 1+ c.position.y);

    if (c.position.y < taille - 1) voisins[3].position = tempPos;
    else voisins[3].valide = false;

    return voisins;
}

void Partie::jouerCoup(const Coup& c, Pion& joueur)
{
    /*on joue un Coup en fonction de son type*/
    if(!coupValide(c, joueur)) return;

    if(c.type == typeCoup::DEPLACEMENT){
        deplacerPion(joueur, c.newpos);
        coupCourant++;
    }
    else if(c.type == typeCoup::MUR && joueur.nbMur > 0){   
        if (board.tabdMur.concatenerMur(c.mur));
        else board.tabdMur.ajouterElement(c.mur);
        joueur.nbMur--;
        coupCourant++;
    }
};

void Partie::afficherJoueur(const Pion& joueur) const{
    printf("Joueur %d en (%d %d) ,nbmurs : %d\n", (int)joueur.ID, joueur.caseCourante.position.x, joueur.caseCourante.position.y, joueur.nbMur);
};

void Partie::afficherPartie() const{
    printf("Tour courant : %d\n", coupCourant);
    for(int i = 0; i < nbJoueurs; i++){
        afficherJoueur(joueurs[i]);
    }
    board.tabdMur.afficher();
    
};

bool Partie::gagnant(const TypeOccupant joueur) const {
    /*on regarde si un joueur a gagné*/

    return true;
};

bool Partie::partieTerminee() const{
    /*on regarde si un joueur a gagné*/
    return gagnant(TypeOccupant::J1) || gagnant(TypeOccupant::J2);
};


char* Partie::StringofPion(const Pion& p) const{
    char* s = new char[100];
    sprintf_s(s, 100, "Joueur %d en %d %d ,nbmurs : %d\n", (int)p.ID, p.caseCourante.position.x, p.caseCourante.position.y, p.nbMur );
    return s;
};

