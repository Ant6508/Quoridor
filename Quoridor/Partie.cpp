
#include <iostream>
#include <string>
#include <stdlib.h>
#include "vec2.h"
#include <assert.h>
#include "TableauDynamiqueMur.cpp"  
#include "MatriceCases.cpp"
#include "Partie.h"

using namespace std;

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
    delete board.Cases;
    delete board.tabdMur;
    board.Cases = NULL;
    board.tabdMur = NULL;
};

void Partie::initPions(){

    joueur1.ID = TypeOccupant::J1; /*On doit ici specifier typeoccupant::*/
    joueur2.ID = TypeOccupant::J2;

    int milieu = taille/2;
    vec2<int> pos1(0, milieu);
    vec2<int> pos2(taille-1, milieu);

    joueur1.caseCourrante = board.Cases->getCase(pos1);
    joueur2.caseCourrante = board.Cases->getCase(pos2);

    board.Cases->SetCaseOccupant(pos1,TypeOccupant::J1);
    board.Cases->SetCaseOccupant(pos2,TypeOccupant::J2);

};

Mur * Partie::getMursbyDir(Direction dir) const{
    /*fonction renvoyant une liste des murs en  fonction du type en parametre*/
    Mur * murs = new Mur[board.tabdMur->taille_utilisee];
    int j = 0;
    for (int i = 0; i < board.tabdMur->taille_utilisee; i++)
    {
        Mur m = board.tabdMur->valeurIemeElement(i);
        if(m.dir == dir){
            murs[j] = m;
            j++;
        }
    }
    return murs;
};

coup Partie::coupofString(string s) const{
    /*fonction qui renvoie un coup a partir d une chaine de caractere*/
    coup c;
    if(s[0] == 'D'){
        c.type = DEPLACEMENT;
        int nposx = stoi(s.substr(1,1));
        int nposy = stoi(s.substr(2,1));
        c.newpos = vec2<int>(nposx,nposy);
    }
    else if(s[0] == 'M'){
        c.type = MUR;
        Mur m;
        
        int Tailx = stoi(s.substr(1,1));
        int Taily = stoi(s.substr(2,1));
        int Headx = stoi(s.substr(3,1));
        int Heady = stoi(s.substr(4,1));

        m.Tail = vec2<int>(Tailx,Taily);
        m.Head = vec2<int>(Headx,Heady);
        m.dir = (m.Tail.x == m.Head.x) ? VERTICAL : HORIZONTAL; /*on determine la direction du mur*/
        c.mur = m;

    }
    else{
        c.type = RIEN;
    }
    return c;
};

void Partie::afficherCoup(coup c) const{
    /*fonction qui affiche un coup*/
    if(c.type == DEPLACEMENT){
        printf("Deplacement en %d %d\n", c.newpos.x, c.newpos.y);
    }
    else if(c.type == MUR){
        printf("Mur de %d %d a %d %d\n", c.mur.Tail.x, c.mur.Tail.y, c.mur.Head.x, c.mur.Head.y);
    }
    else{
        printf("Rien\n");
    }
};


bool Partie::murValide(Mur m) const {
    
    /*un mur est valide ssi : il ne sort pas du board et qu il nest pas sur un autre mur et qu il ne bloque pas le chemin d un joueur*/

    /*1)verifier si il ne sort pas de du board*/
    if ( m.Head.max() > taille)
    {printf("sort du board\n");
        return false;}

    /*2)verifier si il ne chevauche pas un autre mur*/
    for (int i = 0; i < board.tabdMur->taille_utilisee; i++)
    {
        Mur m2 = board.tabdMur->valeurIemeElement(i);
        if(m/m2) 
        {printf("chevauche le mur: ");
            board.tabdMur->afficherElement(i);
            return false;}
    };
    /*3)verifier si il ne bloque pas le chemin d un joueur
    Configuration en x opposé (gauche vs doite) 
    on veut regarder si */


    /*a coder*/


    return true;
};

bool Partie::rencontreMur(const Pion& joueur, Mur m, vec2<int> newpos) const{
    
    if(m.dir == VERTICAL){
        bool b1 = joueur.caseCourrante.position.x+1 == m.Tail.x == newpos.x;
        bool b2 = joueur.caseCourrante.position.x == m.Tail.x == newpos.x+1;
        bool adj = b1 || b2;

        bool ycompri = m.Tail.y <= joueur.caseCourrante.position.y && joueur.caseCourrante.position.y <= m.Head.y;
       
        if(adj && ycompri) return true;
    }
    else if(m.dir == HORIZONTAL){
        bool b1 = joueur.caseCourrante.position.y+1 == m.Tail.y == newpos.y;
        bool b2 = joueur.caseCourrante.position.y == m.Tail.y == newpos.y+1;
        bool adj = b1 || b2;

        bool xcompri = m.Tail.x <= joueur.caseCourrante.position.x && joueur.caseCourrante.position.x <= m.Head.x;
        
        if(adj && xcompri) return true;
    }
   

    return false;
};


bool Partie::deplacementValide(Pion& joueur, vec2<int> newpos) const{
    /*precondition : newpos est une case adjacente a la poistion du joueur*/
    /*un deplacement est valide ssi : il ne sort pas du board et qu il ne rencontre pas un mur*/

    assert(abs(joueur.caseCourrante.position.x - newpos.x) + abs(joueur.caseCourrante.position.y - newpos.y) == 1); /*on verifie que newpos est bien une case adjacente a la position du joueur*/
    
    Direction dirDeplacement = (newpos.x == joueur.caseCourrante.position.x) ? VERTICAL : HORIZONTAL;

    /*1)verifier si il ne sort pas de du board*/
    if ( newpos.max() > taille || newpos.min() < 0)
    {printf("sort du board\n");
        return false;}

    /*2)verifier si il ne rencontre pas un mur : si dir == VERTICAL on regarde seulement les murs horizontaux et vice versa*/
    for(int i = 0; i < board.tabdMur->taille_utilisee; i++){
        Mur m = board.tabdMur->valeurIemeElement(i);
        if(m.dir == dirDeplacement) continue;
        if(rencontreMur(joueur,m,newpos)) return false;
    }
    return true;
};

void Partie::deplacerPion (Pion& joueur, vec2<int> newpos){
    board.Cases->SetCaseOccupant(joueur.caseCourrante.position,TypeOccupant::Vide); /*On met vide sur la case courrante*/
    joueur.caseCourrante = board.Cases->getCase(newpos); /*On change la case courrante du joueur*/
    board.Cases->SetCaseOccupant(newpos,joueur.ID); /*on met a jour la board*/
    
};

void Partie::jouerCoup(coup c){
    /*on joue un coup en fonction de son type*/
    if(c.type == DEPLACEMENT){
        bool possible = deplacementValide(joueur1, c.newpos);
        if(possible){
            deplacerPion(joueur1, c.newpos);
        }
        else{
            printf("deplacement invalide\n");
        }
    }
    else if(c.type == MUR){
        if(murValide(c.mur)){
            if (board.tabdMur->concatenerMur(c.mur)) printf("Mur concaténé\n");
            else board.tabdMur->ajouterElement(c.mur);
        }
        else{
            printf("Mur invalide\n");
        }
    }
    else{
        printf("coup invalide\n");
    }
};

