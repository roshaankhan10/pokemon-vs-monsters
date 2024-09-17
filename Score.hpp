#pragma once
#include "Unit.hpp"
#include"TextDisplay.hpp"
#include<cstring>

class Score: public Unit
{
public:
  Score(SDL_Rect src, SDL_Rect mover);
  int points;
  void draw(SDL_Renderer* renderer) override;
private:
  TextDisplay displayer;
};