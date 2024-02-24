#ifndef _TAB_DYN
#define _TAB_DYN

/*importer Vec2*/
#include "vec2.h"


enum Direction {HORIZONTAL, VERTICAL, NONE};

struct Mur
{
    /* data */
    vec2<int> Tail;
    vec2<int> Head;
    Direction dir;

    Mur operator+(const Mur m2) ;
    bool operator/(const Mur m2) const ;
};



class TableauDynamiqueMur {
public:
    /* données membres */
    /* =============== */

    Mur * ad;
    unsigned int capacite;
    unsigned int taille_utilisee;

    /* fonctions membres */
    /* ================= */
    TableauDynamiqueMur (); // Constructeur par défaut
    /* Postcondition : le tableau a 1 emplacement alloué mais vide (taille utilisée nulle) */

    TableauDynamiqueMur (const TableauDynamiqueMur& t); // Constructeur par copie
    /* Precondition : le tableau t est initialisé */
    /* Postcondition : les deux tableaux contiennent des séquences d'Mur identiques (copie de t) */

    ~TableauDynamiqueMur (); // Destructeur
    /* Postcondition : la mémoire allouée dynamiquement est libérée. */
	
	void vider ();
    /* Postcondition : la mémoire allouée dynamiquement est libérée.
	                   le tableau a 1 emplacement alloué mais vide (taille utilisée nulle) */

    void ajouterElement (Mur e);
    /* Postcondition : l'élément e est ajouté dans le premier emplacement inutilisé du tableau,
                       la taille est incrémentée de 1. Doublement de la capacité si nécessaire. */

    bool concatenerMur (Mur m);
    /* Algo : On cherche pour tous les murs présents dans le tableau si une concatenation bout-a-bout est possible */
    /*Postcondition : Le mur est soit un nouvelle élément à part entière dans le tableau dynamique
                    soit le mur a été concaténé avec un autre mur du TDM*/
    /*Resultat : false si ajout classique true si concatenation*/

    Mur valeurIemeElement (unsigned int indice) const;
    /* Precondition : 0 <= indice < taille_utilisee */
    /* Resultat : retourne l'Mur à l'indice en paramètre */


    void afficherElement (unsigned int indice) const;
    /* Precondition : 0 <= indice < taille_utilisee */
    /* Postcondition : l'Mur à l'indice en paramètre est affiché sur la sortie standard */

    void afficher () const;
    /* Postcondition : tous les éléments du tableau sont affichés sur la sortie standard */


    void trier (); 
    /* Postcondition : le tableau est trié dans l'ordre croissant des valeurs des éléments */
    /*il faudrait definir une fonction de comparaison entre deux murs ...*/

    int rechercherElement (Mur e) const;
    /* Precondition : le tableau est trié dans l'ordre croissant */
    /* Résultat : indice de l'emplacement qui contient un Mur égal à e,
                  -1 si le tableau ne contient pas d'élément égal à e */


private:


    /* fonctions membres */
    void modifierValeurIemeElement (Mur e, unsigned int indice);
    /* Precondition : 0 <= indice < taille_utilisee */
    /* Postcondition : l'Mur à l'indice en paramètre vaut e */

    
    void supprimerElement (unsigned int indice);
        /* Precondition : le tableau est non vide, et 0 <= indice < taille_utilisee */
        /* Postcondition : la taille utilisée du tableau est décrémentée de 1.
                        si taille_utilisee < capacite/3, alors on divise la capacité par 2. */

    void insererElement (Mur e, unsigned int indice);
    /* Precondition : 0 <= indice < taille_utilisee */
    /* Postcondition : e est inséré à l'indice en paramètre et la taille utilisée est incrémentée de 1 */
    
};

#endif