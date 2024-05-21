
#include "TableauDynamiqueMur.h"
#include "vec2.h"

#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;


/*Opérateurs de murs*/

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
    }
    else if(dir == m2.dir && Tail == m2.Head )
    {
        m.Head = Head;
        m.Tail = m2.Tail;
        m.dir = dir;
    }
    else m.dir = Direction::NONE;
    
    return m;
};

bool Mur::operator /(const Mur m2) const {
  /*Opérateur de croisement de deux murs
  m2 est toujours vertical*/
    
  /*verifier si les deux murs sont egaux avec == */

  if(*this == m2) return true;

  else if(dir != m2.dir) /*cas ou les murs ne sont pas de meme direction*/
  {
    if (dir == Direction::VERTICAL) return m2/ *this; /*pour sassurer que m2 toujours vertical*/
    
    if((Tail.x < m2.Tail.x && m2.Tail.x < Head.x) && ( m2.Tail.y < Tail.y && Tail.y < m2.Head.y)) return true;

  }
  else if(dir == m2.dir) /*cas des murs qui ont la meme direction*/
  {
      if (dir == Direction::HORIZONTAL) return ( ( (m2.Tail.x < Tail.x && Tail.x < m2.Head.x) || (m2.Tail.x < Head.x && Head.x < m2.Head.x) ) && (Tail.y == m2.Tail.y));

      if (dir == Direction::VERTICAL) return ( ( (m2.Tail.y < Tail.y && Tail.y < m2.Head.y) || (m2.Tail.y < Head.y && Head.y < m2.Head.y) ) && (Tail.x == m2.Tail.x));
  }
  return false;
}

bool Mur::operator ==(const Mur m2) const {
  /*Opérateur d'égalité de deux murs*/
  return (Tail == m2.Tail && Head == m2.Head);
}


/*PUBLIC TDM*/

TableauDynamiqueMur::TableauDynamiqueMur () {

  ad = new Mur [1]; //pointeur générique vers un mur
  capacite = 1;
  taille_utilisee = 0;
}

TableauDynamiqueMur::TableauDynamiqueMur (const TableauDynamiqueMur & t) { //const tdm & t pour ne pas modifier t
  ad = new Mur [t.capacite];
  capacite = t.capacite;
  taille_utilisee = t.taille_utilisee;
  for (unsigned int i = 0; i < t.taille_utilisee; i++) modifierValeurIemeElement(t.ad[i], i);
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

void TableauDynamiqueMur::ajouterElement (Mur m) {
  Mur * temp;
  if (taille_utilisee == capacite) { // tableau plein, doublons la capacité
      temp = ad;
      ad = new Mur [2*capacite];
      if(ad == NULL) {
          cout << "Espace memoire insuffisant" << endl;
          exit(EXIT_FAILURE);
      }
      capacite *= 2;
      for (unsigned int i = 0; i < taille_utilisee; i++) modifierValeurIemeElement(temp[i], i);
      delete [] temp;
  }
  modifierValeurIemeElement(m, taille_utilisee);
  taille_utilisee++;
}

bool TableauDynamiqueMur::concatenerMur (const Mur m) {
  /*Cas ou concatenation possible en i: on fait l'op en i
    si deuxieme possible en j on fait encore l'op en i puis delete j*/

  unsigned int tempint = -1; /*flag sur pile concatenation simple possible? -1 si non >0 si oui */

  for (unsigned int i = 0; i < taille_utilisee; i++) {

    Mur iemeMur = valeurIemeElement(i);

    if(m.dir==iemeMur.dir && ( iemeMur.Tail == m.Head || iemeMur.Head==m.Tail )) { /*par construction on au plus 2 fois cette condition */
      
      if( tempint != -1) { /*cas ou on a déjà eu un candidat*/
        modifierValeurIemeElement(iemeMur + m, tempint); /*concaténation des deux murs*/ 
        supprimerElement(i); /*suppression de l'élément concaténé*/
        return true;
      }
      else {
        modifierValeurIemeElement(iemeMur + m, i); /*concaténation des deux murs*/
        tempint = i; /*On enregistre à quel emplacement le 1er mur a été concaténé*/
      }
    }
  }

  if(tempint != -1) return true; /*concaténation efféctuée*/
  return false; /*concaténation non efféctuée*/
}

Mur TableauDynamiqueMur::valeurIemeElement (unsigned int indice) const
{
  return ad[indice];
}

char* TableauDynamiqueMur::toString(unsigned int indice) const 
{
  assert(indice < taille_utilisee);
  Mur m = ad[indice];
  char* str = new char[100];
  sprintf_s(str, 100, "Mur %d : Tail : (%d,%d) Head : (%d,%d) Direction : %d\n", indice, m.Tail.x, m.Tail.y, m.Head.x, m.Head.y, m.dir);
  return str;
}

void TableauDynamiqueMur::afficher() const
{
  for (unsigned int i = 0; i < taille_utilisee; i++) {
    printf("%s", toString(i));
  }
}

/*fonctions membres privées*/

void TableauDynamiqueMur::modifierValeurIemeElement (Mur e, unsigned int indice) {
  ad[indice] = e;
}

void TableauDynamiqueMur::supprimerElement (unsigned int indice)
{
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

void TableauDynamiqueMur::insererElement (Mur e, unsigned int indice)
{
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


