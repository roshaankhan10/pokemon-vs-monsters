#include"Pokemon.hpp"

Pokemon::Pokemon(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture, Projectile* proj, int health)
  :Character(src, mover, power, range, frames, Texture, health), projectile(proj), currProj(nullptr)
{}

void Pokemon::gotHit()
{
  // implementation to be done after projectiles are made
}

// this function will create a new projectile
void Pokemon::throwProjectile()
{
  currProj = new Projectile(*projectile);
}

void Pokemon::destroyProjectile()
{
  delete currProj;
  currProj = nullptr;
}