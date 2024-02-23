
#include "TableauDynamiqueMur.h"
#include "vec2.h"

#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;


Mur operator + (const Mur m1, const Mur m2) {
    Mur m;
    if(m1.dir == m2.dir && m1.Head == m2.Tail )
    {
        m.Head = m2.Head;
        m.Tail = m1.Tail;
        m.dir = m1.dir;
        return m;
    }
    else if(m1.dir == m2.dir && m1.Tail == m2.Head )
    {
        m.Head = m2.Head;
        m.Tail = m1.Tail;
        m.dir = m1.dir;
        return m;
    }
    else
    {
        cout << "Les murs ne sont pas concaténables" << endl;
        m.dir = NONE;
        return m;  
    }
};


bool operator >(const vec2<int> v, int i) {
    return (v.x > i) && (v.y > i);
};
    
bool operator >=(const vec2<int> v, int i) {
    return (v.x >= i) && (v.y >= i);
};


bool operator /(const Mur m1, const Mur m2) {

    if(m1.dir != m2.dir) /*cas ou les murs ne sont pas de meme direction*/
    {
      if (m1.dir == VERTICAL) return m2/m1; //pour s assurer que m1 est horizontal et m2 vertical

      if(m1.Tail.x < m2.Tail.x < m1.Head.x && m2.Tail.y < m1.Tail.y < m2.Head.y)
        {
            return true;
        }
    }
    else if(m1.dir == m2.dir) /*cas des murs qui ont la meme direction*/
    {
        if (m1.dir == HORIZONTAL) return m2.Tail.x < m1.Tail.x < m2.Head.x || m2.Tail.x < m1.Head.x < m2.Head.x;

        if (m1.dir == VERTICAL) return m2.Tail.y < m1.Tail.y < m2.Head.y || m2.Tail.y < m1.Head.y < m2.Head.y;   
    }
    return false;
}
TableauDynamiqueMur::TableauDynamiqueMur () {

    ad = new Mur [1]; //pointeur générique vers un mur
    capacite = 1;
    taille_utilisee = 0;
}

TableauDynamiqueMur::TableauDynamiqueMur (const TableauDynamiqueMur & t) { //const tdm & t pour ne pas modifier t
  ad = new Mur [t.capacite];
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
  ad = new Mur [1];
  capacite = 1;
  taille_utilisee = 0;
}

void TableauDynamiqueMur::ajouterElement (Mur e) {
  Mur * temp;
  if (taille_utilisee == capacite) { // tableau plein, doublons la capacité
      temp = ad;
      ad = new Mur [2*capacite];
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

bool TableauDynamiqueMur::concatenerMur (Mur m) {

  for (unsigned int i = 0; i < taille_utilisee; i++) {
      if(m.dir==ad[i].dir && (m.Head == ad[i].Tail || m.Tail == ad[i].Head)) {
          ad[i] = ad[i] + m; 
          return true; /*concaténation efféctuée*/
      }}

  ajouterElement(m);
  return false; /*concaténation non efféctuée*/
}


Mur TableauDynamiqueMur::valeurIemeElement (unsigned int indice) const {
  return ad[indice];
}

void TableauDynamiqueMur::modifierValeurIemeElement (Mur e, unsigned int indice) {
  ad[indice] = e;
}


void TableauDynamiqueMur::afficherElement (unsigned int indice) const {
  printf("Mur %d : Taille : %d %d, Head : %d %d, Direction : %d\n", indice, ad[indice].Tail.x, ad[indice].Tail.y, ad[indice].Head.x, ad[indice].Head.y, ad[indice].dir);
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
    Mur * temp = ad;
    capacite = capacite / 2;
    ad = new Mur [capacite];
    for(unsigned int p = 0; p < taille_utilisee; p++)
        ad[p] = temp[p];
    delete [] temp;
  }
}

void TableauDynamiqueMur::insererElement (Mur e, unsigned int indice) {
  if(taille_utilisee > 0) {
      /* S'il y a au moins un Mur dans le tableau, on recopie le dernier
         en appelant la procédure d'ajout, qui s'occupera d'augmenter la capacité si nécessaire */
      ajouterElement(ad[taille_utilisee - 1]);
  }
  /* Ensuite on décale d'un cran les éléments à droite de indice */
  for (unsigned int j = taille_utilisee - 1; j > indice; j--)
    ad[j] = ad[j-1];
  /* On peut enfin insérer e à la position indice */
  ad[indice] = e;
}


