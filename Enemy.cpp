#include<iostream>
#include"Enemy.hpp"

// Enemy::Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, int speed, std::vector<SDL_Rect> frames, SDL_Texture* Texture, int health, int scoreDrop)
//   : Character(src, mover, power, range, frames, Texture, health), pointsDrop(scoreDrop), movingSpeed(speed)
// {}
Enemy::Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, int speed, std::vector<SDL_Rect> frames, SDL_Texture* Texture, Projectile proj, int health, int scoreDrop, std::string pokeType, int pokeQty)
  : Character(src, mover, power, range, frames, Texture, health), pointsDrop(scoreDrop), movingSpeed(speed), projectileE(proj), pokeDrop(pokeType, pokeQty)
{}

// moves enemy forward
void Enemy::moveForward()
{
  moverRect.x += movingSpeed;
}

void Enemy::gotHit(int damage)
{
  health.currHealth -= damage;
  isHit = true;
}

// this function will create a new projectile
void Enemy::throwProjectile()
{
  // find diff bw prev throw and curr time, only create new projectile if difference greater than 1s
  if (SDL_GetTicks() - elapsedTime > 1000)
  {
    isThrown = true;
    projectileE.moverRect = {moverRect.x + moverRect.w, moverRect.y, 35, 35};
  }
}

void Enemy::destroyProjectile()
{
  isThrown = false;
  projectileE.moverRect = {0,0,0,0};
  
  // update elapsedTime as it'll be used for next projectile throw
  elapsedTime = SDL_GetTicks();
}