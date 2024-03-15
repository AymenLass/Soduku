#include "gestionEvenements.h"






#include <stdio.h>
#include <stdlib.h>
# define N 9
/// G�n�rateur de grille de sudoku


void print(int arr[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", arr[i][j]);

        printf("\n");
        fflush(stdout); // Flush the output buffer after printing each line
    }
}


int isSafe(int grid[N][N], int row,

           int col, int num)
{



    for (int x = 0; x <= 8; x++)

        if (grid[row][x] == num)

            return 0;




    for (int x = 0; x <= 8; x++)

        if (grid[x][col] == num)

            return 0;




    int startRow = row - row % 3,

            startCol = col - col % 3;



    for (int i = 0; i < 3; i++)

        for (int j = 0; j < 3; j++)

            if (grid[i + startRow][j + startCol] == num)

                return 0;


    return 1;
}

int solveSudoku(int grid[N][N], int row, int col)
{



    if (row == N - 1 && col == N)

        return 1;



    if (col == N)

    {

        row++;

        col = 0;

    }


    if (grid[row][col] > 0)

        return solveSudoku(grid, row, col + 1);


    for (int num = 1; num <= N; num++)

    {





        if (isSafe(grid, row, col, num)==1)

        {



            grid[row][col] = num;





            if (solveSudoku(grid, row, col + 1)==1)

                return 1; }
        grid[row][col] = 0;

    }

    return 0;
}



















/// Proc�dure qui attend qu'un �v�nement se produise � l'�cran principal
void attenteEcranPrincipal(SDL_Renderer* renderer, bool *finDuProgramme) {
    SDL_Event event;
    Uint8 *etatTouche;

    // Tant que la fermeture du programme n'a pas été demandée on récupère les événements
    while (!(*finDuProgramme)) {
        // Récupération des événements
        SDL_WaitEvent(&event);
        etatTouche = SDL_GetKeyboardState(NULL);

        // Vérification des événements
        switch (event.type) {
            // Arrêt du programme si la fenêtre est fermée
            case SDL_QUIT:
                *finDuProgramme = true;
                break;

                // Cas des touches enfoncées
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: // Echap : arrêt du programme
                        *finDuProgramme = true;
                        break;

                    case SDLK_F4: // Alt + F4 : arrêt du programme
                        if (etatTouche[SDL_SCANCODE_LALT] && etatTouche[SDL_SCANCODE_F4]) {
                            *finDuProgramme = true;
                        }
                        break;
                }
                break;

                // Cas des clics de souris relâchés
            case SDL_MOUSEBUTTONUP:
                // Bouton "Nouvelle partie"
                if ((event.button.x >= (800 - 332) / 2) &&
                    (event.button.x <= (800 + 332) / 2) &&
                    (event.button.y >= 225) &&
                    (event.button.y <= 254)) {
                    ecranChoixDifficulte(renderer, finDuProgramme);
                }
                    // Bouton "Reprendre une partie"
                else if ((event.button.x >= (800 - 332) / 2) &&
                         (event.button.x <= (800 + 332) / 2) &&
                         (event.button.y >= 285) &&
                         (event.button.y <= 314)) {
                    ecranJouer(renderer, finDuProgramme, 0);
                }
                    // Bouton "Résoudre une grille"
                else if ((event.button.x >= (800 - 332) / 2) &&
                         (event.button.x <= (800 + 332) / 2) &&
                         (event.button.y >= 345) &&
                         (event.button.y <= 374)) {

                    ecranResolveur(renderer, finDuProgramme);
                }
                break;
        } // Remove the semicolon here
    } // Remove the semicolon here
} // Remove the semicolon here


/// Proc�dure qui attend qu'un �v�nement se produise � l'�cran de choix de
// difficult� herehere
void attenteEcranChoix(SDL_Renderer *renderer, bool *finDuProgramme)
{
    SDL_Event event;
    Uint8 *etatTouche;

    // Tant que la fermeture du programme n'a pas été demandée on récupère les événements
    while (!(*finDuProgramme))
    {
        // Récupération des événements
        SDL_WaitEvent(&event);
        etatTouche = SDL_GetKeyboardState(NULL);

        // Vérification des événements
        switch (event.type)
        {
            // Arrêt du programme si la fenêtre est fermée
            case SDL_QUIT:
                *finDuProgramme = true;
                break;

                // Cas des touches enfoncées
            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Echap : arrêt du programme
                        *finDuProgramme = true;
                        break;

                    case SDLK_F4: // Alt + F4 : arrêt du programme

                        if (etatTouche[SDL_SCANCODE_LALT] && etatTouche[SDL_SCANCODE_F4])
                        {
                            *finDuProgramme = true;
                        }
                        break;
                }
                break;

                // Cas des clics de souris relâchés
            case SDL_MOUSEBUTTONUP:

                // Bouton "Retour"
                if ((event.button.x >= 19) && (event.button.x <= 76) &&
                    (event.button.y >= 19) && (event.button.y <= 45))
                {
//                    printf("ecranPrincipal") ;
                    ecranPrincipal(renderer, finDuProgramme);
                }

                    // Bouton niveau facile
                else if ((event.button.x >= 328) && (event.button.x <= 493) &&
                         (event.button.y >= 110) && (event.button.y <= 173))
                {
                    ecranJouer(renderer, finDuProgramme, 2);
                }

                    // niveau moyen
                else if ((event.button.x >= 328) && (event.button.x <= 493) &&
                         (event.button.y >= 241) && (event.button.y <= 304))
                {
                    ecranJouer(renderer, finDuProgramme, 3);
                }

                    // niveau difficile
                else if ((event.button.x >= 328) && (event.button.x <= 493) &&
                         (event.button.y >= 372) && (event.button.y <= 435))
                {
                    ecranJouer(renderer, finDuProgramme, 4);
                }
                break;
        }
    }
}



/// Proc�dure qui attend qu'un �v�nement se produise � l'�cran de jeu



void attenteEcranJouer(SDL_Renderer *renderer, SDL_Texture *grilleTexture, int grilleSudoku[9][9][10], bool *finDuProgramme) {

    printf("winek");
    fflush(stdout);
    int grid[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = grilleSudoku[i][j][0];
        }
    }



    if (solveSudoku(grid, 0, 0) == 1) {
        printf("nour\n");
        fflush(stdout);
        print(grid);
    }


    else{printf("No solution exists");}


    SDL_Event event;
        const Uint8 *etatTouche;
        int positionX = 0, positionY = 0,
        i = 0,
        grilleDepart[9][9][10] = { { { 0 } } },
        decalage = 0, colonne = 0, ligne = 0;
        char nomDuFichier[TAILLE_MAX] = "";
        copierTableau(grilleSudoku, grilleDepart);
        int textureWidth, textureHeight;

        // Get the width and height of the texture
        SDL_QueryTexture(grilleTexture, NULL, NULL, &textureWidth, &textureHeight);




        int windowWidth, windowHeight;

        // Get the size of the renderer's viewport (usually corresponds to window size)
        SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);



        // Tant que la fermeture du programme n'a pas été demandée, on récupère les événements
        while (!*finDuProgramme) {
            // Récupération des événements
            SDL_WaitEvent(&event);
            etatTouche = SDL_GetKeyboardState(NULL);

            // Vérification des événements
            switch (event.type) {
                // Arrêt du programme si la fenêtre est fermée
                case SDL_QUIT:
                    *finDuProgramme = true;
                    break;
                    // Cas des touches enfoncées
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: // Echap : arrêt du programme
                            *finDuProgramme = true;
                            break;
                        case SDLK_F4: // Alt + F4 : arrêt du programme
                            if (etatTouche[SDL_SCANCODE_LALT] && etatTouche[SDL_SCANCODE_F4]) {
                                *finDuProgramme = true;
                            }
                            break;
                    }
                    break;
                    // Cas des clics de souris relâchés
                case SDL_MOUSEBUTTONUP:
                    // Clic effectué sur une case
//                    printf("souris  %d ,  %d" ,event.button.x , event.button.y ) ;
                    if ((event.button.x > (windowWidth - textureWidth) / 2) &&
                        (event.button.x < (windowWidth + textureWidth) / 2) &&
                        (event.button.y > (windowHeight - textureHeight) / 2) &&
                        (event.button.y < (windowHeight + textureHeight) / 2)) {
                        // Recherche de la ligne et de la colonne de la case cliquée
                        while (positionX == 0 || positionY == 0) {
                            if ((event.button.x < 256 + i * 40 + decalage) && (positionX == 0)) {
                                positionX = 217 + i * 40 + decalage;
                                colonne   = i;
                            }
                            if ((event.button.y < 156 + i * 40 + decalage) && (positionY == 0)) {
                                positionY = 117 + i * 40 + decalage;
                                ligne     = i;
                            }
                            if (i == 2) {
                                decalage += 3;
                            } else if (i == 5) {
                                decalage += 3;
                            }
                            i++;
                        }
//                        here here

                        // Procédure de saisie d'un chiffre dans la case
//                        for (int ligne = 0; ligne < 9; ligne++) {
//                            for (int colonne = 0; colonne < 9; colonne++) {
                                if( grilleDepart[ligne][colonne][0]== 0 ){
//                                    printf("ligne : %d , colonne : %d " , ligne , colonne ) ;

                                        saisirChiffre(renderer, positionX, positionY, finDuProgramme, &(grilleSudoku[ligne][colonne][0]));
//                        printf("positionX : %d ,  positionY : %d  , case : %d " ,positionX ,positionY  , &(grilleSudoku[ligne][colonne][0]));
                        // On efface le cadre rouge
                                        afficherGrilleVierge2(renderer);}
                        // On ré-affiche les solutions
                        afficherSolution(grilleSudoku, renderer);
                        positionX = 0;
                        positionY = 0;
                        decalage  = 0;
                        i         = 0;
                    }
                        // Bouton "Valider"
                    else if ((event.button.x > windowWidth - 170) &&
                             (event.button.x < windowWidth - 20) &&
                             (event.button.y > windowHeight - 40) &&
                             (event.button.y < windowHeight - 20)) {
                        printf("dimesions11 %d  , %d ,  %d  , %d  " ,windowWidth- 170 ,windowWidth - 20 , windowHeight - 40 ,windowHeight - 20  ) ;


                        int niveau = 1, ligne = 0, colonne = 0;
                        // On résout la grille de départ
//                        printf("error55");
                        resolveur(grilleDepart, &niveau);
                        // On compare la grille de d�part r�solue � celle propos�e par
                        // l'utilisateur
                        for (int ligne = 0; ligne < 9; ligne++) {
                            for (int colonne = 0; colonne < 9; colonne++) {
                                printf("%d ", grilleSudoku[ligne][colonne][0]);
                            }
                            printf("\n");
                        }

                        while (grilleDepart[ligne][colonne][0] == grilleSudoku[ligne][colonne][0] && colonne < 9) {
                            ligne++;
                            if (ligne == 9) {
                                ligne = 0;
                                colonne++;
                            }
                        }
                        // Si gagné

                        if (colonne == 9) {
//                            SDL_Surface *victoireSurface = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/victoire.bmp");
//                            SDL_Texture *victoireTexture = SDL_CreateTextureFromSurface(renderer, victoireSurface);
//
//                            SDL_Rect positionVictoire;
//                            SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
//                            positionVictoire.x = (windowWidth - victoireSurface->w) / 2;
//                            positionVictoire.y = (windowHeight - victoireSurface->h) / 2;
//
//                            SDL_RenderCopy(renderer, victoireTexture, NULL, &positionVictoire);
//                            SDL_RenderPresent(renderer);
//
//                            SDL_DestroyTexture(victoireTexture);
//                            SDL_FreeSurface(victoireSurface);


                            int windowWidth, windowHeight;
                            SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

                            // Chargement de l'image du bouton retour
                            SDL_Surface *retour = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/retour.bmp");
                            if (!retour) {
                                printf("Error loading retour image: %s\n", SDL_GetError());
                                return;
                            }
                            // Set color key for transparency
                            SDL_SetColorKey(retour, SDL_TRUE, SDL_MapRGB(retour->format, 255, 0, 255));
                            SDL_Texture *retourTexture = SDL_CreateTextureFromSurface(renderer, retour);
                            // Position du bouton retour

                            SDL_Rect positionRetour = {10, 10, 0, 0};

                            SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
                            positionRetour.x = positionRetour.x;

//    positionRetour.x = windowWidth - retour->w - kafraZoom->w;
                            positionRetour.y = positionRetour.y;
                            positionRetour.w = retour->w;
                            positionRetour.h = retour->h;



                            // Chargement du fond
                            SDL_Surface *victoireSurface = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/victoire.bmp");
                            SDL_Texture *victoire = SDL_CreateTextureFromSurface(renderer, victoireSurface);
                            SDL_FreeSurface(victoireSurface);

                            // Position
                            SDL_Rect positionDefaite = {0, 0, windowWidth, windowHeight};

                            // Affichage
                            SDL_RenderCopy(renderer, victoire, NULL, &positionDefaite);
                            SDL_RenderCopy(renderer, retourTexture, NULL, &positionRetour);

                            // Mise à jour de l'écran
                            SDL_RenderPresent(renderer);

                            // Attente d'événements
                            SDL_Event event;

                            // Tant que la fermeture du programme n'a pas été demandée, on récupère les événements
                            while (!(*finDuProgramme))
                            {
                                // Récupération des événements
                                SDL_WaitEvent(&event);
                                const Uint8 *etatTouche = SDL_GetKeyboardState(NULL);

                                // Vérification des événements
                                switch (event.type)
                                {
                                    // Arrêt du programme si la fenêtre est fermée
                                    case SDL_QUIT:
                                        *finDuProgramme = true;
                                        break;

                                        // Cas des touches enfoncées
                                    case SDL_KEYDOWN:
                                        switch (event.key.keysym.sym)
                                        {
                                            case SDLK_ESCAPE: // Echap : arrêt du programme
                                                *finDuProgramme = true;
                                                break;

                                            case SDLK_F4: // Alt + F4 : arrêt du programme
                                                if (etatTouche[SDL_SCANCODE_LALT] && etatTouche[SDL_SCANCODE_F4])
                                                {
                                                    *finDuProgramme = true;
                                                }
                                                break;
                                        }
                                        break;

                                        // Cas des clics de souris relâchés
                                    case SDL_MOUSEBUTTONUP:
                                        // Bouton "retour"
                                        if ((event.button.x >= 10) && (event.button.x <= 86) &&
                                            (event.button.y >= 10) && (event.button.y <= 56))
                                        {
                                            ecranPrincipal(renderer, finDuProgramme);
                                        }
                                        break;
                                }
                            }
                        }

                            // Sinon perdu
                        else {
                            ecranPerdu(renderer,finDuProgramme);
                    }
                        //Bouton "r�initialiser"
}                     else if ((event.button.x > windowWidth - 340) &&
                               (event.button.x < windowWidth - 20) &&
                               (event.button.y > windowHeight - 40) &&
                               (event.button.y < windowHeight - 20)) {
//                        printf("initialiser");
//                        for (int ligne = 0; ligne < 9; ligne++) {
//                            for (int colonne = 0; colonne < 9; colonne++) {
//                                grilleSudoku[ligne][colonne][0] = 0;
//                            }
//                        }
//                        printf("grilleDepart:\n");
//                        for (int i = 0; i < 9; i++) {
//                            for (int j = 0; j < 9; j++) {
//                                printf("%d ", *grilleDepart[i][j]);
//                            }
//                            printf("\n");
//                        }

                        afficherGrilleVierge2(renderer);
                        afficherSolution(grilleDepart, renderer);
                        copierTableau(grilleDepart, grilleSudoku);
                    }


//                        // Printing the contents of grilleSudoku
//                        printf("\ngrilleSudoku:\n");
//                        for (int i = 0; i < 9; i++) {
//                            for (int j = 0; j < 9; j++) {
//                                printf("%d ", *grilleSudoku[i][j]);
//                            }
//                            printf("\n");
//                        }
//                        afficherGrilleVierge2(renderer);
//                        printf(" #**** ") ;
//                        printf(*grilleDepart) ;
//                        printf(" #**** ") ;
//                        afficherSolution(grilleDepart, renderer);
//                        copierTableau(grilleDepart, grilleSudoku);

                        // Bouton "imprimante"
                    else if ((event.button.x >= 737) && (event.button.x <= 785) &&
                               (event.button.y >= 12) && (event.button.y <= 60)) {
                        impressionEcran(renderer, grilleSudoku);
                        afficherGrilleVierge2(renderer);
                        afficherSolution(grilleSudoku, renderer);
                        // Bouton "Retour"
                    } else if ((event.button.x >= 19) && (event.button.x <= 76) &&
                               (event.button.y >= 19) && (event.button.y <= 45)) {
                        // Si retour � l'�cran de choix alors on enregistre la grille
                        printf("ecranPrincipal") ;
                        strcpy(nomDuFichier, "C:/Users/user/Desktop/libraries/projects/sauvegarde.sdk");
                        FILE *fichier = ecritureFichier(nomDuFichier);
                        exportationGrille(fichier, grilleSudoku);
                        fclose(fichier);
                        ecranChoixDifficulte(renderer, finDuProgramme);
                    }

                    if (*finDuProgramme) {
                        // Si le programme est arr�t� on enregistre la grille
                        strcpy(nomDuFichier, "C:/Users/user/Desktop/libraries/projects/sauvegarde.sdk");
                        FILE *fichier = ecritureFichier(nomDuFichier);
                        exportationGrille(fichier, grilleSudoku);
                        fclose(fichier);
                    }
            }
        }
}

/// Proc�dure qui attend qu'un �v�nement se produise � l'�cran de r�solution de
// grille
void attenteEcranResolveur(SDL_Renderer *renderer,
                           SDL_Texture *grilleTexture,
                           bool *finDuProgramme)
{
//    printf("entered") ;

    int grilleWidth, grilleHeight;
    SDL_QueryTexture(grilleTexture, NULL, NULL, &grilleWidth, &grilleHeight);

    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);



    SDL_Event event;
    Uint8 *etatTouche;
    int positionX = 0, positionY = 0, i = 0, decalage = 0,
            grilleSudoku[9][9][10] = { { { 0 } } }, colonne = 0, ligne = 0;

// Tant que la fermeture du programme n'a pas été demandée, on récupère les événements
    while (!*finDuProgramme)
    {
        // Récupération des événements
        SDL_WaitEvent(&event);
        etatTouche = SDL_GetKeyboardState(NULL);

        // Vérification des événements
        switch (event.type)
        {
            // Arrêt du programme si la fenêtre est fermée
            case SDL_QUIT:
                *finDuProgramme = true;
                break;

                // Cas des touches enfoncées
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Echap : arrêt du programme
                        *finDuProgramme = true;
                        break;

                    case SDLK_F4: // Alt + F4 : arrêt du programme
                        if (etatTouche[SDL_SCANCODE_LALT] && etatTouche[SDL_SCANCODE_F4])
                        {
                            *finDuProgramme = true;
                        }
                        break;
                }
                break;

                // Cas des clics de souris relâchés

            case SDL_MOUSEBUTTONUP:
                // Clic sur une case de la grille
                if ((event.button.x > (windowWidth - grilleWidth) / 2) &&
                    (event.button.x < (windowWidth + grilleWidth) / 2) &&
                    (event.button.y > (windowHeight - grilleHeight) / 2) &&
                    (event.button.y < (windowHeight + grilleHeight) / 2))
                {
                    // Recherche de la ligne et de la colonne de la case cliquée
                    while (positionX == 0 || positionY == 0)
                    {
                        if ((event.button.x < 256 + i * 40 + decalage) && (positionX == 0))
                        {
                            positionX = 217 + i * 40 + decalage;
                            colonne = i;
                        }

                        if ((event.button.y < 156 + i * 40 + decalage) && (positionY == 0))
                        {
                            positionY = 117 + i * 40 + decalage;
                            ligne = i;
                        }

                        if (i == 2)
                        {
                            decalage += 3;
                        }
                        else if (i == 5)
                        {
                            decalage += 3;
                        }
                        i++;
                    }

                    // Saisie du chiffre
                    saisirChiffre(renderer, positionX, positionY, finDuProgramme,
                                  &(grilleSudoku[ligne][colonne][0]));

                    // On efface le cadre rouge
                    afficherGrilleVierge(renderer);

                    // On ré-affiche les solutions
                    afficherSolution(grilleSudoku, renderer);
                    event.button.x = 0;
                    event.button.y = 0;
                    positionX      = 0;
                    positionY      = 0;
                    decalage       = 0;
                    i              = 0;
                    break;
                }
                // Autres cas
                if ((event.button.x > windowWidth - 170) &&
                    (event.button.x < windowWidth - 20) &&
                    (event.button.y > windowHeight - 40) &&
                    (event.button.y < windowHeight - 20))
                {
                    int niveau = 1;
                    resolveur(grilleSudoku, &niveau);
                    afficherSolution(grilleSudoku, renderer);
                }
                else if ((event.button.x > windowWidth - 340) &&
                         (event.button.x < windowWidth - 20) &&
                         (event.button.y > windowHeight - 40) &&
                         (event.button.y < windowHeight - 20))
                {
                    for (ligne = 0; ligne < 9; ligne++)
                    {
                        for (colonne = 0; colonne < 9; colonne++)
                        {
                            grilleSudoku[ligne][colonne][0] = 0;
                        }
                    }
                    afficherGrilleVierge(renderer);
                }
                else if ((event.button.x >= 737) && (event.button.x <= 785) &&
                         (event.button.y >= 12) && (event.button.y <= 60))
                {
                    impressionEcran(renderer, grilleSudoku);
                    afficherGrilleVierge(renderer);
                    afficherSolution(grilleSudoku, renderer);
                }
                else if ((event.button.x >= 19) && (event.button.x <= 76) &&
                         (event.button.y >= 19) && (event.button.y <= 45))
                {
                    ecranPrincipal(renderer, finDuProgramme);
                }
                break;
        }
    }

}



/// Proc�dure qui permet de saisir un chiffre dans la grille
void saisirChiffre(SDL_Renderer *renderer,
                   int positionX,
                   int positionY,
                   bool *finDuProgramme,
                   int *caseChiffre)
{
    // Déclaration des variables
    char nomImage[100] = "C:/Users/user/Desktop/libraries/Assets/img/chiffre0.bmp";
    SDL_Event event;
    char numero = 0;

// Create textures for the red border
    SDL_Texture *cadreLargeur = SDL_CreateTexture(renderer,
                                                  SDL_PIXELFORMAT_RGBA8888,
                                                  SDL_TEXTUREACCESS_TARGET,
                                                  39,
                                                  3);
    SDL_Texture *cadreHauteur = SDL_CreateTexture(renderer,
                                                  SDL_PIXELFORMAT_RGBA8888,
                                                  SDL_TEXTUREACCESS_TARGET,
                                                  3,
                                                  39);

// Set render target to cadreLargeur and fill it with red color
    SDL_SetRenderTarget(renderer, cadreLargeur);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

// Set render target to cadreHauteur and fill it with red color
    SDL_SetRenderTarget(renderer, cadreHauteur);
    SDL_RenderClear(renderer);

// Reset render target to default (the window)
    SDL_SetRenderTarget(renderer, NULL);

// Position of the cadre
    SDL_Rect positionCadre1 = {positionX, positionY, 39,3};
    SDL_Rect positionCadre2 = {positionX, positionY + 36, 39,3};
    SDL_Rect positionCadre3 = {positionX + 36, positionY , 3, 39};
    SDL_Rect positionCadre4 = {positionX, positionY , 3, 39};

// Render the cadre textures onto the screen
    SDL_RenderCopy(renderer, cadreLargeur, NULL, &positionCadre1);
    SDL_RenderCopy(renderer, cadreLargeur, NULL, &positionCadre2);
    SDL_RenderCopy(renderer, cadreHauteur, NULL, &positionCadre3);
    SDL_RenderCopy(renderer, cadreHauteur, NULL, &positionCadre4);

// Update the screen
    SDL_RenderPresent(renderer);

// Free the memory
    SDL_DestroyTexture(cadreLargeur);
    SDL_DestroyTexture(cadreHauteur);

    // Event loop
    while (numero == 0 && !*finDuProgramme) {
        // Récupération des événements
        SDL_WaitEvent(&event);
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // Vérification des événements
        switch (event.type) {
            // Arrêt du programme si la fenêtre est fermée
            case SDL_QUIT:
                *finDuProgramme = true;
                break;

                // Cas des touches enfoncées
            case SDL_KEYDOWN:
                if (state[SDL_SCANCODE_KP_1] || state[SDL_SCANCODE_1]) {
                    numero = '1';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_2] || state[SDL_SCANCODE_2]) {
                    numero = '2';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_3] || state[SDL_SCANCODE_3]) {
                    numero = '3';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_4] || state[SDL_SCANCODE_4]) {
                    numero = '4';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_5] || state[SDL_SCANCODE_5]) {
                    numero = '5';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_6] || state[SDL_SCANCODE_6]) {
                    numero = '6';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_7] || state[SDL_SCANCODE_7]) {
                    numero = '7';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_8] || state[SDL_SCANCODE_8]) {
                    numero = '8';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_9] || state[SDL_SCANCODE_9]) {
                    numero = '9';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                } else if (state[SDL_SCANCODE_KP_0] || state[SDL_SCANCODE_0]) {
                    numero = '0';
//                    printf("keydownnnn %c\n", numero); // Debug statement
                    break;
                }
                break;
                int ligne = 0, colonne = 0;
                // Cas des cliques de souris enfoncés
            case SDL_MOUSEBUTTONDOWN:
                numero = 1;
                // Here, you can handle the mouse button down event.
                // Get the cell coordinates based on the mouse click position
//                int x = event.button.x / CELL_SIZE;
//                int y = event.button.y / CELL_SIZE;

                // Check if the clicked cell contains a given number
//                grilleSudoku


                // On initialise la grille
//                for (ligne = 0; ligne < 9; ligne++)
//                {
//                    for (colonne = 0; colonne < 9; colonne++)
//                    {
//                        grilleSudoku[ligne][colonne][0]==0;
//                    }
//                if (!isGivenCell(x, y)) {
//                    // Cell does not contain a given number, allow the user to change it
//                    // Here, you can implement the logic to allow the user to change the number in the grid
//                    // For this example, we're setting 'numero' to 1.
//                    numero = 1; // You can modify this based on your specific requirement.
//                    // printf("Mouse button down event detected: %c\n", numero); // Debug statement
//                } else {
//                    // Cell contains a given number, ignore user input
//                    // Optionally, you can provide feedback to the user indicating that they cannot change this number
//                    printf("You cannot change a given number.\n");
//                }
                break;
        }
    }
    // Handle the input
    if ((numero != '0') && (numero != 1))
    {
        // Modification
        nomImage[50] = numero;


        // Chargement de l'image du chiffre
        SDL_Surface *chiffreSurface = chargementBitmap(nomImage);
        *caseChiffre = numero - 48; // Convert char to int
        if (!chiffreSurface)
        {
            // Handle error if loading fails
            // You can add your error handling mechanism here
            printf("Unable to load image %s! SDL Error: %s\n", nomImage, SDL_GetError());
            return;
        }

        // Create texture from surface
        SDL_Texture *chiffreTexture = SDL_CreateTextureFromSurface(renderer, chiffreSurface);
        SDL_FreeSurface(chiffreSurface); // Free surface after creating texture
        if (!chiffreTexture)
        {
            // Handle error if texture creation fails
            // You can add your error handling mechanism here
            printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
            return;
        }

        // Position du chiffre
        SDL_Rect positionChiffre = {positionX, positionY, 0, 0}; // Adjust as needed

        // On affiche l'image du chiffre
        SDL_QueryTexture(chiffreTexture, NULL, NULL, &positionChiffre.w, &positionChiffre.h);
        SDL_RenderCopy(renderer, chiffreTexture, NULL, &positionChiffre);

        // On actualise l'écran
        SDL_RenderPresent(renderer);

        // On libère la mémoire
        SDL_DestroyTexture(chiffreTexture);
    }
    else if (numero == '0')
    {
        // On réinitialise la case à 0
        *caseChiffre = 0;
    }
}