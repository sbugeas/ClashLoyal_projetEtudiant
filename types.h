#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef enum{tour, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;

typedef struct {
    int posX, posY;
}Tpoint;



typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unit�s que l�on peut attaquer
    Tcible maposition;		//indique soit � air � soit � sol �, utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c�est petit plus c�est rapide
    int degats;
    int portee ;			//en m�tre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de g�rer le fait que chaque unit� attaque une
                            //seule fois par tour ;
                            //0 = a d�j� attaqu�, 1 = peut attaquer ce tour-ci
                            // � remettre � 1 au d�but de chaque tour
    int coutEnElixir;
} Tunite;



#endif // TYPES_H_INCLUDED
