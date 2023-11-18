#include"Enemy.hpp"

Enemy::Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, int speed, std::vector<SDL_Rect> frames, SDL_Texture* Texture, int health)
  : Character(src, mover, power, range, frames, Texture, health), pointsDrop(0), movingSpeed(speed)
{}

// moves enemy forward
void Enemy::moveForward()
{
  moverRect.x = (moverRect.x + movingSpeed);
  // will be destroyed when it crosses certain treshold in grid class
}

void Enemy::gotHit()
{
  // implementation to be done after projectiles are made
}