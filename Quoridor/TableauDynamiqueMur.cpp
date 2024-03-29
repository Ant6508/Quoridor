
#include "TableauDynamiqueMur.h"
#include "vec2.h"

#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;


Mur Mur::operator +(const Mur m2)  {
  /*Opérateur de concaténation de deux murs bout à bout*/
  /*Resulat : un mur qui est la concaténation des deux murs quand c'est possible
            Sinon simplement un mur de dir None*/
    Mur m;
    if(dir == m2.dir && Head == m2.Tail )
    {
        m.Head = m2.Head;
        m.Tail = Tail;
        m.dir = dir;
        return m;
    }
    else if(dir == m2.dir && Tail == m2.Head )
    {
        m.Head = m2.Head;
        m.Tail = Tail;
        m.dir = dir;
        return m;
    }
    else
    {
        cout << "Les murs ne sont pas concaténables" << endl;
        m.dir = Direction::NONE;
        return m;  
    }
};



bool Mur::operator /(const Mur m2) const {
  /*Opérateur de croisement de deux murs*/
    
    if(dir != m2.dir) /*cas ou les murs ne sont pas de meme direction*/
    {
      if (dir == VERTICAL) return m2/ *this; /*pour sassurer que m2 toujours vertical*/
      
      if((Tail.x < m2.Tail.x && m2.Tail.x < Head.x) &&( m2.Tail.y < Tail.y && Tail.y < m2.Head.y)) /*les parentheses sont inutiles mais cest pour se souvenir*/
        {
            return true;
        }
    }
    else if(dir == m2.dir) /*cas des murs qui ont la meme direction*/
    {
        if (dir == HORIZONTAL) return (m2.Tail.x < Tail.x && Tail.x < m2.Head.x) || (m2.Tail.x < Head.x && Head.x < m2.Head.x);

        if (dir == VERTICAL) return (m2.Tail.y < Tail.y && Tail.y < m2.Head.y) || (m2.Tail.y < Head.y && Head.y < m2.Head.y);
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

bool TableauDynamiqueMur::estVide () const {
  return taille_utilisee == 0;
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

bool TableauDynamiqueMur::croiserListeMurs(const Mur m1,const Mur* murs, const int taille) const {
  for (int i = 0; i < taille; i++) {
      assert(murs[i].dir != NONE); /*on ne veut pas de mur de direction NONE dans la liste*/
      if(m1/murs[i]) return true;
  }
  return false;
}



bool TableauDynamiqueMur::concatenerMur (const Mur m) {
  /*Cas ou concatenation possible en i: on fait l'op en i
    si deuxieme possible en j on fait encore l'op en i puis delete j*/

  unsigned tempint = -1; /*flag sur pile concatenation simple possible? -1 si non >0 si oui */

  for (unsigned int i = 0; i < taille_utilisee; i++) {

    if(m.dir==ad[i].dir && ( ad[i].Tail == m.Head || ad[i].Head==m.Tail )) { /*par construction on au plus 2 fois cette condition */
      
      if( tempint != -1) { /*cas ou on a déjà eu un candidat*/
        ad[tempint] = ad[tempint] + ad[i]; /*concaténation*/  
        supprimerElement(i); /*suppression de l'élément concaténé*/
        return true;
      }

      else {
        ad[i] = ad[i] + m; /*cas ou on a pas encore eu de candidat*/
        tempint = i; /*On enregistre à quel emplacement le 1er mur a été concaténé*/
      }
    }
  }



  if(tempint != -1) return true; /*concaténation efféctuée*/
  return false; /*concaténation non efféctuée*/
}


Mur TableauDynamiqueMur::valeurIemeElement (unsigned int indice) const {
  return ad[indice];
}

void TableauDynamiqueMur::modifierValeurIemeElement (Mur e, unsigned int indice) {
  ad[indice] = e;
}

void TableauDynamiqueMur::afficherElement (unsigned int indice) const {
  printf("Mur %d : Tail : %d %d, Head : %d %d, Direction : %d\n", indice, ad[indice].Tail.x, ad[indice].Tail.y, ad[indice].Head.x, ad[indice].Head.y, ad[indice].dir);
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


