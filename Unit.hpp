// using pragma once to prevent redeclaration of Unit
#pragma once
#include<SDL.h>

class Unit
{
public:
  Unit(SDL_Rect src, SDL_Rect mover)
    : srcRect(src), moverRect(mover)
  {}

  SDL_Rect srcRect, moverRect;
  virtual void draw(SDL_Renderer* renderer) = 0;
};