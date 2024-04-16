/*Classe de la mainFrame qui est parente de tous les widgets visibles nottaments les boutons et le panel du board
elle n'a jamais accès à un objet Partie
*/


#pragma once
#include <wx/wx.h>
#include <wx/overlay.h>
#include <wx/dcclient.h>
#include "Base/Partie.h"    


class MainFrame : public wxFrame {

public:
    MainFrame(const wxString& title);

    int sizecase = 75;
    int epaissTraits = 2;

    wxPanel* panelMain;
    /*panel acceuillant tous les widgets */
    /*au final MainFrame n'aura qu'un fils wxFrame direct qui prendra donc tout l'espace dispo*/

    wxPanel* panelBoard;
    /*panel du board de jeu*/

    wxPanel* panelJeu;
    /*panel des infos du jeu*/

    wxButton* initPartieButton;
    
    wxButton* JouerCoup_Button;

    wxButton* afficherMurs_Button;

    wxButton* fermerMenu_Button;


    wxStaticText* CoupCourant_StaticText;

    wxStaticText** Joueurs_StaticText;

    wxTextCtrl* InputCoup_TextCtrl;


    /*fonctions membres*/


    /*Fonctions exclusive pour l'UI -> tous les murs et joueurs sont ont en const*/
    void initBoardUI(const int taille);

    bool afficherImagePNG(const wxString& filename, const vec2<int> pos) const ;
    /*Postcondition : retourne true si l'image est bien affichée*/

    void effacerPion(const vec2<int> pos) const;
    /*Algo : dessine un rectangle gris à la position pos*/ 

    void deplacerPion(const vec2<int> oldpos, const vec2<int> newpos  ,const Pion& joueur) const;
    /*Algo : efface le pion à oldpos et dessine le pion à newpos*/

    void afficherMur(const Mur& m, wxColour c, int epaisseur) const;
    /*Algo : dessine un mur sur le board*/

    void surlignerCase(const vec2<int> pos,const wxColour c) const;
    /*affiche la case pos en bleu*/

    void afficherCoupBoard(const Coup& c,const Pion& joueur) const;
    /*deplace l'icône du joueur ou place un mur le board*/
};