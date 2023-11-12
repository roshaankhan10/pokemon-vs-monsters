#include"DraggableObject.hpp"
#include"Pokeball.hpp"
#include<vector>

// it contains DraggableObjects and pokeballs(sprites and costs)
class Menu
{
  public:
    std::vector<DraggableObject*> pokemonIcons;
    std::vector<Pokeball> pokemonCosts;
    std::vector<Unit> pokeballSprites;

    void drawMenu(SDL_Renderer* gRnderer);
    // need to make methods to draw pokeballSprites using pokemonCosts later
    
  private:
};