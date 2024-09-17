#pragma once
#include "Pokeball.hpp"
#include "Unit.hpp"

// used to create a pokeball class that can be drawn such as in menu and stats
class PokeballUnit: public Unit
{
public:
  PokeballUnit(SDL_Rect src, SDL_Rect mover, std::string ballName, SDL_Texture* texture, int qty=0);

  void draw(SDL_Renderer* renderer) override;
  Pokeball ball;
  SDL_Texture* texture;
};