#include"Score.hpp"

Score::Score(SDL_Rect src, SDL_Rect mover)
  : Unit(src, mover), points(0)
{}

void Score::draw(SDL_Renderer* renderer)
{
  // SDL_RenderCopy(renderer, texture, &srcRect, &moverRect);
  // use sdl render text
}