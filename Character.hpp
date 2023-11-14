#pragma once
#include"AnimationStates.hpp"

class Character: public AnimationStates
{
public:
  Character(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture);
  // AnimationStates sprite;
  
  virtual void gotHit() = 0;
  void draw(SDL_Renderer* renderer) override;

// private:
  int atkPower, atkRange;
  SDL_Texture* texture;
};