#include"Projectile.hpp"

Projectile::Projectile(SDL_Rect src, SDL_Rect mover, std::vector<SDL_Rect> frames, SDL_Texture* Texture)
  : AnimationStates(src, mover, frames), texture(Texture)
{}

void Projectile::draw(SDL_Renderer* renderer)
{
  AnimationStates::updateFrame();
  // moves projectile to left, will change later using some variable
  moverRect.x -= 5;
  SDL_RenderCopy(renderer, texture, &srcRect, &moverRect);
}

// copy constructor
Projectile::Projectile(const Projectile& other)
  : AnimationStates(other.srcRect, other.moverRect, other.states), texture(other.texture) 
{
  // if it doesn't work, we may need deep copy
}