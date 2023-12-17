#include"Character.hpp"
#include"Projectile.hpp"
#include"Pokeball.hpp"

class Enemy: public Character
{
  public:
    // Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, int speed, std::vector<SDL_Rect> frames, SDL_Texture* Texture, int health, int scoreDrop);
    Enemy(SDL_Rect src, SDL_Rect mover, int power, int range, int speed, std::vector<SDL_Rect> frames, SDL_Texture* Texture, Projectile proj, int health, int scoreDrop, std::string pokeType, int pokeQty);

    void moveForward();
    void gotHit(int damage) override;
    void destroyProjectile() ;
    void throwProjectile() ;

    Projectile projectileE;
    Pokeball pokeDrop;
    bool isThrown = false;
    
  // private:
    int pointsDrop, movingSpeed;
    bool isHit = false;
    SDL_Rect empty = {0,0,0,0};
    uint32_t elapsedTime = SDL_GetTicks();
};