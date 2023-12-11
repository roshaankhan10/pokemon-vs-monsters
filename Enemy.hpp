
#include"Character.hpp"
#include"Projectile.hpp"

class Enemy: public Character
{
  public:
    Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, int speed, std::vector<SDL_Rect> frames, SDL_Texture* Texture,Projectile* proj, int health);

    void moveForward();
    void gotHit() override;
    void destroyProjectile() ;
    void throwProjectile() ;

    Projectile* projectileE;
    Projectile* currProjE;

  // private:
    int pointsDrop, movingSpeed;
    bool isHit = false;
    SDL_Rect empty = {0,0,0,0};
    uint32_t elapsedTime = SDL_GetTicks();
};