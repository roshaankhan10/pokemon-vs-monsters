#include "PokeballUnit.hpp"

PokeballUnit::PokeballUnit(SDL_Rect src, SDL_Rect mover, std::string ballName, SDL_Texture* texture)
  : Unit(src, mover), ball(ballName, 0), texture(texture)
{}

void PokeballUnit::draw(SDL_Renderer* renderer)
{
  SDL_RenderCopy(renderer, texture, &srcRect, &moverRect);
}