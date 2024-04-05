#pragma once
#include "MainFrame.h"
#include <string>

using namespace std;

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition)//, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{   /*instancie tous les widgets de la fenetre*/

    wxImage::AddHandler(new wxPNGHandler); /*Ajout du handler pour les images PNG*/
   
    panelMain = new wxPanel(this); /*Panel principal de la fenetre */

    panelBoard = new wxPanel(panelMain, wxID_ANY, wxPoint(0, 0), wxSize(675, 675)); /*Panel du Board de la Partie */
    panelBoard->SetBackgroundColour(wxColour(200, 200, 200));

    panelJeu = new wxPanel(panelMain, wxID_ANY, wxPoint(675, 0), wxSize(325, 675)); /*Panel du Jeu de la Partie */
    panelJeu->SetBackgroundColour(wxColour(200, 230, 230));

    initPartieButton = new wxButton(panelJeu, wxID_ANY, "Commencer Une Partie", wxPoint(75, 0), wxSize(200, 50));

    initPartieButton->SetBackgroundColour(wxColour(250, 0, 0)); 

    CoupCourant_StaticText = new wxStaticText(panelJeu, wxID_ANY, "Coup Courant", wxPoint(0, 70), wxSize(100, 20));

    InputCoup_TextCtrl = new wxTextCtrl(panelJeu, wxID_ANY, "Coup", wxPoint(0, 300), wxSize(100, 50));

    JouerCoup_Button = new wxButton(panelJeu, wxID_ANY, "Jouer Le Coup", wxPoint(150, 300), wxSize(100, 50));

    afficherMurs_Button = new wxButton(panelJeu, wxID_ANY, "Afficher les Murs", wxPoint(0, 380), wxSize(100, 50));

    fermerMenu_Button = new wxButton(panelJeu, wxID_ANY, "Fermer le Menu", wxPoint(150, 380), wxSize(100, 50));

}


void MainFrame::initBoardUI(const int taille)
{
    wxClientDC dc(panelBoard);

    dc.SetBrush(wxColour(200, 200, 200));  /*Brosse grise*/
    dc.DrawRectangle(wxRect(0, 0, taille*sizecase, taille*sizecase)); /*Dessine le rectangle gris*/

    /*declarer le pen*/
    dc.SetPen(wxPen(wxColour(0, 0, 0), 2));  /*stylo noir de largeur 2*/
    
    // dessiner les lignes / colonnes
    for (int i = 0; i < taille+2; i++)
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
    dc.SetPen(wxPen(c, epaisseur)); // declarer le pen
    dc.DrawLine(m.Tail.x*sizecase, m.Tail.y*sizecase, m.Head.x*sizecase, m.Head.y*sizecase);
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
    if(c.type ==typeCoup::RIEN || joueur.ID==TypeOccupant::Vide ) return;

    if(c.type == typeCoup::DEPLACEMENT) deplacerPion( joueur.caseCourante.position, c.newpos, joueur);
        
    else if(c.type == typeCoup::MUR) afficherMur(c.mur, wxColour(0, 0, 250) , 4);
    
}




