#include"Healthbar.hpp"
#include<iostream>

Healthbar::Healthbar(int x, int y, int health)
  : Unit({0,0,0,0}, {x,y,50,5}), maxHealth(health), currHealth(health)
{}

void Healthbar::draw(SDL_Renderer* renderer)
{
  // red color
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &moverRect);
  // green color
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

  // calculate width of green block by considering health left
  float curr = currHealth;
  float maxh = maxHealth;
  float ratio = curr / maxh;
  int width = moverRect.w * ratio;
  SDL_Rect greenBlock = {moverRect.x, moverRect.y, width, moverRect.h};
  SDL_RenderFillRect(renderer, &greenBlock);
}
