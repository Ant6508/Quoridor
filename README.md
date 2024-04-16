# Quoridor

Quoridor est un jeu de plateau stratégique aux règles simples.
Nous proposons une implémentation du jeu entièrement basée en c++ dans le cadre du projet LIFAPCD
On peut décomposer le projet en une partie Base et une partie UI

# Règles du jeu Quoridor
Les règles les suivantes :
- Le jeu se passe sur un board carré de 9x9 cases
- Chaque joueur incarne un Pion qui sont initialement placés face à face au centre de 2 lignes opposées
- Tour à tour un joueur peut décider soit de déplacer son Pion sur une case adjacente innoccupée du board ou bien de placer un Mur de deux cases de longueur
    bloquant le déplacement d'un joueur d'une case vers une autre
- Evidemment deux Murs ne peuvent pas se chavaucher, un Mur ne peut jamais "sortir" d'un côté ou de l'autre du board
    et enfin un Mur ne peut pas empêcher un joueur de gagner la partie
- La partie est gagné par l'un des joueur lorsque celui-ci arrive sur l'une des cases du côté opposé par rapport à celui dont il est parti
![Init2P](./Quoridor/data/ReadMeImages/Init2P.png "Configuration initiale pour 2 joueurs") 


# Comment Jouer au Clavier/Souris sur le plateau
![ExemplePartie](./Quoridor/data/ReadMeImages/partieRandom.png "cases vertes:dispo , murs en bleu")

Click gauche : Afficher les cases disponibles pour se déplacer puis sélectionner avec click gauche encore

touche m : Met un mur sur votre curseur qui est posable avec click droit, ou touche m encore pour annuler la pose du mur

touche s : changer l'orientation vertical/horizontal dur mur qu'on veut poser

touche t : faire apparaître le menu


# Build

BUILD avec Visual studio 2019 pour Windows :
    - Télécharger wxwidgets depuis la source : https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.4/wxWidgets-3.2.4.zip
    - extraire et créer une variable environement appelée WXWIN pointant au dossier racine de wxwidgets
    - Ouvrir la solution wx_vc16.sln et build en mode debug puis release pour les platformes x32 et x64
    Vidéo tutoriel : https://www.youtube.com/watch?v=ONYW3hBbk-8&list=PLFk1_lkqT8MbVOcwEppCPfjGOGhLvcf9G&index=2
    Désormais vous pouvez générer la solution Quoridor présente dans l'archive qui devrait donc être liée aux librairies wxwidgets et démarer le jeu

BUILD avec Cmake en crossplatforme : 
    - Télécharger wxwidgets depuis la source : https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.4/wxWidgets-3.2.4.zip
    - Extraire wxwidgets dans le dossier Quoridor/external
    - depuis l'invite de commande (cmake doit être installé) : cmake . -B BUILD -G "Unix Makefiles"
        et puis une fois terminé : cmake --build BUILD
    - un executable devrait être créé dans le dossier BUILD/ nommé wxQuoridor

# Auteur
Julien P12025052

# Répertoire de l'archive

    Quoridor/
        -Quoridor.sln : Projet vs2019 pour compiler le code

        Quoridor/data : stock les différentes images utilisées dans le projet

        Quoridor/Doc : Documentation doxygen + diagramme de classe

        Quoridor/src : dossier contenant tous les .cpp/.h
            -App : Classe application window mise en place avec wxWidgets et uilisant la classe Partie
            -MainFrame : Objet héritée de wxwin qui contient tous les widgets (UI)
        
        Quoridor/src/base : Base isolée pour le jeu du Quoridor
            -TableauDynamiqueMur : Classe gèrant les objets Murs que les joueurs posent au cours d'une partie
            -Partie : Classe qui réalise le jeu en tant que tel en jouant des coups, maj des joueurs, gestion du tableau des murs etc
            -vec2.h : Classe de Chan Jer Shyan omniprésente dans le code qui propose une classe pour les couples(x,y) -> vec2<int>
            -TestNonRegression.cpp : assert du pleins de cas différents d'une partie pour le debug



# Remerciements

Mayer Alexandre 

Chan Jer Shyan pour sa classe vec2 libre d'utilisation
