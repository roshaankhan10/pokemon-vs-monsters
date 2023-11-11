#include<SDL.h>

class Unit
{
public:
  SDL_Rect srcRect, moverRect;
  virtual void draw() = 0;
};