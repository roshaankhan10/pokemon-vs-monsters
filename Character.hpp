// #include"Unit.hpp"
#include"AnimationStates.hpp"

class Character: public Unit
{
public:
  virtual void gotHit() = 0;
  AnimationStates sprite;

private:
  int atkPower, atkRange;

};