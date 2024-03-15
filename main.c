#include "main.h"
#include <SDL_ttf.h>



int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Load the window icon
    SDL_Surface* iconSurface = SDL_LoadBMP("C:/Users/user/Desktop/libraries/Assets/img/icone.bmp");
    if (iconSurface == NULL) {
        // Handle error if icon loading fails
        fprintf(stderr, "Unable to load window icon: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Create the window
    SDL_Window* ecran = SDL_CreateWindow("EPT Sudoku Puzzler", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if (ecran == NULL) {
        // Handle error if window creation fails
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        SDL_FreeSurface(iconSurface);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Set window icon
    SDL_SetWindowIcon(ecran, iconSurface);

    // Free the icon surface after setting it
    SDL_FreeSurface(iconSurface);

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        // Handle error if renderer creation fails
        fprintf(stderr, "Unable to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(ecran);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Boolean to control program termination
    bool finDuProgramme = false;

    // Load the main screen
    ecranPrincipal(renderer, &finDuProgramme);

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Quit SDL
    SDL_DestroyWindow(ecran);
    SDL_Quit();
    return EXIT_SUCCESS;
}





//#include <stdio.h>
//#include <SDL.h>
//#include <SDL_ttf.h>
//
//#define SCREEN_WIDTH 500
//#define SCREEN_HEIGHT 600
//#define GRID_SIZE 9
//#define CELL_SIZE (SCREEN_WIDTH / GRID_SIZE)
//#define FONT_SIZE 40
//
//// Define font globally
//TTF_Font* font = NULL;
//
//int grid[GRID_SIZE][GRID_SIZE] = {
//        {7, 8, 0, 4, 0, 0, 1, 2, 0},
//        {6, 0, 0, 0, 7, 5, 0, 0, 9},
//        {0, 0, 0, 6, 0, 1, 0, 7, 8},
//        {0, 0, 7, 0, 4, 0, 2, 6, 0},
//        {0, 0, 1, 0, 5, 0, 9, 3, 0},
//        {9, 0, 4, 0, 6, 0, 0, 0, 5},
//        {0, 7, 0, 3, 0, 0, 0, 1, 2},
//        {1, 2, 0, 0, 0, 7, 4, 0, 0},
//        {0, 4, 9, 2, 0, 6, 0, 0, 7}
//};
//
//SDL_Window* window = NULL;
//SDL_Renderer* renderer = NULL;
//SDL_Event event;
//
//void draw_grid();
//void draw_numbers();
//void handle_events();
//
//int main(int argc, char* argv[]) {
//    SDL_Init(SDL_INIT_VIDEO);
//    TTF_Init();
//
//    window = SDL_CreateWindow("Sudoku Solver using Backtracking", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    font = TTF_OpenFont("C:/Users/user/Desktop/libraries/Assets/fonts/arial.ttf", FONT_SIZE); // Replace "path_to_font.ttf" with the path to your font file
//
//    int quit = 0;
//    while (!quit) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                quit = 1;
//            }
//        }
//
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//        SDL_RenderClear(renderer);
//
//        draw_grid();
//        draw_numbers();
//        handle_events();
//
//        SDL_RenderPresent(renderer);
//        SDL_Delay(10);
//    }
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    TTF_CloseFont(font);
//    TTF_Quit();
//    SDL_Quit();
//
//    return 0;
//}
//
//void draw_grid() {
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    for (int i = 0; i <= GRID_SIZE; ++i) {
//        int thickness = (i % 3 == 0) ? 3 : 1;
//        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT);
//        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE);
//    }
//}
//
//void draw_numbers() {
//    SDL_Color textColor = {0, 0, 0};
//    SDL_Surface* surface;
//    SDL_Texture* texture;
//    for (int i = 0; i < GRID_SIZE; ++i) {
//        for (int j = 0; j < GRID_SIZE; ++j) {
//            if (grid[i][j] != 0) {
//                char number[2];
//                snprintf(number, 2, "%d", grid[i][j]);
//                surface = TTF_RenderText_Solid(font, number, textColor);
//                texture = SDL_CreateTextureFromSurface(renderer, surface);
//                SDL_Rect destRect = {j * CELL_SIZE + (CELL_SIZE - surface->w) / 2, i * CELL_SIZE + (CELL_SIZE - surface->h) / 2, surface->w, surface->h};
//                SDL_RenderCopy(renderer, texture, NULL, &destRect);
//                SDL_FreeSurface(surface);
//                SDL_DestroyTexture(texture);
//            }
//        }
//    }
//}
//
//void handle_events() {
//    while (SDL_PollEvent(&event)) {
//        if (event.type == SDL_MOUSEBUTTONDOWN) {
//            int x = event.button.x / CELL_SIZE;
//            int y = event.button.y / CELL_SIZE;
//            printf("Clicked cell: (%d, %d)\n", x, y);
//        }
//    }
//}
