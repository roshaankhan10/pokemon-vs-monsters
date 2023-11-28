#include"Pokemon.hpp"

Pokemon::Pokemon(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture, Projectile proj, int health)
  :Character(src, mover, power, range, frames, Texture, health), projectile(proj)
{}

void Pokemon::gotHit()
{
  // implementation to be done after projectiles are made
}

// this function will create a new projectile
void Pokemon::throwProjectile()
{
  // find diff bw prev throw and curr time, only create new projectile if difference greater than 1.5s
  if (SDL_GetTicks() - elapsedTime > 1500)
  {
    isThrown = true;
    projectile.moverRect = {moverRect.x-20, moverRect.y, 35, 35};
  }
}

void Pokemon::destroyProjectile()
{
  isThrown = false;
  projectile.moverRect = {0,0,0,0};
  // update elapsedTime as it'll be used for next projectile throw
  elapsedTime = SDL_GetTicks();
}