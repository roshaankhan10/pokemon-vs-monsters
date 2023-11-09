#include<iostream>
#include "draw.hpp"
#include <vector>
using namespace std;

// First rectangle is srcRect, second is moverRect

// used vectors to create SDL_Rect array for all animation states
vector<SDL_Rect> ballStates = {{32,43,120,108}, {225,33,120,120}, {433,48,100,96}, {615,47,124,112}, {805,37,124,124}, } ;


// function to update srcRect of a particular vector that takes the sprite, it's count and it's states
void animateSprite(int count, Unit& sprite, vector<SDL_Rect> states)
{
    sprite.srcRect = states[count % states.size()];
}

// function to move a sprite in x direction and loop back to start when goes out of screen
void moveSprite(Unit& sprite)
{
    sprite.moverRect.x -= 7 ;
}

// int array to store counts for each sprite type
vector<int> b_counts ;
vector<Unit> balls;

// Menu Icons:
SDL_Rect braviary = {11, 7, 88, 82};
SDL_Rect charizard = {597, 8, 74, 81};
SDL_Rect metagross = {949, 6, 77, 52};
SDL_Rect pikachu = {1365, 0, 39, 46};
SDL_Rect azumarill = {1621, 2, 58, 59};

SDL_Rect braviaryM = {250, 40, 50, 50};
SDL_Rect charizardM = {310, 30, 60, 60};
SDL_Rect metagrossM = {380, 50, 60, 40};
SDL_Rect pikachuM = {450, 50, 35, 35};
SDL_Rect azumarillM = {490, 40, 50, 50};


void drawMenu(SDL_Renderer* gRnderer, SDL_Texture* assets){
     SDL_RenderCopy(gRnderer, assets, &braviary, &braviaryM) ;
     SDL_RenderCopy(gRnderer, assets, &charizard, &charizardM) ;
     SDL_RenderCopy(gRnderer, assets, &metagross, &metagrossM) ;
     SDL_RenderCopy(gRnderer, assets, &azumarill, &azumarillM) ;
     SDL_RenderCopy(gRnderer, assets, &pikachu, &pikachuM) ;
}

    // it draws, moves and animates each ball sprite
void drawObjects(SDL_Renderer* gRenderer, SDL_Texture* assets){
    for (int i = 0; i < balls.size(); i++)
    {
        SDL_RenderCopy(gRenderer, assets, &balls[i].srcRect, &balls[i].moverRect) ;
        b_counts[i]++ ;
        animateSprite(b_counts[i], balls[i], ballStates) ;
        moveSprite(balls[i]);
    }    
}



void createObject(int x, int y){
    // for each sprite, create a new Unit and initialize it with first animation state, 
    Unit new_ball = {ballStates[0], {x, y, 30, 30}} ;
    
    // push it in the respective vector Unit array,
    balls.push_back(new_ball) ;
    
    // and initialize it's count to 0 by pushing it in respective vector count array 
    b_counts.push_back(0) ;
}