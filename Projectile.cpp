#include"Projectile.hpp"

Projectile::Projectile(SDL_Rect src, SDL_Rect mover, std::vector<SDL_Rect> frames, SDL_Texture* Texture, int projSpeed)
  : AnimationStates(src, mover, frames), texture(Texture), speed(projSpeed)
{}

void Projectile::draw(SDL_Renderer* renderer)
{
  AnimationStates::updateFrame();
  // moves projectile based on speed
  moverRect.x += speed;
  SDL_RenderCopy(renderer, texture, &srcRect, &moverRect);
}

// copy constructor
Projectile::Projectile(const Projectile& other)
  : AnimationStates(other.srcRect, other.moverRect, other.states), texture(other.texture), speed(other.speed) 
{
  // if it doesn't work, we may need deep copy
}