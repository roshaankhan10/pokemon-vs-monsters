#include"AnimationStates.hpp"

AnimationStates::AnimationStates(SDL_Rect src, SDL_Rect mover, std::vector<SDL_Rect> frames)
  : Unit(src, mover), states(frames), currFrame(0)
{}

// updates frame by going to next srcRect in states
void AnimationStates::updateFrame()
{
  currFrame = (currFrame + 1) % states.size();
  srcRect = states[currFrame];
}