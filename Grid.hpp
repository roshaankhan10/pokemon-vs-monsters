#include<SDL.h>
#include<vector>
#include"Pokemon.hpp"

class Grid
{
public:
  Grid(int x, int y, int w, int h, int rows, int cols);
  
  // create some methods that can be utilized in other classes and for grid itself
  // for instance, to insert a new pokemon, if space in given index

private:
  // the array that will store coordinates of each tile on the grid/background
  int startX, startY, tileWidth, tileHeight, numRows, numCols;
  vector<SDL_Rect> tiles;
  vector<Pokemon*> pokemons;
};