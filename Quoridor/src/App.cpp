#pragma once
#include "App.h"

wxIMPLEMENT_APP(App);


bool App::OnInit() {


	mainFrame = new MainFrame("Quoridor UIs");

	mainFrame->SetClientSize(800, 450);
	mainFrame->Center();
	mainFrame->Show(true);


	/*Bind des fonctions membres de App sur un boutton de la classe MainFrame avec lambda*/

	/*fonctions pour les différents boutons de la fenetre*/
	mainFrame->initPartieButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {onButtonInitPartie(event);});
	mainFrame->JouerCoup_Button->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {onButtonJouerCoup(event);});
	mainFrame->afficherMurs_Button->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {wxAfficherInfotdm();});

	/*fonctions pour les inputs souris*/
	mainFrame->panelBoard->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event) {onleftClickBoard(event);});
	mainFrame->panelBoard->Bind(wxEVT_RIGHT_DOWN, [this](wxMouseEvent& event) {onRightClickBoard(event);});
	mainFrame->panelBoard->Bind(wxEVT_MOTION, [this](wxMouseEvent& event) {onMouseMoveBoard(event);});
	
	mainFrame->Bind(wxEVT_CHAR_HOOK, [this](wxKeyEvent& event) {onKeyPressBoard(event);}); /*bind pour un appui de touche*/
	mainFrame->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& event) {OnExit(event);}); /*bind pour la fermeture de la fenetre*/
	return true;

		 
}


void App::initPartieUI(const int taille)
{
	
	mainFrame->initBoardUI(taille);
	mainFrame->initPionsUI(taille);

}

void App::initJeuUI(const int taille)
{
	mainFrame->CoupCourant_StaticText->SetLabel("Coup Courant : 0");
	string s = "J1 : (0," + to_string((int)taille/2) + ")";
	mainFrame->J1StaticText->SetLabel(s);
	
	s = "J2 : (" + to_string(taille-1) + "," + to_string((int)taille/2) + ")";
	mainFrame->J2StaticText->SetLabel(s);

	s = "Murs : 5";
	mainFrame->J1MursStaticText->SetLabel(s);
	s = "Murs : 5";
	mainFrame->J2MursStaticText->SetLabel(s);

	mainFrame->InputCoup_TextCtrl->SetLabel("D03");
}

void App::updatejeuUI(){

	/*update le tour courant*/
	mainFrame->CoupCourant_StaticText->SetLabel("Coup Courant : " + to_string(partie->coupCourant));


	/*update les positions des joueurs*/
	string s = "J1 : (" + to_string(partie->joueur1.caseCourante.position.x) + "," + to_string(partie->joueur1.caseCourante.position.y) + ")";
	mainFrame->J1StaticText->SetLabel(s);

	string s2  = "J2 : (" + to_string(partie->joueur2.caseCourante.position.x) + "," + to_string(partie->joueur2.caseCourante.position.y) + ")";
	mainFrame->J2StaticText->SetLabel(s2);
	
	mainFrame->J1MursStaticText->SetLabel("Murs : " + to_string(partie->joueur1.nbMur));

	mainFrame->J2MursStaticText->SetLabel("Murs : " + to_string(partie->joueur2.nbMur));
}

void App::onButtonInitPartie(wxCommandEvent& event)
{
	
	initPartieUI(9);
	if (partieInit) delete partie;
	partie = mainFrame->initPartie(9);

	initJeuUI(9);
	partieInit = true;

	murTemp.dir = Direction::NONE;
	
}

void App::jouerCoupBoard(const string s)
{
	coup c = partie->coupofString(s);
	Pion& p = (partie->coupCourant % 2 == 0) ? partie->joueur1 : partie->joueur2; /*passsage en ref sinon pas d'actualisation*/
	
	if(partie->coupValide(c, p))
	{
		mainFrame->afficherCoupBoard(c, p);
		partie->jouerCoup(c, p);
		updatejeuUI();

		string id = (partie->coupCourant % 2 == 0) ? "J1" : "J2";
		if(partie->gagnant(p.ID)) wxMessageBox("Gagnant : " + id);
	}
	
}

void App::onButtonJouerCoup(wxCommandEvent& event)
{

	string coupstring = mainFrame->InputCoup_TextCtrl->GetValue().ToStdString();
	
	if(voisinsSelected) {effacerVoisinesPion(partie->joueur1) ; effacerVoisinesPion(partie->joueur2); voisinsSelected = false;}

	jouerCoupBoard(coupstring);
}

void App::afficherVoisinesPion(const Pion& joueur) const
{

	Case* voisines;
	voisines = partie->board.Cases->GetVoisins(joueur.caseCourante);

	for(int i = 0; i < 4; i++)
	{
		if(voisines[i].valide && voisines[i].Occupant == TypeOccupant::Vide && partie->deplacementValide(joueur,voisines[i].position))
		{
			mainFrame->surlignerCase(voisines[i].position, wxColour(100, 100, 250));
		}
	}

	/*supprimer la liste des voisines pour eviter un mem leak...*/
	delete[] voisines;
	voisines = NULL;
}

void App::effacerVoisinesPion(const Pion& joueur) const
{
	Case* voisines;
	voisines = partie->board.Cases->GetVoisins(joueur.caseCourante);

	for(int i = 0; i < 4; i++)
	{
		if(voisines[i].valide && voisines[i].Occupant == TypeOccupant::Vide && partie->deplacementValide(joueur,voisines[i].position))
		{
			mainFrame->effacerPion(voisines[i].position);
		}
	}
	/*supprimer la liste des voisines pour eviter un mem leak...*/
	delete[] voisines;
	voisines = NULL;
}

void App::onleftClickBoard(wxMouseEvent& event)
{

	if(!partieInit) return;

	/*On recupere la position du click*/
	wxPoint pos = event.GetPosition();
	vec2<int> posCase;
	posCase.x = pos.x / mainFrame->sizecase;
	posCase.y = pos.y / mainFrame->sizecase; /*attention pas de double affectation sinon 0 sur y*/
		
	/*On recupere le joueur courant*/
	Pion& p = (partie->coupCourant % 2 == 0) ? partie->joueur1 : partie->joueur2;

	if(voisinsSelected){
		
		effacerVoisinesPion(p);
		voisinsSelected = false;

		Case* voisines;
		voisines = partie->board.Cases->GetVoisins(p.caseCourante);
		
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
		afficherVoisinesPion(p);
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

	if(voisinsSelected) {effacerVoisinesPion(partie->joueur1) ; effacerVoisinesPion(partie->joueur2); voisinsSelected = false;}

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

	if(voisinsSelected) {effacerVoisinesPion(partie->joueur1) ; effacerVoisinesPion(partie->joueur2); voisinsSelected = false;}

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
	else {
	mainFrame->afficherMur(murTemp, wxColour(0, 0, 0) , 2);	

	}
	
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
	
	event.Skip();
}

void App::wxAfficherInfoMur(unsigned int indice) const
{
	if(!partieInit) return;
	if(indice >= partie->board.tabdMur->taille_utilisee) return;
	char* str = new char[100];
	str = partie->board.tabdMur->toString(indice);
	wxMessageBox(str);

	delete [] str;
	str = NULL;
}

void App::wxAfficherInfotdm() const
{
	if(!partieInit) return;
	for(unsigned int i = 0; i < partie->board.tabdMur->taille_utilisee; i++)
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

void App::OnExit(wxCloseEvent& event)
{
	
	event.Skip();
}