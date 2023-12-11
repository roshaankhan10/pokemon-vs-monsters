#include"Enemy.hpp"
#include<iostream>


Enemy::Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, int speed, std::vector<SDL_Rect> frames, SDL_Texture* Texture,Projectile* proj, int health)
  : Character(src, mover, power, range, frames, Texture, health), pointsDrop(0), movingSpeed(speed) ,projectileE(proj),currProjE(nullptr)
{}

// moves enemy forward
void Enemy::moveForward()
{
  moverRect.x = (moverRect.x + movingSpeed);
  // std::cout<<moverRect.x;
  // will be destroyed when it crosses certain treshold in grid class
}

void Enemy::gotHit()
{
  // implementation to be done after projectiles are made
  health.currHealth -= 5;
  isHit = true;
}

// this function will create a new projectile
void Enemy::throwProjectile()
{
  // find diff bw prev throw and curr time, only create new projectile if difference greater than 1.5s
  // if (SDL_GetTicks() - elapsedTime > 1000)
    currProjE = new Projectile(*projectileE);
  std::cout<<"currProj"<<std::endl;
}

void Enemy::destroyProjectile()
{
  delete currProjE;
  currProjE= nullptr;
  // update elapsedTime as it'll be used for next projectile throw
  elapsedTime = SDL_GetTicks();
  // std::cout<<"here" <<elapsedTime<<std::endl;
  
}