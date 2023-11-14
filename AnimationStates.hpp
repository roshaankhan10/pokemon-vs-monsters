#include"Unit.hpp"
#include<vector>

// this class inherits from Unit and stores all possible states of a particular sprite and index of currentFrame
// these can be used for animating it and then drawing on sdl
class AnimationStates: public Unit
{
public:
  AnimationStates(SDL_Rect src, SDL_Rect mover, std::vector<SDL_Rect> states);
  std::vector<SDL_Rect> states;
  int currFrame;
  
  void updateFrame();
};