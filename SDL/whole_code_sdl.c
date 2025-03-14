#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//gcc whole_code_sdl.c -o chess $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf

enum screen_size {
    SCREEN_WIDTH = 1000,
    SCREEN_HEIGHT = 720,
};

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    // Initialisierung von SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Initialisierung fehlgeschlagen! SDL_Error: %s\n", SDL_GetError());
        goto end_of_file;
    }

    // Erstellt ein Fenster
    SDL_Window *window = SDL_CreateWindow("Schach", SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Fenster nicht erstellt! SDL_Error: %s\n", SDL_GetError());
        goto end_of_file;
    }

    //Struktur um in SDL Pixelmanipulationen durchzuführen
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        SDL_Log("Oberfläche nicht erhalten! SDL_Error: %s\n", SDL_GetError());
        goto end_of_file;
    }

    // Farben erstellen (int)
    Sint32 white = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
    Sint32 grey = SDL_MapRGBA(surface->format, 128, 128, 128, 255);

    //Größe der Rechtecke (single square)
    int rect_size = 90;

    //Schachbrett erstellen
    for(int row = 0; row <8; row++) {
        for(int column = 0; column < 8; column++) {
            SDL_Rect rect = {
                .x = column * rect_size, // x stellt die horizontale Position dar
                .y = row * rect_size, // y stellt die vertikale Position dar
                .w = rect_size, // w stellt die Breite des Rechtecks dar
                .h = rect_size, // h stellt die Höhe des Rechtecks dar
            };

            //Farbe des Rechtecks
            if ((row + column) % 2 == 0) {
                SDL_FillRect(surface, &rect, white);
            } else {
                SDL_FillRect(surface, &rect, grey);
            }
        }
    }

    //make the changes visible on the user's screen
    SDL_UpdateWindowSurface(window); 

    // Flags für die Initialisierung von SDL_Image (pieces)
    int flags = IMG_INIT_PNG | IMG_INIT_JPG; 

    if(IMG_Init(flags) != flags) {
		SDL_Log(
			"SDL_Image couldn't be initialized! SDL_image Error: %s\n", 
			IMG_GetError());
		return -1;
	}

    //image_black_pawn is a pointer to an SDL_Surface object that contains the picture of a black pawn
    SDL_Surface *image_black_pawn = IMG_Load("chess_figures/black_pawn.png");
    if (image_black_pawn == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    //in the following SDL_Surface objects are created for all the chess figures
    SDL_Surface *image_white_pawn = IMG_Load("chess_figures/white_pawn.png");
    if (image_white_pawn == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_black_rook = IMG_Load("chess_figures/black_rook.png");
    if (image_black_rook == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_white_rook = IMG_Load("chess_figures/white_rook.png");
    if (image_white_rook == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_black_horse = IMG_Load("chess_figures/black_horse.png");
    if (image_black_horse == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_white_horse = IMG_Load("chess_figures/white_horse.png");
    if (image_white_horse == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_black_bishop = IMG_Load("chess_figures/black_bishop.png");
    if (image_black_bishop == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_white_bishop = IMG_Load("chess_figures/white_bishop.png");
    if (image_white_bishop == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_black_queen = IMG_Load("chess_figures/black_queen.png");
    if (image_black_queen == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_white_queen = IMG_Load("chess_figures/white_queen.png");
    if (image_white_queen == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_black_king = IMG_Load("chess_figures/black_king.png");
    if (image_black_king == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Surface *image_white_king = IMG_Load("chess_figures/white_king.png");
    if (image_white_king == NULL) {
        SDL_Log("Bild nicht geladen%s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

//in the following for loops are created that create SDL_Rect objects for the pawns 
//with the correct coordinates and sizes for the images and then print them on the surface

    //for loop that creates 8 SDL_Rect objects for the black pawns in the 7th row
    for(int i=0; i<8; i++){
        SDL_Rect image_rect_black_pawn = {
            .x = i * rect_size + 15, // Beispiel: Bild in der x Spalte
            .y = rect_size, // Bild in der 2. Reihe
            .w = image_black_pawn->w, // Breite des Bildes
            .h = image_black_pawn->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_black_pawn, NULL, surface, &image_rect_black_pawn); 
    }

    //for loop that creates 8 SDL_Rect objects for the white pawns in the 2nd row
    for(int i=0; i<8; i++){
        SDL_Rect image_rect_white_pawn = {
            .x = i * rect_size + 15, // Beispiel: Bild in der x Spalte
            .y = rect_size * 6, // Bild in der 2. Reihe
            .w = image_white_pawn->w, // Breite des Bildes
            .h = image_white_pawn->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_white_pawn, NULL, surface, &image_rect_white_pawn); 
    }

    //for loop that creates 2 SDL_Rect objects for the black rooks in the 8th row
    for(int i=0; i<2; i++) {
        SDL_Rect image_rect_black_rooks = {
            .x = i * 7 * rect_size + 10, // Beispiel: Bild in der x Spalte
            .y = rect_size * 0, // Bild in der 8. Reihe
            .w = image_black_rook->w, // Breite des Bildes
            .h = image_black_rook->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_black_rook, NULL, surface, &image_rect_black_rooks); 
    }

    //for loop that creates 2 SDL_Rect objects for the black rooks in the 8th row
    for(int i=0; i<2; i++) {
        SDL_Rect image_rect_white_rooks = {
            .x = i * 7 * rect_size + 10, // Beispiel: Bild in der x Spalte
            .y = rect_size * 7, // Bild in der 8. Reihe
            .w = image_white_rook->w, // Breite des Bildes
            .h = image_white_rook->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_white_rook, NULL, surface, &image_rect_white_rooks); 
    }

        SDL_Rect image_rect_black_horse1 = {
            .x = 1 * rect_size -2, // Beispiel: Bild in der x Spalte
            .y = rect_size * 0, // Bild in der 8. Reihe
            .w = image_black_horse->w, // Breite des Bildes
            .h = image_black_horse->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_black_horse, NULL, surface, &image_rect_black_horse1);

        SDL_Rect image_rect_black_horse2 = {
            .x = 6 * rect_size -2, // Beispiel: Bild in der x Spalte
            .y = rect_size * 0, // Bild in der 8. Reihe
            .w = image_black_horse->w, // Breite des Bildes
            .h = image_black_horse->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_black_horse, NULL, surface, &image_rect_black_horse2);

        SDL_Rect image_rect_white_horse1 = {
            .x = 1 * rect_size -2, // Beispiel: Bild in der x Spalte
            .y = rect_size * 7, // Bild in der 8. Reihe
            .w = image_white_horse->w, // Breite des Bildes
            .h = image_white_horse->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_white_horse, NULL, surface, &image_rect_white_horse1);

        SDL_Rect image_rect_white_horse2 = {
            .x = 6 * rect_size -2, // Beispiel: Bild in der x Spalte
            .y = rect_size * 7, // Bild in der 8. Reihe
            .w = image_white_horse->w, // Breite des Bildes
            .h = image_white_horse->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_white_horse, NULL, surface, &image_rect_white_horse2);

        SDL_Rect image_rect_black_bishop1 = {
            .x = 2 * rect_size + 0, // Beispiel: Bild in der x Spalte
            .y = rect_size * 0, // Bild in der 8. Reihe
            .w = image_black_bishop->w, // Breite des Bildes
            .h = image_black_bishop->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_black_bishop, NULL, surface, &image_rect_black_bishop1);

        SDL_Rect image_rect_black_bishop2 = {
            .x = 5 * rect_size + 0, // Beispiel: Bild in der x Spalte
            .y = rect_size * 0, // Bild in der 8. Reihe
            .w = image_black_bishop->w, // Breite des Bildes
            .h = image_black_bishop->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_black_bishop, NULL, surface, &image_rect_black_bishop2); 

        SDL_Rect image_rect_white_bishop1 = {
            .x = 2 * rect_size + 0, // Beispiel: Bild in der x Spalte
            .y = rect_size * 7, // Bild in der 8. Reihe
            .w = image_white_bishop->w, // Breite des Bildes
            .h = image_white_bishop->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_white_bishop, NULL, surface, &image_rect_white_bishop1);

        SDL_Rect image_rect_white_bishop2 = {
            .x = 5 * rect_size + 0, // Beispiel: Bild in der x Spalte
            .y = rect_size * 7, // Bild in der 8. Reihe
            .w = image_white_bishop->w, // Breite des Bildes
            .h = image_white_bishop->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_white_bishop, NULL, surface, &image_rect_white_bishop2);

        SDL_Rect image_rect_black_queen = {
            .x = 3 * rect_size -2, // Beispiel: Bild in der x Spalte
            .y = (rect_size * 0)-2, // Bild in der 8. Reihe
            .w = image_black_queen->w, // Breite des Bildes
            .h = image_black_queen->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_black_queen, NULL, surface, &image_rect_black_queen);

        SDL_Rect image_rect_white_queen = {
            .x = 3 * rect_size -4, // Beispiel: Bild in der x Spalte
            .y = (rect_size * 7)-2, // Bild in der 8. Reihe
            .w = image_white_queen->w, // Breite des Bildes
            .h = image_white_queen->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_white_queen, NULL, surface, &image_rect_white_queen);

        SDL_Rect image_rect_black_king = {
            .x = 4 * rect_size + 0, // Beispiel: Bild in der x Spalte
            .y = rect_size * 0, // Bild in der 8. Reihe
            .w = image_black_king->w, // Breite des Bildes
            .h = image_black_king->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_black_king, NULL, surface, &image_rect_black_king);

        SDL_Rect image_rect_white_king = {
            .x = 4 * rect_size + 0, // Beispiel: Bild in der x Spalte
            .y = rect_size * 7, // Bild in der 8. Reihe
            .w = image_white_king->w, // Breite des Bildes
            .h = image_white_king->h // Höhe des Bildes
        };
        //The SDL_BlitSurface function copies the image to the surface
        SDL_BlitSurface(image_white_king, NULL, surface, &image_rect_white_king);

    //get all the images of pieces on the user's window
    SDL_UpdateWindowSurface(window);

    SDL_FreeSurface(image_black_pawn); // Freigabe des Bildes
    SDL_FreeSurface(image_white_pawn); // Freigabe des Bildes
    SDL_FreeSurface(image_black_rook); // Freigabe des Bildes
    SDL_FreeSurface(image_white_rook); // Freigabe des Bildes
    SDL_FreeSurface(image_black_horse); // Freigabe des Bildes
    SDL_FreeSurface(image_white_horse); // Freigabe des Bildes
    SDL_FreeSurface(image_black_bishop); // Freigabe des Bildes
    SDL_FreeSurface(image_white_bishop); // Freigabe des Bildes
    SDL_FreeSurface(image_black_queen); // Freigabe des Bildes
    SDL_FreeSurface(image_white_queen); // Freigabe des Bildes
    SDL_FreeSurface(image_black_king); // Freigabe des Bildes
    SDL_FreeSurface(image_white_king); // Freigabe des Bildes

    //Insertion of text on right part of window via sdl_ttf
    //initializing sdl_ttf
    if (TTF_Init() == -1) {
		SDL_Log("SDL_ttf konnte nicht initialisiert werden! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    TTF_Font *font = TTF_OpenFont("Go_Mono.ttf", 28);
    if (font == NULL){
		SDL_Log("Font could not be loaded. SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}
	
    // white color (SDL_Color)
	SDL_Color white_color = {.r = 255, .g = 255, .b = 255, .a = 255};

    // from text to pixels
    SDL_Surface *text = TTF_RenderText_Solid(font, "HP: ", white_color);
    if (text == NULL) {
        SDL_Log("Text rendering failed: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Surface *text_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
	if (text_konvertiert == NULL) {
		SDL_Log("Text konnte nicht konvertiert werden! SDL_Error Error: %s\n", SDL_GetError());
        SDL_FreeSurface(text);
        TTF_CloseFont(font);
        return -1;
	}
	
	//hier irgendwie kompilierfehler 
    //CHANGE: from *textRect to textRect
    //it's already a "box" with smth inside, *box just gives an address of the box 
	SDL_Rect textRect = {	//creating a rect object for the text to go into
		.x = (8 * rect_size) + 10,		//it should be located at the upper right corner of the window, next to the board
		.y = rect_size, 
		.w = text_konvertiert->w, 
		.h = text_konvertiert->h
	};
	//CHANGE: textRect --> &textRect
	if (SDL_BlitSurface(text_konvertiert, NULL, surface, &textRect) != 0) {
		SDL_Log("Text konnte nicht kopiert werden! SDL_Error Error: %s\n", SDL_GetError());
        SDL_FreeSurface(text);
        SDL_FreeSurface(text_konvertiert);
        TTF_CloseFont(font);
        return -1;
	}

    SDL_Log("Text position: (%d, %d), size: (%d, %d)", textRect.x, textRect.y, textRect.w, textRect.h);

	SDL_UpdateWindowSurface(window);

	SDL_FreeSurface(text);
	SDL_FreeSurface(text_konvertiert);

    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
    

end_of_file:	//ttf_quit() needed?
	IMG_Quit();
	TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

