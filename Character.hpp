#pragma once
#include"AnimationStates.hpp"
#include"Healthbar.hpp"

class Character: public AnimationStates
{
public:
  Character(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture, int health);
  
  virtual void gotHit() = 0;
  void draw(SDL_Renderer* renderer) override;
  bool isDead();

// private:
  int atkPower, atkRange;
  Healthbar health;
  SDL_Texture* texture;
};