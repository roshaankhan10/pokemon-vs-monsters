// not an actual class but has functions we need to display text
#pragma once;
#include<SDL.h>
#include <SDL_ttf.h>
#include<iostream>

class TextDisplay
{
public:
    void displayText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y)
    {
    SDL_Color textColor = {0, 0, 0}; // White color

    // creates a surface which will be used for creating texture
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (surface == nullptr) {
        std::cerr << "Text rendering failed: " << TTF_GetError() << std::endl;
    }

    // texture created, now just need to display it at certain position
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // free up memory

    // Destination rectangle where text is to be drawn
    SDL_Rect destRect = {x, y, 0, 0}; 
    
    // Render the text texture
    SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    TTF_CloseFont(font);
    }

    TTF_Font* loadFont(const std::string& fontPath, int fontSize) 
    {
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (font == nullptr) {
            std::cerr << "Font loading failed: " << TTF_GetError() << std::endl;
        }
        return font;
    }
};