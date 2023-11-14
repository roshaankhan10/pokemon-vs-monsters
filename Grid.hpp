#include<SDL.h>
#include<iostream>
#include<vector>
#include"Pokemon.hpp"

class Grid
{
public:
  Grid(SDL_Texture* Texture, int x, int y, int w, int h, int rows, int cols);
  ~Grid();
  
  // create some methods that can be utilized in other classes and for grid itself

  // for instance, to insert a new pokemon, if space in given index
  int insertIndex(int x, int y);
  void placePokemon(int x, int y, SDL_Rect src);

  void drawGrid(SDL_Renderer* renderer);

private:
  // the array that will store coordinates of each tile on the grid/background
  int startX, startY, tileWidth, tileHeight, numRows, numCols;
  std::vector<SDL_Rect> tiles;
  std::vector<Pokemon*> pokemons;
  std::vector<Pokemon*> availablePokemons;
  SDL_Texture* texture;
};