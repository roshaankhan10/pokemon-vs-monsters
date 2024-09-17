#include"Unit.hpp"

class Healthbar: public Unit
{
public:
  Healthbar(int x, int y, int health);
  void draw(SDL_Renderer* renderer) override;

  int maxHealth, currHealth;
};