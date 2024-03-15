#include "ecrans.h"
#include "SDL_render.h"



//#include <stdio.h>
//#include <stdlib.h>
//# define N 9
///// G�n�rateur de grille de sudoku
//
//
//void print(int arr[N][N])
//{
//
//    for (int i = 0; i < N; i++)
//
//    {
//
//        for (int j = 0; j < N; j++)
//
//            printf("%d ",arr[i][j]);
//
//        printf("\n");
//
//    }
//}
//
//int isSafe(int grid[N][N], int row,
//
//           int col, int num)
//{
//
//
//
//    for (int x = 0; x <= 8; x++)
//
//        if (grid[row][x] == num)
//
//            return 0;
//
//
//
//
//    for (int x = 0; x <= 8; x++)
//
//        if (grid[x][col] == num)
//
//            return 0;
//
//
//
//
//    int startRow = row - row % 3,
//
//            startCol = col - col % 3;
//
//
//
//    for (int i = 0; i < 3; i++)
//
//        for (int j = 0; j < 3; j++)
//
//            if (grid[i + startRow][j + startCol] == num)
//
//                return 0;
//
//
//    return 1;
//}
//
//int solveSudoku(int grid[N][N], int row, int col)
//{
//
//
//
//    if (row == N - 1 && col == N)
//
//        return 1;
//
//
//
//    if (col == N)
//
//    {
//
//        row++;
//
//        col = 0;
//
//    }
//
//
//    if (grid[row][col] > 0)
//
//        return solveSudoku(grid, row, col + 1);
//
//
//    for (int num = 1; num <= N; num++)
//
//    {
//
//
//
//
//
//        if (isSafe(grid, row, col, num)==1)
//
//        {
//
//
//
//            grid[row][col] = num;
//
//
//
//
//
//            if (solveSudoku(grid, row, col + 1)==1)
//
//                return 1; }
//        grid[row][col] = 0;
//
//    }
//
//    return 0;
//}
//
//
//
//





void ecranPrincipal(SDL_Renderer* renderer, bool* finDuProgramme) {
    SDL_Event event;

    // Chargement des textures
    SDL_Surface* fondEcran = SDL_LoadBMP("C:/Users/user/Desktop/libraries/Assets/img/fondEcran1.bmp");
    if (fondEcran == NULL) {
        fprintf(stderr, "Unable to load background image: %s\n", SDL_GetError());
        return;
    }

    // Chargement de l'illustration de la Kafra
    SDL_Surface* kafraZoom = SDL_LoadBMP("C:/Users/user/Desktop/libraries/Assets/img/kafraZoom.bmp");
    if (kafraZoom == NULL) {
        fprintf(stderr, "Unable to load Kafra image: %s\n", SDL_GetError());
        SDL_FreeSurface(fondEcran);
        return;
    }

    // Chargement de l'illustration de la bulle
    SDL_Surface* bulle = SDL_LoadBMP("C:/Users/user/Desktop/libraries/Assets/img/bulleAccueil.bmp");
    if (bulle == NULL) {
        fprintf(stderr, "Unable to load bubble image: %s\n", SDL_GetError());
        SDL_FreeSurface(fondEcran);
        SDL_FreeSurface(kafraZoom);
        return;
    }

    // Chargement du bouton "nouvelle partie"
    SDL_Surface* nouvellePartie = SDL_LoadBMP("C:/Users/user/Desktop/libraries/Assets/img/nouvellePartie.bmp");
    if (nouvellePartie == NULL) {
        fprintf(stderr, "Unable to load new game button image: %s\n", SDL_GetError());
        SDL_FreeSurface(fondEcran);
        SDL_FreeSurface(kafraZoom);
        SDL_FreeSurface(bulle);
        return;
    }

    // Chargement du bouton "Reprendre une partie"
    SDL_Surface* chargerPartie = SDL_LoadBMP("C:/Users/user/Desktop/libraries/Assets/img/reprendrePartie.bmp");
    if (chargerPartie == NULL) {
        fprintf(stderr, "Unable to load resume game button image: %s\n", SDL_GetError());
        SDL_FreeSurface(fondEcran);
        SDL_FreeSurface(kafraZoom);
        SDL_FreeSurface(bulle);
        SDL_FreeSurface(nouvellePartie);
        return;
    }

    // Chargement du bouton "Résoudre une grille"
//    SDL_Surface* resoudreGrille = SDL_LoadBMP("C:/Users/user/Desktop/libraries/Assets/img/resoudreGrille.bmp");
//    if (resoudreGrille == NULL) {
//        fprintf(stderr, "Unable to load solve grid button image: %s\n", SDL_GetError());
//        SDL_FreeSurface(fondEcran);
//        SDL_FreeSurface(kafraZoom);
//        SDL_FreeSurface(bulle);
//        SDL_FreeSurface(nouvellePartie);
//        SDL_FreeSurface(chargerPartie);
//        return;
//    }

    // Positionnement des éléments
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_Rect positionFond;
    SDL_GetRendererOutputSize(renderer, &positionFond.w, &positionFond.h);
    positionFond.x = 0;
    positionFond.y = 0;

    SDL_Rect positionKafraZoom = {windowWidth - kafraZoom->w, windowHeight - kafraZoom->h, kafraZoom->w, kafraZoom->h};
    SDL_Rect positionBulle = {windowWidth - bulle->w - kafraZoom->w, windowHeight - bulle->h, bulle->w, bulle->h};
    SDL_Rect positionNouvellePartie = {(windowWidth - nouvellePartie->w) / 2, (windowHeight - 5 * nouvellePartie->h) / 2, nouvellePartie->w, nouvellePartie->h};
    SDL_Rect positionChargerPartie = {(windowWidth - chargerPartie->w) / 2, (windowHeight - chargerPartie->h) / 2, chargerPartie->w, chargerPartie->h};
//    SDL_Rect positionResoudreGrille = {(windowWidth - resoudreGrille->w) / 2, (windowHeight + 3 * resoudreGrille->h) / 2, resoudreGrille->w, resoudreGrille->h};

    // Transparences
    SDL_SetColorKey(kafraZoom, SDL_TRUE, SDL_MapRGB(kafraZoom->format, 255, 0, 255));
    SDL_SetColorKey(nouvellePartie, SDL_TRUE, SDL_MapRGB(nouvellePartie->format, 255, 0, 255));
    SDL_SetColorKey(chargerPartie, SDL_TRUE, SDL_MapRGB(chargerPartie->format, 255, 0, 255));
//    SDL_SetColorKey(resoudreGrille, SDL_TRUE, SDL_MapRGB(resoudreGrille->format, 255, 0, 255));
    SDL_SetColorKey(bulle, SDL_TRUE, SDL_MapRGB(bulle->format, 255, 0, 255));

    // On affiche les images dans cet ordre
    SDL_Texture* fondTexture = SDL_CreateTextureFromSurface(renderer, fondEcran);
    SDL_RenderCopy(renderer, fondTexture, NULL, &positionFond);

    SDL_Texture* kafraTexture = SDL_CreateTextureFromSurface(renderer, kafraZoom);
    SDL_RenderCopy(renderer, kafraTexture, NULL, &positionKafraZoom);

    SDL_Texture* bulleTexture = SDL_CreateTextureFromSurface(renderer, bulle);
    SDL_RenderCopy(renderer, bulleTexture, NULL, &positionBulle);

    SDL_Texture* nouvellePartieTexture = SDL_CreateTextureFromSurface(renderer, nouvellePartie);
    SDL_RenderCopy(renderer, nouvellePartieTexture, NULL, &positionNouvellePartie);

    SDL_Texture* chargerPartieTexture = SDL_CreateTextureFromSurface(renderer, chargerPartie);
    SDL_RenderCopy(renderer, chargerPartieTexture, NULL, &positionChargerPartie);

//    SDL_Texture* resoudreGrilleTexture = SDL_CreateTextureFromSurface(renderer, resoudreGrille);
//    SDL_RenderCopy(renderer, resoudreGrilleTexture, NULL, &positionResoudreGrille);

    SDL_RenderPresent(renderer);

    // En attente d'événements
    attenteEcranPrincipal(renderer, finDuProgramme);

    // Libérer les ressources
    SDL_FreeSurface(fondEcran);
    SDL_FreeSurface(kafraZoom);
    SDL_FreeSurface(bulle);
    SDL_FreeSurface(nouvellePartie);
    SDL_FreeSurface(chargerPartie);
//    SDL_FreeSurface(resoudreGrille);

    // Destroy textures
    SDL_DestroyTexture(fondTexture);
    SDL_DestroyTexture(kafraTexture);
    SDL_DestroyTexture(bulleTexture);
    SDL_DestroyTexture(nouvellePartieTexture);
    SDL_DestroyTexture(chargerPartieTexture);
//    SDL_DestroyTexture(resoudreGrilleTexture);
}

/// Choix difficult�
void ecranChoixDifficulte(SDL_Renderer *renderer, bool *finDuProgramme) {
    // Chargement de l'image du fond d'écran
    SDL_Surface *fondEcran = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/fondEcranChoix.bmp");
    if (!fondEcran) {
        printf("Error loading background image: %s\n", SDL_GetError());
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(fondEcran, SDL_TRUE, SDL_MapRGB(fondEcran->format, 255, 0, 255));
    SDL_Texture *fondTexture = SDL_CreateTextureFromSurface(renderer, fondEcran);

    // Position du fond d'écran
    SDL_Rect positionFond = {0, 0, 0, 0};
    SDL_QueryTexture(fondTexture, NULL, NULL, &positionFond.w, &positionFond.h);

    // Chargement de l'illustration de la Kafra
    SDL_Surface *kafraZoom = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/kafraZoom.bmp");
    if (!kafraZoom) {
        printf("Error loading Kafra image: %s\n", SDL_GetError());
        // Handle error, perhaps return from the function or clean up resources
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(kafraZoom, SDL_TRUE, SDL_MapRGB(kafraZoom->format, 255, 0, 255));
    SDL_Texture *kafraTexture = SDL_CreateTextureFromSurface(renderer, kafraZoom);

    // Position de l'illustration de la Kafra
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_Rect positionKafraZoom = {windowWidth - kafraZoom->w, windowHeight - kafraZoom->h, kafraZoom->w, kafraZoom->h};

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
    positionRetour.x = 10;

//    positionRetour.x = windowWidth - retour->w - kafraZoom->w;
    positionRetour.y = 10 ;
    positionRetour.w = retour->w;
    positionRetour.h = retour->h;

    // Chargement de la bulle
    SDL_Surface *bulle = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/bulleDifficulte.bmp");
    if (!bulle) {
        printf("Error loading bulle image: %s\n", SDL_GetError());
        // Handle error, perhaps return from the function or clean up resources
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(bulle, SDL_TRUE, SDL_MapRGB(bulle->format, 255, 0, 255));
    SDL_Texture *bulleTexture = SDL_CreateTextureFromSurface(renderer, bulle);

    // Position of the bubble
    SDL_Rect positionBulle = {0, 0, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionBulle.x = windowWidth - bulle->w - kafraZoom->w;
    positionBulle.y = windowHeight - bulle->h;
    positionBulle.w = bulle->w;
    positionBulle.h = bulle->h;

    // Chargement du perso Facile
    SDL_Surface *persoFacile = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/persoFacile.bmp");
    if (!persoFacile) {
        printf("Error loading persoFacile image: %s\n", SDL_GetError());
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(persoFacile, SDL_TRUE, SDL_MapRGB(persoFacile->format, 255, 0, 255));
    SDL_Texture *persoFacileTexture = SDL_CreateTextureFromSurface(renderer, persoFacile);

    // Position
    SDL_Rect positionPersoFacile = {0, 0, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionPersoFacile.x = 260;
    positionPersoFacile.y = 0.9 * (windowHeight - persoFacile->h) / 5;
    positionPersoFacile.w = persoFacile->w;
    positionPersoFacile.h = persoFacile->h;

    // Chargement du perso Moyen
    SDL_Surface *persoMoyen = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/persoMoyen.bmp");
    if (!persoMoyen) {
        printf("Error loading persoMoyen image: %s\n", SDL_GetError());
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(persoMoyen, SDL_TRUE, SDL_MapRGB(persoMoyen->format, 255, 0, 255));
    SDL_Texture *persoMoyenTexture = SDL_CreateTextureFromSurface(renderer, persoMoyen);

    // Position
    SDL_Rect positionPersoMoyen = {0, 0, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionPersoMoyen.x = windowWidth - persoMoyen->w - kafraZoom->w;
    positionPersoMoyen.y = (int)(2.3 * (windowHeight - persoMoyen->h) / 5);
    positionPersoMoyen.w = persoMoyen->w;
    positionPersoMoyen.h = persoMoyen->h;

    // Chargement du perso Difficile
    SDL_Surface *persoDifficile = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/persoDifficile.bmp");
    if (!persoDifficile) {
        printf("Error loading persoDifficile image: %s\n", SDL_GetError());
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(persoDifficile, SDL_TRUE, SDL_MapRGB(persoDifficile->format, 255, 0, 255));
    SDL_Texture *persoDifficileTexture = SDL_CreateTextureFromSurface(renderer, persoDifficile);

    // Position
    SDL_Rect positionPersoDifficile = {0, 0, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionPersoDifficile.x = 260;
    positionPersoDifficile.y = 3.5 * (windowHeight - persoDifficile->h) / 5;
    positionPersoDifficile.w = persoDifficile->w;
    positionPersoDifficile.h = persoDifficile->h;

    // Chargement du bouton facile
    SDL_Surface *facile = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/facile.bmp");
    if (!facile) {
        printf("Error loading facile image: %s\n", SDL_GetError());
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(facile, SDL_TRUE, SDL_MapRGB(facile->format, 255, 0, 255));
    SDL_Texture *facileTexture = SDL_CreateTextureFromSurface(renderer, facile);

    // Position
    SDL_Rect positionFacile = {0, 0, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionFacile.x = 325;
    positionFacile.y = (windowHeight - facile->h) / 5;
    positionFacile.w = facile->w;
    positionFacile.h = facile->h;

    // Chargement du bouton difficile
    SDL_Surface *difficile = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/difficile.bmp");
    if (!difficile) {
        printf("Error loading difficile image: %s\n", SDL_GetError());
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(difficile, SDL_TRUE, SDL_MapRGB(difficile->format, 255, 0, 255));
    SDL_Texture *difficileTexture = SDL_CreateTextureFromSurface(renderer, difficile);

    // Position
    SDL_Rect positionDifficile = {0, 0, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionDifficile.x = 325;
    positionDifficile.y = (int)(3.5 * (windowHeight - difficile->h) / 5);
    positionDifficile.w = difficile->w;
    positionDifficile.h = difficile->h;

    // Chargement du bouton moyen
    SDL_Surface *moyen = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/moyen.bmp");
    if (!moyen) {
        printf("Error loading moyen image: %s\n", SDL_GetError());
        return;
    }
    // Set color key for transparency
    SDL_SetColorKey(moyen, SDL_TRUE, SDL_MapRGB(moyen->format, 255, 0, 255));
    SDL_Texture *moyenTexture = SDL_CreateTextureFromSurface(renderer, moyen);

    // Position
    SDL_Rect positionMoyen = {0, 0, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionMoyen.x = 325;
    positionMoyen.y = (int)(2.25 * (windowHeight - moyen->h) / 5);
    positionMoyen.w = moyen->w;
    positionMoyen.h = moyen->h;

    // On affiche les images
    SDL_RenderCopy(renderer, fondTexture, NULL, &positionFond);
    SDL_RenderCopy(renderer, kafraTexture, NULL, &positionKafraZoom);
    SDL_RenderCopy(renderer, bulleTexture, NULL, &positionBulle);
    SDL_RenderCopy(renderer, retourTexture, NULL, &positionRetour);
    SDL_RenderCopy(renderer, persoDifficileTexture, NULL, &positionPersoDifficile);
    SDL_RenderCopy(renderer, persoFacileTexture, NULL, &positionPersoFacile);
    SDL_RenderCopy(renderer, persoMoyenTexture, NULL, &positionPersoMoyen);
    SDL_RenderCopy(renderer, difficileTexture, NULL, &positionDifficile);
    SDL_RenderCopy(renderer, facileTexture, NULL, &positionFacile);
    SDL_RenderCopy(renderer, moyenTexture, NULL, &positionMoyen);

    // Mise à jour de l'écran
    SDL_RenderPresent(renderer);

    // En attente d'événements
    attenteEcranChoix(renderer, finDuProgramme);

    // On libère les textures
    SDL_DestroyTexture(retourTexture);
    SDL_DestroyTexture(fondTexture);
    SDL_DestroyTexture(kafraTexture);
    SDL_DestroyTexture(bulleTexture);
    SDL_DestroyTexture(persoDifficileTexture);
    SDL_DestroyTexture(persoFacileTexture);
    SDL_DestroyTexture(persoMoyenTexture);
    SDL_DestroyTexture(difficileTexture);
    SDL_DestroyTexture(facileTexture);
    SDL_DestroyTexture(moyenTexture);
}



/// �cran de jeu
void ecranJouer(SDL_Renderer *renderer, bool *finDuProgramme, int niveau) {

    // Chargement de l'image du fond d'écran
    SDL_Surface *fondEcran = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/fondGrille.bmp");
    SDL_SetColorKey(fondEcran, SDL_TRUE, SDL_MapRGB(fondEcran->format, 255, 0, 255));
    SDL_Texture *fondTexture = SDL_CreateTextureFromSurface(renderer, fondEcran);

    // Position du fond d'écran
    SDL_Rect positionFond = {0, 0, 0, 0};
    SDL_QueryTexture(fondTexture, NULL, NULL, &positionFond.w, &positionFond.h);

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
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionRetour.w = retour->w;
    positionRetour.h = retour->h;


    // Chargement du bouton imprimante  truc : imporatation de l'image->  transparence -> texture
    SDL_Surface *imprimante = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/imprimante.bmp");
    SDL_SetColorKey(imprimante, SDL_TRUE, SDL_MapRGB(retour->format, 255, 0, 255));
    SDL_Texture *imprimanteTexture = SDL_CreateTextureFromSurface(renderer, imprimante);


    // Position du bouton imprimante
    SDL_Rect positionImprimante = {785 - imprimante->w, 12, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionImprimante.w = imprimante->w;
    positionImprimante.h = imprimante->h;




    // Chargement de la grille
    SDL_Surface *grille = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/grilleVierge.bmp");
    SDL_Texture *grilleTexture = SDL_CreateTextureFromSurface(renderer, grille);


    // Position de la grille

        SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
        SDL_Rect positionGrille = {(windowWidth - grille->w) / 2, (windowHeight - grille->h) / 2, grille->w, grille->h};
        SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
        positionGrille.w = grille->w;
        positionGrille.h = grille->w;

    // Chargement du bouton valider
    SDL_Surface *resoudre = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/valider.bmp");
    SDL_SetColorKey(resoudre, SDL_TRUE, SDL_MapRGB(resoudre->format, 255, 0, 255));
    SDL_Texture *resoudreTexture = SDL_CreateTextureFromSurface(renderer, resoudre);

    // Position du bouton valider
    int resoudreTextureWidth, resoudreTextureHeight;
    SDL_QueryTexture(resoudreTexture, NULL, NULL, &resoudreTextureWidth, &resoudreTextureHeight);

// New position calculation
    SDL_Rect positionResoudre = {
            (windowWidth -170),
            (windowHeight - 40) ,
            resoudreTextureWidth,
            resoudreTextureHeight
    };


    printf("dimensions1 %d  , %d ,  %d  , %d  " ,positionResoudre.x ,positionResoudre.y ,positionResoudre.w ,positionResoudre.h  ) ;


    // Chargement du bouton réinitialiser
    SDL_Surface *reinitialiser = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/reinitialiser.bmp");
    SDL_SetColorKey(reinitialiser, SDL_TRUE, SDL_MapRGB(reinitialiser->format, 255, 0, 255));
    SDL_Texture *reinitialiserTexture = SDL_CreateTextureFromSurface(renderer, reinitialiser);

    // Position du bouton réinitialiser

    SDL_Rect positionReinitialiser = {
            (windowWidth - 340) ,
            (windowHeight - 40) ,
            resoudreTextureWidth,
            resoudreTextureHeight
    };
//    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
//    positionReinitialiser.x = positionReinitialiser.x;
//    positionReinitialiser.y = positionReinitialiser.y;
//    positionReinitialiser.w = positionReinitialiser.w; // Set to 0 if the width is not specified
//    positionReinitialiser.h = positionReinitialiser.h; // Set to 0 if the height is not specified
    printf("dimensions2 %d  , %d ,  %d  , %d  " ,positionReinitialiser.x ,positionReinitialiser.y ,positionReinitialiser.w ,positionReinitialiser.h  ) ;


    // Opacité de la grille
    SDL_SetSurfaceAlphaMod(grille, 190);

    // On affiche les images
    SDL_RenderCopy(renderer, fondTexture, NULL, &positionFond);
    SDL_RenderCopy(renderer, grilleTexture, NULL, &positionGrille);
    SDL_RenderCopy(renderer, retourTexture, NULL, &positionRetour);
    SDL_RenderCopy(renderer, resoudreTexture, NULL, &positionResoudre);
    SDL_RenderCopy(renderer, reinitialiserTexture, NULL, &positionReinitialiser);
    SDL_RenderCopy(renderer, imprimanteTexture, NULL, &positionImprimante);

    // Mise à jour de l'écran
    SDL_RenderPresent(renderer);

    // Soit on crée une nouvelle partie si un niveau a été choisi soit on reprend
    // la partie précédente
    int grilleSudoku[9][9][10] = { { { 0 } } };

    if (niveau != 0) {
        generateur(grilleSudoku, &niveau);
    } else {
        char nomDuFichier[TAILLE_MAX] = "C:/Users/user/Desktop/libraries/projects/sauvegarde.sdk";
        FILE *fichier = lectureFichier(nomDuFichier);
        importationGrille(fichier, grilleSudoku);
    }

    // On affiche les solutions à l'écran
    afficherSolution(grilleSudoku, renderer);




//    // En attente d'événements
    attenteEcranJouer(renderer,  grilleTexture, grilleSudoku, finDuProgramme);
//    printf("winek");
//    fflush(stdout);
//    int grid[N][N];
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            grid[i][j] = grilleSudoku[i][j][0];
//        }
//    }
//
//
//
//    if (solveSudoku(grid, 0, 0)==1){ printf("nour") ; print(grid);}
//
//    else{printf("No solution exists");}

    // On libère les textures
    SDL_DestroyTexture(fondTexture);
    SDL_DestroyTexture(grilleTexture);
    SDL_DestroyTexture(retourTexture);
    SDL_DestroyTexture(resoudreTexture);
    SDL_DestroyTexture(reinitialiserTexture);
    SDL_DestroyTexture(imprimanteTexture);
}




/// �cran de "R�soudre une grille"
void ecranResolveur(SDL_Renderer *renderer, bool *finDuProgramme)
{
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);


    // Chargement de l'image du fond d'écran
    SDL_Surface *fondEcran = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/fondGrille.bmp");
    SDL_Texture *fondTexture = SDL_CreateTextureFromSurface(renderer, fondEcran);
    // Position du fond d'écran
    SDL_Rect positionFond = {0, 0, 0, 0};
    SDL_QueryTexture(fondTexture, NULL, NULL, &positionFond.w, &positionFond.h);

//grille

    // Chargement de la grille
    SDL_Surface *grille = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/grilleVierge.bmp");
    SDL_Texture *grilleTexture = SDL_CreateTextureFromSurface(renderer, grille);


    // Position de la grille

    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_Rect positionGrille = {(windowWidth - grille->w) / 2, (windowHeight - grille->h) / 2, grille->w, grille->h};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionGrille.w = grille->w;
    positionGrille.h = grille->w;


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

    positionRetour.w = retour->w;
    positionRetour.h = retour->h;





    // Chargement de l'image du bouton imprimante
    SDL_Surface *imprimante = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/imprimante.bmp");
    SDL_SetColorKey(imprimante, SDL_TRUE, SDL_MapRGB(retour->format, 255, 0, 255));
    SDL_Texture *imprimanteTexture = SDL_CreateTextureFromSurface(renderer, imprimante);

    // Position du bouton
    int imprimanteWidth, imprimanteHeight;
    SDL_QueryTexture(imprimanteTexture, NULL, NULL, &imprimanteWidth, &imprimanteHeight);
    SDL_Rect positionImprimante = {785 - imprimanteWidth, 12, 0, 0};
    positionImprimante.w = imprimante->w;
    positionImprimante.h = imprimante->h;





    // Chargement du bouton résoudre
    SDL_Surface *resoudre = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/resoudre.bmp");
    SDL_SetColorKey(resoudre, SDL_TRUE, SDL_MapRGB(resoudre->format, 255, 0, 255));
    SDL_Texture *resoudreTexture = SDL_CreateTextureFromSurface(renderer, resoudre);
    int resoudreTextureWidth, resoudreTextureHeight;
    SDL_QueryTexture(resoudreTexture, NULL, NULL, &resoudreTextureWidth, &resoudreTextureHeight);


    // Position du bouton résoudre
    SDL_Rect positionResoudre = {
            (windowWidth -170),
            (windowHeight - 40) ,
            resoudreTextureWidth,
            resoudreTextureHeight
    };

    // Chargement du bouton réinitialise
    SDL_Surface *reinitialiser = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/reinitialiser.bmp");
    SDL_SetColorKey(reinitialiser, SDL_TRUE, SDL_MapRGB(reinitialiser->format, 255, 0, 255));
    SDL_Texture *reinitialiserTexture = SDL_CreateTextureFromSurface(renderer, reinitialiser);

    // Position du bouton réinitialise
    SDL_Rect positionReinitialiser = {
            (windowWidth - 340) ,
            (windowHeight - 40) ,
            resoudreTextureWidth,
            resoudreTextureHeight
    };



    // On affiche les images
    SDL_RenderCopy(renderer, fondTexture, NULL, &positionFond);
    SDL_RenderCopy(renderer, grilleTexture, NULL, &positionGrille);
    SDL_RenderCopy(renderer, retourTexture, NULL, &positionRetour);
    SDL_RenderCopy(renderer, resoudreTexture, NULL, &positionResoudre);
    SDL_RenderCopy(renderer, reinitialiserTexture, NULL, &positionReinitialiser);
    SDL_RenderCopy(renderer, imprimanteTexture, NULL, &positionImprimante);

    // Mise à jour de l'écran
    SDL_RenderPresent(renderer);

//    // En attente d'événements
    attenteEcranResolveur(renderer, fondTexture, finDuProgramme);

    // On libère les textures
    SDL_DestroyTexture(fondTexture);
    SDL_DestroyTexture(grilleTexture);
    SDL_DestroyTexture(retourTexture);
    SDL_DestroyTexture(imprimanteTexture);
    SDL_DestroyTexture(resoudreTexture);
    SDL_DestroyTexture(reinitialiserTexture);
}




// �cran de la d�faite
void ecranPerdu(SDL_Renderer *renderer, bool *finDuProgramme)
{
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
    SDL_Surface *defaiteSurface = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/defaite.bmp");
    SDL_Texture *defaite = SDL_CreateTextureFromSurface(renderer, defaiteSurface);
    SDL_FreeSurface(defaiteSurface);

    // Position
    SDL_Rect positionDefaite = {0, 0, windowWidth, windowHeight};

    // Affichage
    SDL_RenderCopy(renderer, defaite, NULL, &positionDefaite);
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

    // Libération des textures
    SDL_DestroyTexture(defaite);
    SDL_DestroyTexture(retourTexture);
}

