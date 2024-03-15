#include "resolveur.h"

/// Proc�dure de r�solution d'une grille de Sudoku
void resolveur(int grille[9][9][10], int *niveau)
{
    // Count the number of cells to solve
    int  compteurDeCases = nombreCasesRestantes(grille);
    bool stop            = false;

    // Search for possibilities for the cells to solve in the grid
    recherchePossibilitesGrille(&compteurDeCases, grille, niveau);

    /* Once a complete first pass of the grid has been made, all
       possibilities for each cell have been determined.
       We then proceed to solve the grid until the counter of
          remaining cells is zero.
       If we notice that the boolean variable 'stop' does not change anymore,
          it means that the treatments related to the current level are not sufficient,
          so we have to move to the next level. */
    while ((compteurDeCases > 0) && (*niveau != 6))
    {
        // Initialize the 'stop' variable as "false"
        stop = false;

        // We launch the grid resolution
        resolutionGrille(&compteurDeCases, grille, niveau, &stop);
//        printf("Seeing if grille have a solution....\n ");
        // If the 'stop' variable is still false after leaving the resolution algorithm,
        // it means that none of the treatments applied have modified the grid,
        // so we move to the next level
        if (stop == false)
        {
            (*niveau)++;
        }
    }

    if (compteurDeCases > 0)
    {
        // If the cell counter is not zero, then the grid is not
        // solvable with the employed algorithm
        printf("\nGrid not solvable!\n");
        affichageGrille(grille); // temporary
        exit(EXIT_FAILURE);
    }

}


/// Proc�dure d'importation de la grille par lecture du fichier
void importationGrille(FILE *fichier, int grille[9][9][10])
{
    int ligne = 0, colonne = 0;

    for (ligne = 0; ligne < 9; ligne++)
    {
        for (colonne = 0; colonne < 9; colonne++)
        {
            fscanf(fichier, "%d,", &grille[ligne][colonne][0]);
        }
    }
}

/// Proc�dure d'affichage de la grille de Sudoku
void affichageGrille(int grille[9][9][10])
{
    int ligne = 0, colonne = 0;

    printf("-------------------\n");

    printf("solution is here");

    for (ligne = 0; ligne < 9; ligne++)
    {
        for (colonne = 0; colonne < 9; colonne++)
        {
            if (colonne == 0)
            {
                printf("|%d ", grille[ligne][colonne][0]);
            }
            else if (((colonne + 1) % 3))
            {
                printf("%d ", grille[ligne][colonne][0]);
            }
            else
            {
                printf("%d|", grille[ligne][colonne][0]);
            }
        }
        putchar('\n');

        if (!((ligne + 1) % 3))
        {
            printf("-------------------\n");
        }
    }
}
