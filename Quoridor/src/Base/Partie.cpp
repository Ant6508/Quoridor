
#include <iostream>
#include <string>
#include <stdlib.h>
#include "vec2.h"
#include <assert.h>
#include <regex>
#include "TableauDynamiqueMur.cpp"  
#include "MatriceCases.cpp"
#include "Partie.h"

using namespace std;

Partie::Partie()
{
    board.Cases = new MatriceCases(1);
    board.tabdMur = new TableauDynamiqueMur();
    coupCourant = 0;
    taille = 0;
};

Partie::Partie(int Taille)
{
    board.Cases = new MatriceCases(Taille);
    board.tabdMur = new TableauDynamiqueMur();

    coupCourant = 0;
    taille = Taille;
    initPions();
};

Partie::~Partie()
{


};

void Partie::initPions(){

    joueur1.ID = TypeOccupant::J1; /*On doit ici specifier typeoccupant::*/
    joueur2.ID = TypeOccupant::J2;

    int milieu = taille/2;
    vec2<int> pos1(0, milieu);
    vec2<int> pos2(taille-1, milieu);

    joueur1.caseCourante = board.Cases->getCase(pos1);
    joueur2.caseCourante = board.Cases->getCase(pos2);

    board.Cases->SetCaseOccupant(pos1,TypeOccupant::J1);
    board.Cases->SetCaseOccupant(pos2,TypeOccupant::J2);

};


bool Partie::stringValide(const string s) const
{
    std::regex patternDeplacement ("^D\\d\\d$"); //D01
    std::regex patternMur ("^M\\d\\d\\d\\d$"); //M1213

    return std::regex_match(s, patternDeplacement) || std::regex_match(s, patternMur);

}

coup Partie::coupofString(const string s) const{

    
    /*fonction qui renvoie un coup a partir d une chaine de caractere*/
    coup c;

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
    else{
        c.type = typeCoup::RIEN;
    }
    return c;
};

void Partie::afficherCoup(const coup& c) const{
    /*fonction qui affiche un coup*/
    if(c.type == typeCoup::DEPLACEMENT){
        printf("Deplacement en %d %d\n", c.newpos.x, c.newpos.y);
    }
    else if(c.type == typeCoup::MUR){
        printf("Mur de %d %d a %d %d\n", c.mur.Tail.x, c.mur.Tail.y, c.mur.Head.x, c.mur.Head.y);
    }
    else{
        printf("Rien\n");
    }
};


bool Partie::murValide(const Mur& m) const {
    
    /*un mur est valide ssi : il ne sort pas du board et qu il nest pas sur un autre mur et qu il ne bloque pas le chemin d un joueur
                            et que tx = hx ou ty=hy */

    /*1)verifier si il ne sort pas de du board*/
    if ( m.Head.max() > taille)
    {printf("sort du board\n");
        return false;}

    /*2)tx = hx ou ty=hy*/
    if(m.Tail.x != m.Head.x && m.Tail.y != m.Head.y) return false ;


    /*3)verifier si il ne chevauche pas un autre mur*/
    for (int unsigned i = 0; i < board.tabdMur->taille_utilisee; i++)
    {
        Mur m2 = board.tabdMur->valeurIemeElement(i);
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
    printf("dirDeplacement : %d\n", dirDeplacement);

    /* 1)verifier si un autre joueur est sur newpos*/
    if(board.Cases->getCase(newpos).Occupant != TypeOccupant::Vide) return false;

    /*2)verifier si il ne sort pas de du board*/
    if ( newpos.max() >= taille || newpos.min() < 0)
    {printf("sort du board\n");
        return false;}

    /*3)verifier si il ne rencontre pas un mur : si dir == VERTICAL on regarde seulement les murs horizontaux et vice versa*/
    for(int i = 0; i < board.tabdMur->taille_utilisee; i++){
        Mur m = board.tabdMur->valeurIemeElement(i);
        if(m.dir == dirDeplacement) continue;
        if(rencontreMur(joueur,m,newpos)) return false;
    }



    return true;
};

bool Partie::coupValide(const coup &c, const Pion& joueur) const
{
    /*un coup est valide ssi : il est de type deplacement et que le deplacement est valide ou que c est un mur et que le mur est valide*/
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
    board.Cases->SetCaseOccupant(joueur.caseCourante.position,TypeOccupant::Vide); /*On met vide sur la case courrante*/
    joueur.caseCourante = board.Cases->getCase(newpos); /*On change la case courrante du joueur*/
    board.Cases->SetCaseOccupant(newpos,joueur.ID); /*on met a jour la board*/
};

void Partie::jouerCoup(const coup& c, Pion& joueur){
    /*on joue un coup en fonction de son type*/

    if(!coupValide(c, joueur)) return;

    if(c.type == typeCoup::DEPLACEMENT){
        deplacerPion(joueur, c.newpos);
        coupCourant++;
    }
    else if(c.type == typeCoup::MUR && joueur.nbMur > 0){   
        if (board.tabdMur->concatenerMur(c.mur));
        else board.tabdMur->ajouterElement(c.mur);
        joueur.nbMur--;
        coupCourant++;
    }
};

void Partie::afficherJoueur(const Pion& joueur) const{
    printf("Joueur %d en %d %d ,nbmurs : %d\n", joueur.ID, joueur.caseCourante.position.x, joueur.caseCourante.position.y, joueur.nbMur);
};

void Partie::afficherPartie(const bool verboseCases) const{
    printf("Tour courant : %d\n", coupCourant);
    afficherJoueur(joueur1);
    afficherJoueur(joueur2);
    board.tabdMur->afficher();
    if(verboseCases) board.Cases->afficher();
};

bool Partie::gagnant(const TypeOccupant joueur) const {
    /*on regarde si un joueur a gagné*/

    if(joueur == TypeOccupant::J1){
        if (joueur1.caseCourante.position.x == taille-1) return true;}

    else if(joueur == TypeOccupant::J2){
        if (joueur2.caseCourante.position.x == 0) return true; }

    return false;
};

bool Partie::partieTerminee() const{
    /*on regarde si un joueur a gagné*/
    return gagnant(TypeOccupant::J1) || gagnant(TypeOccupant::J2);
};



void Partie::jouerConsole() {
    /*Lance une partie avec input console*/

    while(true){

        afficherPartie(false);

        char* s;
        scanf_s("%s", &s);
        

        if (s == "exit") break;
        coup c = coupofString(s);
        afficherCoup(c);

        if(c.type == typeCoup::RIEN) continue;

        if(coupCourant % 2 == 0){
            jouerCoup(c, joueur1);
        }
        else{
            jouerCoup(c, joueur2);
        }

        if(partieTerminee()){
            printf("Partie terminee\n");
            break;
        }
        coupCourant++;



    }
    
}