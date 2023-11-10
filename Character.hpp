#include"Unit.hpp"

class Character: public Unit
{
public:
  void gotHit() = 0;
  AnimationStates sprite;

private:
  int atkPower, atkRange;

};