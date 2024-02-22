
#include "TableauDynamiqueMur.h"

#include <iostream>
#include <stdlib.h>
using namespace std;


Mur* operator + (Mur* m1, Mur m2) { //mur de gauche : pointeur vers un mur du tableau, mur de droite : mur à ajouter
    Mur * m = new Mur;
    
    if (m1->Head == m2.Tail) {
        m->Head = m2.Head;
        m->Tail = m1->Tail;
    }
    else if (m1->Tail == m2.Head) {
        m->Head = m1->Head;
        m->Tail = m2.Tail;  
    }
    if(m1->dir == HORIZONTAL){
      m->dir = HORIZONTAL;
    }
    else {
      m->dir = VERTICAL;
    }

    return m;
}

TableauDynamiqueMur::TableauDynamiqueMur () {

    ad = new ElementTD [1]; //pointeur générique vers un mur
    capacite = 1;
    taille_utilisee = 0;
}

TableauDynamiqueMur::TableauDynamiqueMur (const TableauDynamiqueMur & t) { //const tdm & t pour ne pas modifier t
  ad = new ElementTD [t.capacite];
  capacite = t.capacite;
  taille_utilisee = t.taille_utilisee;
  for (unsigned int i = 0; i < t.taille_utilisee; i++) ad[i] = t.ad[i];
}

TableauDynamiqueMur::~TableauDynamiqueMur () {
  delete [] ad;
  ad = NULL;
  capacite = 0;
  taille_utilisee = 0;
}

void TableauDynamiqueMur::vider () {
  delete [] ad;
  ad = new ElementTD [1];
  capacite = 1;
  taille_utilisee = 0;
}

void TableauDynamiqueMur::ajouterElement (ElementTD e) {
  ElementTD * temp;
  if (taille_utilisee == capacite) { // tableau plein, doublons la capacité
      temp = ad;
      ad = new ElementTD [2*capacite];
      if(ad == NULL) {
          cout << "Espace memoire insuffisant" << endl;
          exit(EXIT_FAILURE);
      }
      capacite *= 2;
      for (unsigned int i = 0; i < taille_utilisee; i++) ad[i] = temp[i];
      delete [] temp;
  }
  ad[taille_utilisee] = e;
  taille_utilisee++;
}

void TableauDynamiqueMur::concatenerMur (Mur m) {

  for (unsigned int i = 0; i < taille_utilisee; i++) {
      if(m.dir==ad[i]->dir && (m.Head == ad[i]->Tail || m.Tail == ad[i]->Head)) {
          ad[i] = ad[i] + m; //pointe vers le nouveau mur
          return;
      } }

  ajouterElement(&m);
}

ElementTD TableauDynamiqueMur::valeurIemeElement (unsigned int indice) const {
  return ad[indice];
}

void TableauDynamiqueMur::modifierValeurIemeElement (ElementTD e, unsigned int indice) {
  ad[indice] = e;
}


void TableauDynamiqueMur::afficherElement (unsigned int indice) const {
  cout << "Head " << ad[indice]->Head.x << " " << ad[indice]->Head.y << "Tail " << ad[indice]->Tail.x << " " << ad[indice]->Tail.y << endl;
}
void TableauDynamiqueMur::afficher () const {
  for(unsigned int i = 0; i < taille_utilisee; i++) {
      afficherElement(i);
  }
}

void TableauDynamiqueMur::supprimerElement (unsigned int indice) {
  if(indice < taille_utilisee-1) {
      for(unsigned int p = indice; p < taille_utilisee-1; p++)
        ad[p] = ad[p+1];
  }
  taille_utilisee--;
  if (taille_utilisee < capacite / 3) { //cest la ou on divise la capacité par 2 du tableau
    ElementTD * temp = ad;
    capacite = capacite / 2;
    ad = new ElementTD [capacite];
    for(unsigned int p = 0; p < taille_utilisee; p++)
        ad[p] = temp[p];
    delete [] temp;
  }
}

void TableauDynamiqueMur::insererElement (ElementTD e, unsigned int indice) {
  if(taille_utilisee > 0) {
      /* S'il y a au moins un ElementTD dans le tableau, on recopie le dernier
         en appelant la procédure d'ajout, qui s'occupera d'augmenter la capacité si nécessaire */
      ajouterElement(ad[taille_utilisee - 1]);
  }
  /* Ensuite on décale d'un cran les éléments à droite de indice */
  for (unsigned int j = taille_utilisee - 1; j > indice; j--)
    ad[j] = ad[j-1];
  /* On peut enfin insérer e à la position indice */
  ad[indice] = e;
}

void TableauDynamiqueMur::trier () {
  /* tri par sélection */
  unsigned int i, j, indmin;
  ElementTD min;
  for (i = 0; i < taille_utilisee - 1; i++) {
      indmin = i;
      for (j = i+1; j < taille_utilisee; j++) {
          if (ad[j] < ad[indmin]) indmin = j;
      }
      min = ad[indmin];
      ad[indmin] = ad[i];
      ad[i] = min;
    }
}

int TableauDynamiqueMur::rechercherElement (ElementTD e) const {
  int debutZR, finZR, milieuZR; /* indices de la zone de recherche */
  bool trouve, fini;
  int res;

  if (taille_utilisee < 1) return -1; // tableau vide
  if ((e < ad[0]) || (e > ad[taille_utilisee-1])) return -1; // l'élément recherche n'est pas compris entre le min et le max du tableau

  debutZR = 0;
  finZR = taille_utilisee - 1;
  fini = false;
  trouve = false;
  res = -1;

  while ((!fini) && (!trouve)) {
      milieuZR = (finZR - debutZR)/2 + debutZR;

      if (e == ad[debutZR])     {trouve = true; res = debutZR;}
      if (e == ad[finZR])       {trouve = true; res = finZR;}
      if (e == ad[milieuZR])    {trouve = true; res = milieuZR;}
      if (debutZR == milieuZR)  {fini = true;}

      if ((!trouve) && (!fini)) {
          if(ad[milieuZR] < e) debutZR = milieuZR;
          else finZR = milieuZR;
      }
    }
    return res;
}

