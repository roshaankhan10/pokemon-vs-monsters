#include"DraggableObject.hpp"
#include"PokeballUnit.hpp"
#include<vector>
#include<SDL_ttf.h>

// it contains DraggableObjects and pokeballs(sprites and costs)
class Menu
{
  public:
    std::vector<DraggableObject*> pokemonIcons;
    std::vector<PokeballUnit*> pokemonCosts;

    void drawMenu(SDL_Renderer* gRnderer);
    // need to make methods to draw pokeballSprites using pokemonCosts later
    
  private:
};