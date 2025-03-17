#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Globale Variablen das in allen Dateien gleiche größe ist
extern SDL_Window *window;
extern SDL_Surface *surface;

int text_sdl(void) {
    int rect_size = 90;

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
		.x = (9 * rect_size),		//it should be located at the upper right corner of the window, next to the board
		.y = rect_size * 0, 
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


	SDL_FreeSurface(text); 
	SDL_FreeSurface(text_konvertiert); 

    // Letters A-H unter dem Schachbrett
    const char *letters = "ABCDEFGH";
    for(int i = 0; i < 8; i++) {
        char letter[2] = {letters[i], '\0'}; 
        SDL_Surface *text = TTF_RenderText_Solid(font, letter, white_color);
        if (text == NULL) {
            SDL_Log("Text rendering failed: %s\n", TTF_GetError());
            return -1;
        }
        
        // Konvertiere die Text-Surface
        SDL_Surface *text_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
	    if (text_konvertiert == NULL) {
		    SDL_Log("Text konnte nicht konvertiert werden! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            TTF_CloseFont(font);
            return -1;
    	}
        
        // Positioning from letters
        SDL_Rect letter_rect = {
            .x = i * rect_size + (rect_size/2), // Zentriert unter jedem Feld
            .y = 8 * rect_size, // Unter dem Brett
            .w = text_konvertiert->w,
            .h = text_konvertiert->h
        };
    
        // Drawing of the letters
        if (SDL_BlitSurface(text_konvertiert, NULL, surface, &letter_rect)) {
            SDL_Log("Text konnte nicht kopiert werden! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            SDL_FreeSurface(text_konvertiert);
            TTF_CloseFont(font);
            return -1;
        }
        
        // Gib die Surfaces frei
        SDL_FreeSurface(text);
        SDL_FreeSurface(text_konvertiert);
    }

    // Zahlen 1-8 links vom Schachbrett
    for (int i=1; i<9; i++) {
        char number[2] = {i + '0', '\0'};
        SDL_Surface *text = TTF_RenderText_Solid(font, number, white_color);
        if (text == NULL) {
            SDL_Log("Text rendering failed: %s\n", TTF_GetError());
            return -1;
        }
        
        // Konvertiere die Text-Surface
        SDL_Surface *number_konvertiert = SDL_ConvertSurfaceFormat(text, surface->format->format, 0);
        if (number_konvertiert == NULL) {
            SDL_Log("Zahl konnte nicht konvertiert werden! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            TTF_CloseFont(font);
            return -1;
    	}
        
        // Positioning from numbers
        SDL_Rect number_rect = {
            .x = 8 * rect_size + 5, // Rechts vom Brett
            .y = (8-i) * rect_size + (rect_size - 60) , // Zentriert neben jedem Feld
            .w = number_konvertiert->w,
            .h = number_konvertiert->h
        };
    
        // Drawing of the numbers
        if (SDL_BlitSurface(number_konvertiert, NULL, surface, &number_rect)) {
            SDL_Log("Text konnte nicht kopiert werden! SDL_Error Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text);
            SDL_FreeSurface(number_konvertiert);
            TTF_CloseFont(font);
            return -1;
        }
        
        // Gib die Surfaces frei
        SDL_FreeSurface(number_konvertiert);
        SDL_FreeSurface(text);
    }
    TTF_CloseFont(font);
    return 0;
}