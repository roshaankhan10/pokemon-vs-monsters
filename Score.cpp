#include"Score.hpp"

Score::Score(SDL_Rect src, SDL_Rect mover)
  : Unit(src, mover), points(0)
{}

void Score::draw(SDL_Renderer* renderer)
{
  TTF_Font* font = displayer.loadFont("assets/16020_FUTURAM.ttf", 24);
  std::string scoreText = "Score: " + std::to_string(points);
  displayer.displayText(renderer, font, scoreText, 800, 110);
}