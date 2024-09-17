#include "PokeballUnit.hpp"

PokeballUnit::PokeballUnit(SDL_Rect src, SDL_Rect mover, std::string ballName, SDL_Texture* texture, int qty)
  : Unit(src, mover), ball(ballName, qty), texture(texture)
{}

void PokeballUnit::draw(SDL_Renderer* renderer)
{
  SDL_RenderCopy(renderer, texture, &srcRect, &moverRect);
}