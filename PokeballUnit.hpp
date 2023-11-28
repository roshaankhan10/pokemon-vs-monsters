#pragma once
#include "Pokeball.hpp"
#include "Unit.hpp"

class PokeballUnit: public Unit
{
public:
  PokeballUnit(SDL_Rect src, SDL_Rect mover, std::string ballName, SDL_Texture* texture);

  void draw(SDL_Renderer* renderer) override;
  Pokeball ball;
  SDL_Texture* texture;
};