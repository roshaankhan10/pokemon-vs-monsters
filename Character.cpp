#include"Character.hpp"

Character::Character(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture)
  : atkPower(power), atkRange(range), AnimationStates(src, mover, frames), texture(Texture)
{}

// first updates frame then draws the new frame
void Character::draw(SDL_Renderer* renderer)
{
  AnimationStates::updateFrame();
  SDL_RenderCopy(renderer, texture, &srcRect, &moverRect);
}