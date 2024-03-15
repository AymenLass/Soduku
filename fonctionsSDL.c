#include "fonctionsSDL.h"

/// Proc�dure qui initialise la SDL
void initialisationSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
}

/// Fonction qui retourne la cr�ation d'une fen�tre en 640x480 32bits/pixel
// utilisant la RAM de la carte graphique et le double buffering
SDL_Window* creationEcran(int hauteur, int largeur) {
    // Création d'une nouvelle fenêtre à l'écran
    SDL_Window  *ecran = SDL_CreateWindow("Your Window Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, hauteur, largeur, SDL_WINDOW_SHOWN);

    if (ecran == NULL) { // Si la fenêtre n'existe pas alors :
        // On écrit l'erreur dans un fichier
        fprintf(stderr, "Impossible de créer la fenêtre SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE); // On quitte le programme
    }
    return ecran;
}


/// On effectue une impression de l'�cran en affichant temporairement � l'�cran
// seulement la grille et un fond blanc que l'on enregistre ensuite dans un
// fichier bmp
void impressionEcran(SDL_Renderer* renderer, int grilleSudoku[9][9][10]) {
    SDL_Texture *fondBlanc = SDL_CreateTexture(renderer,
                                               SDL_PIXELFORMAT_RGBA8888,
                                               SDL_TEXTUREACCESS_TARGET,
                                               800,
                                               600);

// Set render target to fondBlanc and fill it with white color
    SDL_SetRenderTarget(renderer, fondBlanc);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

// Reset render target to default (the window)
    SDL_SetRenderTarget(renderer, NULL);

// Position of the fond
    SDL_Rect positionFond = {0, 0 , 0 , 0};

// Load the grille texture
    SDL_Surface *grilleSurface = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/grilleVierge.bmp");
    if (!grilleSurface)
    {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        return;
    }
    SDL_SetColorKey(grilleSurface, SDL_TRUE, SDL_MapRGB(grilleSurface->format, 255, 255, 255));
    SDL_Texture *grille = SDL_CreateTextureFromSurface(renderer, grilleSurface);

// Query the grille texture's width and height
    int grilleWidth, grilleHeight;
    SDL_QueryTexture(grille, NULL, NULL, &grilleWidth, &grilleHeight);

// Position of the grille
    SDL_Rect positionGrille = {(800 - grilleWidth) / 2, (600 - grilleHeight) / 2};

// Render the fond and grille textures onto the screen
    SDL_RenderCopy(renderer, fondBlanc, NULL, &positionFond);
    SDL_RenderCopy(renderer, grille, NULL, &positionGrille);

// Render any additional content here, such as the solution grid

// Update the screen
    SDL_RenderPresent(renderer);

// Save the rendered content to a bitmap file
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 800, 600, 32, SDL_PIXELFORMAT_RGBA8888);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface,  "C:/Users/user/Desktop/libraries/Assets/img/impression_grille.bmp");
    SDL_FreeSurface(surface);

// Free the memory
    SDL_DestroyTexture(fondBlanc);
    SDL_DestroyTexture(grille);
}





/// Fonction qui retourne une surface contenant une image charg�e au format
// bitmap
SDL_Surface* chargementBitmap( char* filename) {
    // Load image from file
    SDL_Surface* loadedSurface = SDL_LoadBMP(filename);
    if (loadedSurface == NULL) {
        fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
        return NULL;
    }

    return loadedSurface;
}

/// Proc�dure qui permet d'afficher au centre de l'�cran une grille de sudoku
// vierge sur l'�cran du r�solveur



void afficherGrilleVierge(SDL_Renderer *renderer)
{
    // Chargement du fond d'écran avec transparence
    SDL_Surface *fondSurface = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/fondGrille.bmp");
    if (!fondSurface)
    {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        return;
    }
    SDL_SetColorKey(fondSurface, SDL_TRUE, SDL_MapRGB(fondSurface->format, 255, 255, 255));
    SDL_Texture *fondEcran = SDL_CreateTextureFromSurface(renderer, fondSurface);


    // Chargement de la grille avec transparence
    SDL_Surface *grilleSurface = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/grilleVierge.bmp");
    if (!grilleSurface)
    {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        return;
    }
    SDL_SetColorKey(grilleSurface, SDL_TRUE, SDL_MapRGB(grilleSurface->format, 255, 255, 255));
    SDL_Texture *grille = SDL_CreateTextureFromSurface(renderer, grilleSurface);


    // Chargement des autres images
    SDL_Surface *retour = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/retour.bmp");
    SDL_Surface *imprimante = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/imprimante.bmp");
    SDL_Surface *resoudre = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/resoudre.bmp");
    SDL_Surface *reinitialiser = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/reinitialiser.bmp");

    SDL_Texture *retourTexture = SDL_CreateTextureFromSurface(renderer, retour);
    SDL_Texture *imprimanteTexture = SDL_CreateTextureFromSurface(renderer, imprimante);
    SDL_Texture *resoudreTexture = SDL_CreateTextureFromSurface(renderer, resoudre);
    SDL_Texture *reinitialiserTexture = SDL_CreateTextureFromSurface(renderer, reinitialiser);
// Set color key for transparency
    SDL_SetTextureBlendMode(retourTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(imprimanteTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(resoudreTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(reinitialiserTexture, SDL_BLENDMODE_BLEND);


// Calcul des positions des images
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    int imprimanteWidth, imprimanteHeight;
    SDL_QueryTexture(imprimanteTexture, NULL, NULL, &imprimanteWidth, &imprimanteHeight);

    SDL_Rect positionFond = {0, 0, 0, 0};
    SDL_Rect positionRetour = {10, 10, 0, 0};
    SDL_Rect positionImprimante = {785 - imprimanteWidth, 12, 0, 0};
    SDL_Rect positionGrille = {(windowWidth - 800) / 2, (windowHeight - 600) / 2, 800, 600};
    SDL_Rect positionResoudre = {windowWidth - 170, windowHeight - 40, 0, 0};
    SDL_Rect positionReinitialiser = {windowWidth - 340, windowHeight - 40, 0, 0};

    // Affichage des images
    SDL_RenderCopy(renderer, fondEcran, NULL, &positionFond);
    SDL_RenderCopy(renderer, grille, NULL, &positionGrille);
    SDL_RenderCopy(renderer, retourTexture, NULL, &positionRetour);
    SDL_RenderCopy(renderer, imprimanteTexture, NULL, &positionImprimante);
    SDL_RenderCopy(renderer, resoudreTexture, NULL, &positionResoudre);
    SDL_RenderCopy(renderer, reinitialiserTexture, NULL, &positionReinitialiser);

    // Mise à jour de l'écran
    SDL_RenderPresent(renderer);



    SDL_FreeSurface(fondSurface);
    SDL_FreeSurface(grilleSurface);


    // Libération de la mémoire
    SDL_DestroyTexture(fondEcran);
    SDL_DestroyTexture(grille);
    SDL_DestroyTexture(retourTexture);
    SDL_DestroyTexture(imprimanteTexture);
    SDL_DestroyTexture(resoudreTexture);
    SDL_DestroyTexture(reinitialiserTexture);
}


/// Proc�dure qui permet d'afficher au centre de l'�cran une grille de sudoku
// vierge sur l'�cran de jeu

void afficherGrilleVierge2(SDL_Renderer *renderer)
{
    // Chargement du fond d'éc                             ran avec transparence
    SDL_Surface *fondEcran = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/fondGrille.bmp");
    if (!fondEcran)
    {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        return;
    }
    SDL_SetColorKey(fondEcran, SDL_TRUE, SDL_MapRGB(fondEcran->format, 255, 255, 255));
    SDL_Texture *fondTexture = SDL_CreateTextureFromSurface(renderer, fondEcran);


    // Chargement de la grille avec transparence
    SDL_Surface *grille = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/grilleVierge.bmp");
    SDL_Texture *grilleTexture = SDL_CreateTextureFromSurface(renderer, grille);
    if (!grille)
    {
        fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
        return;
    }
//    SDL_SetColorKey(grille, SDL_TRUE, SDL_MapRGB(grille->format, 255, 255, 255));
//    SDL_FreeSurface(grille);

    // Chargement des autres images
    SDL_Surface *retour = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/retour.bmp");
    SDL_SetColorKey(retour, SDL_TRUE, SDL_MapRGB(retour->format, 255, 0, 255));
    SDL_Texture *retourTexture = SDL_CreateTextureFromSurface(renderer, retour);

    SDL_Surface *imprimante = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/imprimante.bmp");
    SDL_SetColorKey(imprimante, SDL_TRUE, SDL_MapRGB(retour->format, 255, 0, 255));
    SDL_Texture *imprimanteTexture = SDL_CreateTextureFromSurface(renderer, imprimante);

    SDL_Surface *resoudre = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/valider.bmp");
    SDL_SetColorKey(resoudre, SDL_TRUE, SDL_MapRGB(resoudre->format, 255, 0, 255));
    SDL_Texture *resoudreTexture = SDL_CreateTextureFromSurface(renderer, resoudre);

    SDL_Surface *reinitialiser = chargementBitmap("C:/Users/user/Desktop/libraries/Assets/img/reinitialiser.bmp");
    SDL_SetColorKey(reinitialiser, SDL_TRUE, SDL_MapRGB(reinitialiser->format, 255, 0, 255));
    SDL_Texture *reinitialiserTexture = SDL_CreateTextureFromSurface(renderer, reinitialiser);






    int resoudreTextureWidth, resoudreTextureHeight;
    SDL_QueryTexture(resoudreTexture, NULL, NULL, &resoudreTextureWidth, &resoudreTextureHeight);


// Calcul des positions des images
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    int imprimanteWidth, imprimanteHeight;
    SDL_QueryTexture(imprimanteTexture, NULL, NULL, &imprimanteWidth, &imprimanteHeight);

    SDL_Rect positionRetour = {10, 10, 0, 0};

    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionRetour.w = retour->w;
    positionRetour.h = retour->h;
    // Position du bouton imprimante
    SDL_Rect positionImprimante = {785 - imprimante->w, 12, 0, 0};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionImprimante.w = imprimante->w;
    positionImprimante.h = imprimante->h;
    //grille
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_Rect positionGrille = {(windowWidth - grille->w) / 2, (windowHeight - grille->h) / 2, grille->w, grille->h};
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    positionGrille.w = grille->w;
    positionGrille.h = grille->w;
    //Ressoudre
    SDL_Rect positionResoudre = {
            (windowWidth -170),
            (windowHeight - 40) ,
            resoudreTextureWidth,
            resoudreTextureHeight
    };
    // Position du bouton réinitialiser

    SDL_Rect positionReinitialiser = {
            (windowWidth - 340) ,
            (windowHeight - 40) ,
            resoudreTextureWidth,
            resoudreTextureHeight
    };
    //fond
    SDL_Rect positionFond = {0, 0, 0, 0};
    SDL_QueryTexture(fondTexture, NULL, NULL, &positionFond.w, &positionFond.h);




    // Affichage des images
    SDL_RenderCopy(renderer, fondTexture, NULL, &positionFond);
    SDL_RenderCopy(renderer, grilleTexture, NULL, &positionGrille);
    SDL_RenderCopy(renderer, retourTexture, NULL, &positionRetour);
    SDL_RenderCopy(renderer, resoudreTexture, NULL, &positionResoudre);
    SDL_RenderCopy(renderer, reinitialiserTexture, NULL, &positionReinitialiser);
    SDL_RenderCopy(renderer, imprimanteTexture, NULL, &positionImprimante);

    // Mise à jour de l'écran
    SDL_RenderPresent(renderer);

    // Libération de la mémoire
    SDL_DestroyTexture(fondTexture);
    SDL_DestroyTexture(grilleTexture);
    SDL_DestroyTexture(retourTexture);
    SDL_DestroyTexture(resoudreTexture);
    SDL_DestroyTexture(reinitialiserTexture);
    SDL_DestroyTexture(imprimanteTexture);
}


/// Proc�dure qui affiche l'ensemble des chiffres d'une grille � l'�cran de jeu
int afficherSolution(int grille[9][9][10], SDL_Renderer *renderer)
{
    int ligne = 0, colonne = 0, decalageX = 0, decalageY = 0;
    char nomImage[64];

//
//
//                        for (int i = 0; i < 9; i++) {
//                            for (int j = 0; j < 9; j++) {
//                                printf("%d ", *grille[i][j]);
//                            }
//                            printf("\n");
//                        }

    for (ligne = 0; ligne < 9; ligne++)
    {
        if (ligne >= 6)
        {
            decalageY += 6;
        }
        else if (ligne >= 3)
        {
            decalageY += 3;
        }


        for (colonne = 0; colonne < 9; colonne++)
        {

            if (grille[ligne][colonne][0] != 0)
            {
//                printf("the number is  %d " , grille[ligne][colonne][0]) ;
//                printf("####C:/Users/user/Desktop/libraries/Assets/img/chiffre%d.bmp####", grille[ligne][colonne][0]) ;
                // Construct image filename
                sprintf(nomImage, "C:/Users/user/Desktop/libraries/Assets/img/chiffre%d.bmp", grille[ligne][colonne][0]);

                // Load image surface
                SDL_Surface *chiffreSurface = chargementBitmap(nomImage);
                if (!chiffreSurface)
                {
                    printf("Error loading image: %s\n", nomImage);
                    continue; // Skip rendering if surface loading failed
                }

                // Create texture from surface
                SDL_Texture *chiffreTexture = SDL_CreateTextureFromSurface(renderer, chiffreSurface);
                SDL_FreeSurface(chiffreSurface); // Free surface after creating texture
                if (!chiffreTexture)
                {
                    printf("Error creating texture: %s\n", SDL_GetError());
                    continue; // Skip rendering if texture creation failed
                }

                // Get texture size
                int textureW, textureH;
                SDL_QueryTexture(chiffreTexture, NULL, NULL, &textureW, &textureH);


                if (colonne >= 6)
                {
                    decalageX += 6;
                }
                else if (colonne >= 3)
                {
                    decalageX += 3;
                }

                // Set rendering position with adjustments
                SDL_Rect positionChiffre;
                positionChiffre.x = 217 + colonne * 40 + decalageX;
                positionChiffre.y = 117 + ligne * 40 + decalageY;
                positionChiffre.w = textureW;
                positionChiffre.h = textureH;

                // Render texture
                SDL_RenderCopy(renderer, chiffreTexture, NULL, &positionChiffre);

                // Destroy texture
                SDL_DestroyTexture(chiffreTexture);
                decalageX = 0;
            }
        }
        decalageY = 0;
    }
    SDL_RenderPresent(renderer);
}

