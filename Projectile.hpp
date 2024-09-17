#pragma once
#include"AnimationStates.hpp"

class Projectile: public AnimationStates
{
public:
  Projectile(SDL_Rect src, SDL_Rect mover, std::vector<SDL_Rect> frames, SDL_Texture* Texture, int projSpeed);
  Projectile(const Projectile& other);
  void draw(SDL_Renderer* renderer) override;

private:
  SDL_Texture* texture;
  int speed;
};