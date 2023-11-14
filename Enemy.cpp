#include"Enemy.hpp"

Enemy::Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture)
  : Character(src, mover, power, range, frames, Texture), pointsDrop(0)
{}

// moves enemy forward
void Enemy::moveForward()
{
  moverRect.x = (moverRect.x + 5) % 1000;
}

void Enemy::gotHit()
{
  // implementation to be done after projectiles are made
}