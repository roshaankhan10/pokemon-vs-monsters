#include"Pokemon.hpp"

Pokemon::Pokemon(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture)
  :Character(src, mover, power, range, frames, Texture)
{}

void Pokemon::gotHit()
{
  // implementation to be done after projectiles are made
}