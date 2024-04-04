#pragma once
#include "MainFrame.h"
#include <string>


MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    /*instancie tous les widgets de la fenetre*/

    wxInitAllImageHandlers(); /*Initialisation des handlers pour les images*/

    panelMain = new wxPanel(this); /*Panel principal de la fenetre */

    panelBoard = new wxPanel(panelMain, wxID_ANY, wxPoint(0, 0), wxSize(450, 450)); /*Panel du Board de la Partie */
    panelBoard->SetBackgroundColour(wxColour(200, 200, 200));

    panelJeu = new wxPanel(panelMain, wxID_ANY, wxPoint(450, 0), wxSize(400, 400)); /*Panel du Jeu de la Partie */

    initPartieButton = new wxButton(panelJeu, wxID_ANY, "Commencer Une Partie", wxPoint(75, 0), wxSize(200, 50));
    initPartieButton->SetBackgroundColour(wxColour(250, 0, 0)); 

    CoupCourant_StaticText = new wxStaticText(panelJeu, wxID_ANY, "Coup Courant", wxPoint(0, 70), wxSize(100, 20));

    J1StaticText = new wxStaticText(panelJeu, wxID_ANY, "J1", wxPoint(0, 100), wxSize(100, 20));
    J2StaticText = new wxStaticText(panelJeu, wxID_ANY, "J2", wxPoint(200, 100), wxSize(100, 20));

    J1MursStaticText = new wxStaticText(panelJeu, wxID_ANY, "Murs J1", wxPoint(0, 140), wxSize(100, 20));
    J2MursStaticText = new wxStaticText(panelJeu, wxID_ANY, "Murs J2", wxPoint(200, 140), wxSize(100, 20));

    InputCoup_TextCtrl = new wxTextCtrl(panelJeu, wxID_ANY, "Coup", wxPoint(0, 170), wxSize(100, 50));

    JouerCoup_Button = new wxButton(panelJeu, wxID_ANY, "Jouer Le Coup", wxPoint(150, 170), wxSize(100, 50));

    afficherMurs_Button = new wxButton(panelJeu, wxID_ANY, "Afficher les Murs", wxPoint(150, 230), wxSize(100, 50));

}


void MainFrame::initBoardUI(const int taille)
{
    
    wxClientDC dc(panelBoard);

    dc.SetBrush(wxColour(200, 200, 200));  /*Brosse grise*/
    dc.DrawRectangle(wxRect(0, 0, taille*sizecase, taille*sizecase)); /*Dessine le rectangle gris*/

    /*declarer le pen*/
    dc.SetPen(wxPen(wxColour(0, 0, 0), 2));  /*stylo noir de largeur 2*/
    
    // dessiner les lignes / colonnes
    for (int i = 0; i < taille+1; i++)
    {
        dc.DrawLine(0, i * sizecase, taille*sizecase, i * sizecase);
        dc.DrawLine(i * sizecase, 0, i * sizecase, taille*sizecase);
    }
}


bool MainFrame::afficherImagePNG(const wxString& filename, const vec2<int> pos) const
{
    wxImage* image = new wxImage(filename, wxBITMAP_TYPE_PNG);

    if (!image->IsOk())
    {
        wxLogError("Cannot load file '%s'.", filename);
        delete image; 
        return false;
    }
    
    image->Rescale(sizecase-epaissTraits, sizecase-epaissTraits, wxIMAGE_QUALITY_HIGH); //48*48

    wxClientDC dc(panelBoard);
    dc.DrawBitmap(wxBitmap(*image), wxPoint(pos.x*sizecase+1, pos.y*sizecase+1), true);

    delete image;
    return true;
}

void MainFrame::initPionsUI(const int taille) 
{
    wxString filename;
    filename = "../data/J0.png";
    int yinit = (int) (taille / 2);
    afficherImagePNG(filename, vec2<int>(0, yinit));

    filename = "../data/J1.png";
    afficherImagePNG(filename, vec2<int>(taille-1, yinit));

    
}

void MainFrame::effacerPion(const vec2<int> pos) const
{
    wxClientDC dc(panelBoard);
    dc.SetBrush(wxColour(200, 200, 200));   
    dc.SetPen(wxColour(200, 200, 200));
    dc.DrawRectangle(wxRect(pos.x*sizecase+1, pos.y*sizecase+1, sizecase-2, sizecase-2));
}

void MainFrame::deplacerPion(const vec2<int> oldpos, const vec2<int> newpos ,const Pion& joueur) const
{

    wxString filename;
    filename = "../data/J" + std::to_string((int) joueur.ID) + ".png";
    bool affiche = afficherImagePNG(filename, newpos);
    assert(affiche);

    effacerPion(oldpos);
}


void MainFrame::afficherMur(const Mur m, const wxColour c,int epaisseur) const
{
    wxClientDC dc(panelBoard);

    // declarer le pen
    dc.SetPen(wxPen(c, epaisseur)); 

    dc.DrawLine(m.Tail.x*50, m.Tail.y*50, m.Head.x*50, m.Head.y*50);

}


void MainFrame::surlignerCase(const vec2<int> pos,wxColour c) const
{
    wxClientDC dc(panelBoard);
    dc.SetBrush(c);
    dc.SetPen(c);
    dc.DrawRectangle(wxRect(pos.x*sizecase+1, pos.y*sizecase+1, sizecase-epaissTraits, sizecase-epaissTraits));
}

void MainFrame::afficherCoupBoard(const coup& c,const Pion& joueur) const

{
    if(c.type == typeCoup::DEPLACEMENT) {
        deplacerPion( joueur.caseCourante.position, c.newpos, joueur);
    }
    else if(c.type == typeCoup::MUR) {
        afficherMur(c.mur, wxColour(0, 0, 250) , 4);
    }
}



