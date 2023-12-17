#include"Character.hpp"
#include"Projectile.hpp"

class Pokemon: public Character
{
public: 
  Pokemon(SDL_Rect src, SDL_Rect mover, int power, int range, std::vector<SDL_Rect> frames, SDL_Texture* Texture, Projectile proj, int health);
  void gotHit(int damage) override;
  void throwProjectile();
  void destroyProjectile();

  Projectile projectile;
  
  // flag to check if pokemon's projectile is being thrown or not
  bool isThrown = false; 
  
  // stores timestamp at which last projectile died
  uint32_t elapsedTime = SDL_GetTicks();
};