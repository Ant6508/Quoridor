
#pragma once
#include "App.h"
#include <iostream>

#include <string>
using namespace std;

wxIMPLEMENT_APP(App);


bool App::OnInit()
{ /*entry point*/

	mainFrame = new MainFrame("Quoridor UIs");

	mainFrame->SetSize(1000, 715);
	mainFrame->Center();
	mainFrame->Show(true);


	/*Bind des fonctions membres de App sur un boutton de la classe MainFrame avec lambda*/

	/*fonctions pour les différents boutons de la fenetre*/
	mainFrame->initPartieButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {onButtonInitPartie(event);});
	mainFrame->JouerCoup_Button->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {onButtonJouerCoup(event);});
	mainFrame->afficherMurs_Button->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {wxAfficherInfotdm(event);});
	mainFrame->fermerMenu_Button->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {fermerMenu(event);});

	/*fonctions pour les inputs souris*/
	mainFrame->panelBoard->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event) {onLeftClickBoard(event);});
	mainFrame->panelBoard->Bind(wxEVT_RIGHT_DOWN, [this](wxMouseEvent& event) {onRightClickBoard(event);});
	mainFrame->panelBoard->Bind(wxEVT_MOTION, [this](wxMouseEvent& event) {onMouseMoveBoard(event);});
	
	mainFrame->Bind(wxEVT_CHAR_HOOK, [this](wxKeyEvent& event) {onKeyPressBoard(event);}); /*bind pour un appui de touche*/
	mainFrame->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& event) {OnExit(event);}); /*bind pour la fermeture de la fenetre*/
	return true;

		 
}


void App::initPartieUI(const int taille)
{
	mainFrame->initBoardUI(taille);
	initPionsUI();
}

void App::initPionsUI()
{
	for(int i = 0; i < partie->nbJoueurs; i++)
	{
		string filename = "../data/J" + std::to_string((int) partie->joueurs[i].ID) + ".png";
		mainFrame->afficherImagePNG(filename, partie->joueurs[i].caseCourante.position);
	}
}

void App::initJeuUI(const int taille)
{
	mainFrame->CoupCourant_StaticText->SetLabel("Coup Courant : 0");
	mainFrame->InputCoup_TextCtrl->SetLabel("D03");

	mainFrame->Joueurs_StaticText = new wxStaticText*[partie->nbJoueurs];
	for(int i = 0; i < partie->nbJoueurs; i++)
	{
		char* str = partie->StringofPion(partie->joueurs[i]);
		mainFrame->Joueurs_StaticText[i] = new wxStaticText(mainFrame->panelJeu, wxID_ANY, str, wxPoint(0, 100 + i*40), wxSize(200, 20));
		delete [] str;
		str = NULL;
	}
}

void App::updatejeuUI(){
	/*update le tour courant*/
	mainFrame->CoupCourant_StaticText->SetLabel("Coup Courant : " + to_string(partie->coupCourant));

	/*update les positions des joueurs*/
	for(int i = 0; i < partie->nbJoueurs; i++)
	{
		char* str = partie->StringofPion(partie->joueurs[i]);
		mainFrame->Joueurs_StaticText[i]->SetLabel(str);
		delete [] str;
	}

}

void App::onButtonInitPartie(wxCommandEvent& event)
{

	if(partieInit) delete partie;
	partie =NULL;
	partie = new Partie(9);
	initPartieUI(9);

	initJeuUI(9);
	partieInit = true;
}

void App::jouerCoupBoard(const string coupString)
{
	Coup c = partie->coupofString(coupString);
	Pion& p = (partie->JoueurOfTour());
	
	if(partie->coupValide(c, p))
	{
		mainFrame->afficherCoupBoard(c, p); /*affichage UI sur le board*/
		partie->jouerCoup(c, p); /*Joueur le Couppour l'objet Partie*/
		updatejeuUI(); /*update l'UI text*/
	}
}

void App::onButtonJouerCoup(wxCommandEvent& event)
{
	if(!partieInit) return;
	string coupstring = mainFrame->InputCoup_TextCtrl->GetValue().ToStdString(); /*rècupère le Coupprésent dans la txtbox*/
	if(voisinsSelected) {effacerVoisinesPion(partie->JoueurOfTour()); voisinsSelected = false;}
	jouerCoupBoard(coupstring); /*joue le Coupsi il est possible*/
}

void App::afficherVoisinesPion(const Pion& joueur) const
{
	Case* voisines;
	voisines = partie->GetVoisins(joueur.caseCourante);
	if(voisines == nullptr) return; 

	for(int i = 0; i < 4; i++)
	{
		if(voisines[i].valide && partie->deplacementValide(joueur,voisines[i].position)) /*Couvre donc le cas ou un joueur est présent sur la newcase*/
			mainFrame->surlignerCase(voisines[i].position, wxColour(102, 204, 0));
	}

	/*supprimer la liste des voisines pour éviter un mem leak...*/
	delete[] voisines;
	voisines = NULL;
}

void App::effacerVoisinesPion(const Pion& joueur) const
{
	Case* voisines;
	voisines = partie->GetVoisins(joueur.caseCourante);
	if(voisines == nullptr) return; 

	for(int i = 0; i < 4; i++)
	{
		if(voisines[i].valide && partie->deplacementValide(joueur,voisines[i].position))
		{
			mainFrame->effacerPion(voisines[i].position);
		}
	}
	/*supprimer la liste des voisines pour eviter un mem leak...*/
	delete[] voisines;
	voisines = NULL;
}

void App::onLeftClickBoard(wxMouseEvent& event)
{

	if(!partieInit) return;

	/*On recupere la position du click*/
	wxPoint pos = event.GetPosition();
	vec2<int> posCase;
	posCase.x = pos.x / mainFrame->sizecase;
	posCase.y = pos.y / mainFrame->sizecase; /*attention pas de double affectation sinon 0 sur y*/
		
	/*On recupere le joueur courant*/
	Pion& p = partie->JoueurOfTour();


	if(voisinsSelected){
		
		effacerVoisinesPion(p);
		voisinsSelected = false;

		Case* voisines;
		voisines = partie->GetVoisins(p.caseCourante);
		if(voisines == nullptr) return; /*cas ou la case est invalide (hors board)*/
		
		for(int i = 0; i < 4; i++)
		{	
			if(voisines[i].valide && posCase == voisines[i].position)
			{
				string s = "D" + to_string(voisines[i].position.x) + to_string(voisines[i].position.y);
				jouerCoupBoard(s);
				break;
			}
		}
		/*supprimer la liste des voisines pour eviter un mem leak...*/
		delete[] voisines;
		voisines = NULL;
		return; 
	}
	else{
		afficherVoisinesPion(p); /*pour le joueur dont c'est le tour*/
		voisinsSelected = true;
	}

	if(murSelected) {
		
		if(murTemp.dir != Direction::NONE) mainFrame->afficherMur(murTemp, wxColour(0, 0, 0), 2);
		murTemp.dir = Direction::NONE;
		murSelected = false;
	}

}

void App::onRightClickBoard(wxMouseEvent& event)
{
	if(!partieInit || !murSelected || !partie->murValide(murTemp) ) return;

	if(voisinsSelected) {effacerVoisinesPion(partie->JoueurOfTour()); voisinsSelected = false;}

	wxPoint pos = event.GetPosition();

	vec2<int> posCase;
	posCase.x = pos.x / mainFrame->sizecase;
	posCase.y = pos.y / mainFrame->sizecase;

	string coupstring = "M" + to_string(murTemp.Tail.x) + to_string(murTemp.Tail.y) + to_string(murTemp.Head.x) + to_string(murTemp.Head.y);

	jouerCoupBoard(coupstring);

	murTemp.dir = Direction::NONE;
	murTemp.Tail = vec2<int>(0,0);
	murTemp.Head = vec2<int>(0,0);
	murSelected = false;

}

void App::onEventPlacerMur()
{
	if(!partieInit) return;

	if(voisinsSelected) {effacerVoisinesPion(partie->JoueurOfTour()); voisinsSelected = false;}

	if(murSelected) {
		murSelected = false;
		if(murTemp.dir != Direction::NONE) mainFrame->afficherMur(murTemp, wxColour(0, 0, 0), 2);
		}
	else murSelected = true;
}


void App::onMouseMoveBoard(wxMouseEvent& event)
{
	if(!partieInit || !murSelected ) return;

	wxPoint pos = event.GetPosition();

	vec2<int> posCase;
	posCase.x = pos.x / mainFrame->sizecase;
	posCase.y = pos.y / mainFrame->sizecase;

	if(murTemp.dir == Direction::NONE){ /*cas ou on a pas encore de mur préposé*/

		Direction tempdir = Direction::HORIZONTAL;	
		murTemp.dir = tempdir;
	}
	else mainFrame->afficherMur(murTemp, wxColour(0, 0, 0) , 2);	
	
	vec2<int> delta;
	if (murTemp.dir == Direction::HORIZONTAL) delta.x = 2;	
	else delta.y = 2;

	murTemp.Tail = posCase;
	murTemp.Head = posCase + delta;

	bool murValide = partie->murValide(murTemp);

	if (murValide) mainFrame->afficherMur(murTemp, wxColour(0, 0, 250),2);
	else murTemp.dir = Direction::NONE;


}

void App::onKeyPressBoard(wxKeyEvent& event)
{
	
	if(!partieInit) return;

	/*si touche "s" on change la direction du mur temp*/
	if(event.GetKeyCode() == 83 && murSelected)
	{
		if(murTemp.dir == Direction::HORIZONTAL) murTemp.dir = Direction::VERTICAL;
		else murTemp.dir = Direction::HORIZONTAL;
	}
	/*si touche on m on appelle la logique pour placer un mur*/
	else if (event.GetKeyCode() == 77) onEventPlacerMur();

	/*si touche "t" on affiche le menu*/
	else if (event.GetKeyCode() == 84) mainFrame->SetSize(mainFrame->panelBoard->GetSize().x+mainFrame->panelJeu->GetSize().x , mainFrame->GetSize().y);
	
	event.Skip();
}

void App::wxAfficherInfoMur(unsigned int indice) const
{
	if(!partieInit) return;
	if(indice >= partie->board.tabdMur.taille_utilisee) return;
	char* str = partie->board.tabdMur.toString(indice);
	wxMessageBox(str);

	delete [] str;
	str = NULL;
}

void App::wxAfficherInfotdm(wxCommandEvent& event) const
{
	if(!partieInit) return;
	for(unsigned int i = 0; i < partie->board.tabdMur.taille_utilisee; i++)
	{
		wxAfficherInfoMur(i);
	}
}

void App::wxAfficherMurtemp() const
{
	return;
	if(partieInit) return;
	if(murTemp.dir == Direction::NONE) return;
	char* str = new char[100];
	sprintf_s(str, 100, "Mur temp : Taille : (%d,%d) Head : (%d,%d) Direction : %d\n", murTemp.Tail.x, murTemp.Tail.y, murTemp.Head.x, murTemp.Head.y, murTemp.dir);
	wxMessageBox(str);
	delete [] str;
	str = NULL;
}

void App::wxAfficherInfoPion(const Pion& joueur) const
{
	if(!partieInit) return;
	char* str = partie->StringofPion(joueur);
	wxMessageBox(str);
	delete [] str;
	str = NULL;
}

void App::fermerMenu(wxCommandEvent& event)
{
	mainFrame->SetSize(mainFrame->GetSize().y ,mainFrame->GetSize().y);

}

void App::OnExit(wxCloseEvent& event)
{
	delete partie;
	delete [] mainFrame->Joueurs_StaticText;

	
	event.Skip();
}