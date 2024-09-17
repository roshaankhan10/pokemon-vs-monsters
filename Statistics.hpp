#pragma once
#include"Score.hpp"
#include"PokeballUnit.hpp"
#include"TextDisplay.hpp"
#include<vector>
#include<SDL_ttf.h>
#include<iostream>
#include<string>

class Statistics
{
public:
  Statistics(SDL_Rect scoreSrc, SDL_Rect scoreMover, SDL_Texture* texture);
  void displayStats(SDL_Renderer* renderer);
  void updateBalls(std::string ballType, int qty);
  bool haveBalls(Pokeball ball);

  Score scores;
  std::vector<PokeballUnit*> pokeballs;
private:
  TextDisplay displayer;
};