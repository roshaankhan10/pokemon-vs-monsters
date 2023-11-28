#pragma once
#include"Score.hpp"
#include"PokeballUnit.hpp"
#include<vector>
#include<SDL_ttf.h>
#include<iostream>
#include<string>

class Statistics
{
public:
  Statistics(SDL_Rect scoreSrc, SDL_Rect scoreMover, SDL_Texture* texture);
  void displayText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);
  void displayStats(SDL_Renderer* renderer, TTF_Font* font);

  Score scores;
  std::vector<PokeballUnit*> pokeballs;
};