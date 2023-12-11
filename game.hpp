// #pragma once
#include"Menu.hpp"
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>
// #include <SDL2/SDL_mixer.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include"Grid.hpp"

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //adding background music 
    Mix_Music* bgMusic = NULL;
    //global reference to png image sheets
    SDL_Texture* pokemons = NULL;
    SDL_Texture* monsters = NULL;
    SDL_Texture* pokeballs = NULL;
    SDL_Texture* projectiles = NULL;
    SDL_Texture* projectilesE = NULL;

public:

    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
    // method to determine if mouse is over a draggable object to start dragging it by changing selectedObject
    bool IsMouseOverDraggableObject(int x, int y, std::vector<DraggableObject*> objects, DraggableObject*& selectedObject);
};

