
cmake_minimum_required(VERSION 3.27)
project(projects C)

set(CMAKE_C_STANDARD 17)





set(SDL2_INCLUDE_DIR "C:/Users/user/Desktop/libraries/SDL2-2.30.1/x86_64-w64-mingw32/include/SDL2")
set(SDL2_LIB_DIR "C:/Users/user/Desktop/libraries/SDL2-2.30.1/x86_64-w64-mingw32/lib")
#Set paths to SDL2_ttf library
set(SDL2_IMAGE_INCLUDE_DIR "C:/Users/user/Desktop/libraries/SDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2")
set(SDL2_IMAGE_LIB_DIR "C:/Users/user/Desktop/libraries/SDL2_image-2.8.2/x86_64-w64-mingw32/lib")
#Set paths to SDL2_image library
set(SDL2_TTF_INCLUDE_DIR "C:/Users/user/Desktop/libraries/SDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2")
set(SDL2_TTF_LIB_DIR "C:/Users/user/Desktop/libraries/SDL2_ttf-2.22.0/x86_64-w64-mingw32/lib")

# Include directories for SDL2, SDL2_image, and SDL2_ttf
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

# Link directories for SDL2, SDL2_image, and SDL2_ttf
link_directories(${SDL2_LIB_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})
link_directories(${SDL2_TTF_LIB_DIR})

# Add the executable
add_executable(projects main.c
        main.h
        gestionEvenements.c
        gestionEvenements.h
        fonctionsSDL.c
        fonctionsSDL.h
        ecrans.c
        ecrans.h
        Sudoku_Console/fonctionsDeBase.c
        Sudoku_Console/fonctionsDeBase.h
        Sudoku_Console/resolveur.c
        Sudoku_Console/resolveur.h
        Sudoku_Console/recherches.c
        Sudoku_Console/recherches.h
        Sudoku_Console/suppression.c
        Sudoku_Console/suppression.h
        Sudoku_Console/resolution.c
        Sudoku_Console/resolution.h
        Sudoku_Console/tests.c
        Sudoku_Console/tests.h
        Sudoku_Console/backtracking.c
        Sudoku_Console/backtracking.h
        Sudoku_Console/generateur.c
        Sudoku_Console/generateur.h)


# Link SDL2, SDL2_image, and SDL2_ttf libraries
target_link_libraries(projects ${SDL2_LIB_DIR}  -lmingw32 -lSDL2main -lSDL2 -mwindows)
target_link_libraries(projects SDL2 SDL2_image SDL2_ttf)

