//NOM prénom étudiant 1 : BRUNETIERE THIBAUD
//NOM prénom étudiant 2 : BUGEAS SAMUEL

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonction d'affichage pour le jeu 2048

#include "types.h"
#include "list_lib.h"

#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'écran
    SDL_Surface* pSpriteTour = SDL_LoadBMP("./data/Tour.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp"); //indice 1
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp"); //indice 2
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp"); //indice 3
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp"); //indice 4
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); //indice 5
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp"); //indice 6  Ne figure pas dans l'enum TuniteDuJeu
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp"); //indice 7 idem
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp"); //indice 8 idem
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp"); //indice 9 idem

    // ASTUCE : on stocke le sprite d'une unité à l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
    // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unité (NULL dans le plateau) et en foction de certains indices x,y définissant le chemin central
    SDL_Surface* TabSprite[10]={pSpriteTour,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};


    if ( pSpriteTour )  //si le permier sprite a bien été chargé, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);

        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^
        //message("Welcome in ClashLoyal","Ceci est un point de depart de votre future interface de votre jeu ClahLoyal");
        //message("et fin","ECHAP->quitter, S/C ET D/V les gerer les sauvegardes");

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */

        //INITIALISATION VARIABLES
        srand(time(NULL));
        int *elixirPlayer1 = (int*)malloc(sizeof(int));
        int *elixirPlayer2 = (int*)malloc(sizeof(int));
        *elixirPlayer1 = 10;
        *elixirPlayer2 = 10;

        //Initialisation des listes de joueur
        TListePlayer player1;
        TListePlayer player2;
        initListe(&player1);
        initListe(&player2);

        //Ajout des rois
        Tunite *roi_1 = creeTourRoi(5, 17);
        Tunite *roi_2 = creeTourRoi(5, 1);

        AjouterUnite(&player1, roi_1);
        AjouterUnite(&player2, roi_2);

        //Test
        Tunite *testUnit_1 = creeChevalier(5, 2);
        AjouterUnite(&player1, testUnit_1);


        //Placement des rois sur le plateau
        PositionnePlayerOnPlateau(player1, jeu);
        PositionnePlayerOnPlateau(player2, jeu);


        /*
        // FIN de vos variables                                                              */
        /**********************************************************************/

        // boucle principale du jeu
        int cont = 1;
        while ( cont != 0 ){   //VOUS DEVEZ GERER (DETECTER) LA FIN DU JEU -> tourRoiDetruite
                SDL_PumpEvents(); //do events


                /***********************************************************************/
                /*                                                                     */
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU

                ////////////// BOUCLE DE JEU ///////////////

                //DISTRIBUTION ELIXIR
                giveElixir(elixirPlayer1);
                giveElixir(elixirPlayer2);

                //COMBAT
                Attack(&player1,&player2);

                //MAJ plateau
                initPlateauAvecNULL(jeu,LARGEURJEU, HAUTEURJEU);
                PositionnePlayerOnPlateau(player1, jeu);
                PositionnePlayerOnPlateau(player2, jeu);

                //DETECTION FIN DE JEU (après combat car un roi a peut-être été tué)
                if(tourRoiDetruite(player1))
                {
                    printf("\n\nJoueur 2 gagne !");
                    cont = 0;
                }
                else if(tourRoiDetruite(player2))
                {
                    printf("\n\nJoueur 1 gagne !");
                    cont = 0;
                }

                //DÉPLACEMENT(+ MAJ plateau)
                MoveUnit(player1, player2,jeu);


                //CRÉATION
                if(getNbreCell(player1) < MAXUNITS)
                {
                    AjouterUnite(&player1, AcheteUnite(elixirPlayer1, player1, jeu));
                }
                if(getNbreCell(player2) < MAXUNITS)
                {
                    AjouterUnite(&player2, AcheteUnite(elixirPlayer2, player2, jeu));
                }

                //MAJ plateau
                initPlateauAvecNULL(jeu,LARGEURJEU, HAUTEURJEU);
                PositionnePlayerOnPlateau(player1, jeu);
                PositionnePlayerOnPlateau(player2, jeu);


                //Pour que ce soit + lent
                sleep(1);

                ////////////// FIN BOUCLE DE JEU ///////////////



                /*                                                                     */
                /*                                                                     */
                // FIN DE VOS APPELS
                /***********************************************************************/
                //affichage du jeu à chaque tour
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(150);  //valeur du délai à modifier éventuellement

                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if ( pKeyStates[SDL_SCANCODE_V] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur C */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        //message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");


                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_S] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appyue sur S */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

        }
        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTour); // Libération de la ressource occupée par le sprite
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
