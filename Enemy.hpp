#include"Character.hpp"

class Enemy: public Character
{
  public:
    Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture);

    void moveForward();
    void gotHit() override;

  private:
    int pointsDrop;
};