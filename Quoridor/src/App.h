#pragma once
#include <wx\wx.h>
#include <wx/bitmap.h>
#include <wx/image.h> 
#include <string>
#include "MainFrame.h"



class App : public wxApp
{
public:
	/*Données membres*/
	Partie* partie=nullptr;
	/*Partie en cours*/
	/* * sur un objet Partie sur le tas*/

	bool partieInit = false;
	/*Bool de l'initialisation de la partie*/

	bool voisinsSelected = false;
	/*Bool les cases voisines sont elles affichées*/

	bool murSelected = false;
	/*Bool de la pose de mur*/

	Mur murTemp;
	/*Mur temporaire pour une possible pose*/

	MainFrame* mainFrame=nullptr;
	/*main wxframe*/

	/*Fonctions membres*/

	bool OnInit();
	/*Fonction d'initialisation de l'application et point d'entré pour wxwidgets*/

	void initPartieUI(const int taille);
	/*Init l'interface graphique du jeu et du board*/
	/*init du board dans MainFrame*/

	void initJeuUI(const int taille);
	/*Init les infos du jeu*/

	void initPionsUI();
	/*Init les pions sur le board*/

	void updatejeuUI();
	/*Update les textes en fonction de la partie en cours*/

	void jouerCoupBoard(const string coupString);
	/*joue le coup s sur le board si c'est permit */
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

	void onLeftClickBoard(wxMouseEvent& event);
	/*fonctions appelés pour tout click gauche sur panelboard*/
	/*permet de déplacer le joueur sur les cases disponibles*/

	void onRightClickBoard(wxMouseEvent& event);
	/*fonctions appelés pour tout click droit sur panelboard*/
	/*permet de poser un mur à la souris avec un faux drag and drop*/

	void onMouseMoveBoard(wxMouseEvent& event);
	/*Fonction de l'event du mouvement de la souris sur panelboard*/

	void onKeyPressBoard(wxKeyEvent& event);
	/*Fonction de l'event du clavier*/

	void onEventPlacerMur();
	/*Fonction de l'event placerMur*/

	void wxAfficherInfoMur(unsigned int indice) const;
	/*fonctions debug pour afficher (wxmessagebox) les infos des murs*/

	void wxAfficherInfotdm(wxCommandEvent& event) const;
	/*fonctions debug pour afficher (wxmessagebox) les murs*/

	void wxAfficherMurtemp() const;
	/*Fonction pour le debug*/

	void wxAfficherInfoPion(const Pion& joueur) const;
	/*fonctions debug pour afficher (wxmessagebox) les infos des pions*/

	void wxAfficherMenu(wxCommandEvent& event) const;

	void fermerMenu(wxCommandEvent& event);

	void OnExit(wxCloseEvent& event);
	/*Fonction en fermeture de la fenetre*/
	/*Détruit partie*/
};