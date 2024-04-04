#pragma once
#include <wx\wx.h>
#include <wx/bitmap.h>
#include <wx/image.h> 
#include <string>
#include "MainFrame.h"



class App : public wxApp
{
public:
	bool OnInit();


	Partie* partie; 

	bool partieInit = false;
	/*Bool de l'initialisation de la partie*/

	bool voisinsSelected = false;
	/*Bool de l'affichage des cases voisines*/

	bool murSelected = false;
	Mur murTemp;

	MainFrame* mainFrame;
	/*main wxframe*/


	void initPartieUI(const int taille);
	/*Init l'interface graphique du jeu et du board*/
	/*init du board dans MainFrame*/

	void initJeuUI(const int taille);
	/*Init les infos du jeu*/

	void updatejeuUI();
	/*Update les textes en fonction de la partie en cours*/

	void jouerCoupBoard(const string s);
	/*joue le coup s sur le board*/
	/*Update l'ui et la partie*/

	void afficherVoisinesPion(const Pion& joueur) const;
	/*Affiche les cases voisines du joueur ssi il peut s'y déplacer*/

	void effacerVoisinesPion(const Pion& joueur) const;
	/*efface les cases voisines*/


	/*fonctions liéss aux différents event utilisateur possibles*/

	void onButtonInitPartie(wxCommandEvent& event);
	/*Fonction du bouton initPartie*/

	void onButtonJouerCoup(wxCommandEvent& event);
	/*Fonction de l'event du bouton jouerCoup*/

	void onleftClickBoard(wxMouseEvent& event);
	/*fonctions appelés pour tout click gauche sur panelboard*/
	/*permet de déplacer le joueur sur les cases disponibles*/

	void onRightClickBoard(wxMouseEvent& event);
	/*fonctions appelés pour tout click droit sur panelboard*/
	/*permet de poser un mur à la souris avec un faux drag and drop*/

	void onKeyPressBoard(wxKeyEvent& event);
	/*Fonction de l'event du clavier*/

	void onMouseMoveBoard(wxMouseEvent& event);
	/*Fonction de l'event du mouvement de la souris sur panelboard*/

	void onEventPlacerMur();
	/*Fonction de l'event placerMur*/

	/*fonctions debug pour afficher (wxmessagebox) les infos des murs*/
	void wxAfficherInfoMur(unsigned int indice) const;

	void wxAfficherInfotdm(wxCommandEvent& event) const;

	void wxAfficherMurtemp() const;
	/*Fonction pour le debug*/

	void wxAfficherInfoPion(const Pion& joueur) const;

	void OnExit(wxCloseEvent& event);
};