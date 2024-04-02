#pragma once
#include <wx\wx.h>
#include "Base\Partie.h"
#include <wx/overlay.h>
#include <wx/dcclient.h>


class MainFrame : public wxFrame {

public:
    MainFrame(const wxString& title);

    int sizecase = 50;
    int epaissTraits = 2;

    wxPanel* panelMain;
    /*panel acceuillant tous les widgets */

    wxPanel* panelBoard;
    /*panel du board de jeu*/

    wxPanel* panelJeu;
    /*panel des infos du jeu*/

    /*textes du nombre de mur restants*/
    wxStaticText* J1MursStaticText;
    wxStaticText* J2MursStaticText;

    wxButton* initPartieButton;

    wxStaticText* CoupCourant_StaticText;
    wxStaticText* J1StaticText;
    wxStaticText* J2StaticText;

    wxTextCtrl* InputCoup_TextCtrl;
    wxButton* JouerCoup_Button;

    wxButton* placerMur_Button;

    wxButton* afficherMurs_Button;


    /*fonctions membres*/

    Partie* initPartie(const int taille);

    /*Fonctions exclusive pour l'UI -> tous les murs et joueurs sont ont en const*/
    void initBoardUI(const int taille);

    bool afficherImagePNG(const wxString& filename, const vec2<int> pos) const ;
    /*Postcondition : retourne true si l'image est bien affichée*/

    void initPionsUI(const int taille);
    /*Initialise les pions des joueurs sur le board*/

    void effacerPion(const vec2<int> pos) const;
    /*Algo : dessine un rectangle gris à la position pos*/ 

    void deplacerPion(const vec2<int> oldpos, const vec2<int> newpos  ,const Pion& joueur) const;
    /*Algo : efface le pion à oldpos et dessine le pion à newpos*/

    void afficherMur(const Mur, wxColour c, int epaisseur) const;
    /*Algo : dessine un mur sur le board*/

    void surlignerCase(const vec2<int> pos,wxColour c) const;
    /*affiche la case pos en bleu*/

    void afficherCoupBoard(const coup& c,const Pion& joueur) const;
    /*deplace l'icône du joueur ou place un mur le board*/


};