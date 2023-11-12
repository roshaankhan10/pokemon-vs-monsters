#include"Unit.hpp"
#include<vector>

class AnimationStates: public Unit
{
public:
  std::vector<SDL_Rect> states;
  int currFrame;
  
  void draw(SDL_Renderer* renderer) override
  {
    currFrame = (currFrame + 1) % states.size();
  }
};