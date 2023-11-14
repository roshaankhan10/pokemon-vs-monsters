#include"Grid.hpp"

// vector variables to store all animation states
std::vector<SDL_Rect> pikaStates = {{1365, 0, 39, 46}, {1465, 0, 40, 46}, {1513, 2, 44, 45}, {1562, 3, 46, 44}, {1362, 49, 48, 45}, {1411, 49, 47, 45}, {1463, 48, 44, 44}, {1562, 95, 46, 44}, {1413, 140, 43, 44}, {1413, 186, 43, 45}, {1510, 187, 47, 44}, {1363, 232, 42, 44}, {1413, 186+44, 43, 45}, {1363, 278, 44, 44}, {1462, 279, 48, 44}};

std::vector<SDL_Rect> bravStates = {{11, 7, 88, 82}, {313, 10, 95, 79}, {1, 144, 95, 55}, {103, 144, 95, 55}, {215, 152, 88, 54}, {422, 151, 81, 62}, {14, 261, 81, 62}, {102, 249, 97, 59}};

// stores respective display setting of each mover to be used when creating new pokemon
SDL_Rect pikaMover = {18,21,35,35};
SDL_Rect bravMover = {10,13,50,50};

// initialize each tile of grid in constructor as well as pushes nullptr for each pokemon
Grid::Grid(SDL_Texture* Texture, int x = 50, int y = 155, int w = 70, int h = 80, int rows = 5, int cols = 9)
  : startX(x), startY(y), tileWidth(w), tileHeight(h), numRows(rows), numCols(cols), texture(Texture)
{
  for (int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      tiles.push_back({x + (w * j), y + (h * i), w, h});
      pokemons.push_back(nullptr);
    }
  }

  // now insert all available pokemon pointers
  Pokemon* pika = new Pokemon(pikaStates[0], pikaMover, 30, 4, pikaStates, texture);
  availablePokemons.push_back(pika);

  Pokemon* brav = new Pokemon(bravStates[0], bravMover, 50, 8, bravStates, texture);
  availablePokemons.push_back(brav);
}

// loops through the tiles and returns index of the tile corresponding to click, returns -1 if not found
int Grid::insertIndex(int x, int y)
{
  for (int i = 0; i < tiles.size(); i++)
  {
    if (x >= tiles[i].x && x < (tiles[i].x + tiles[i].w) && y >= tiles[i].y && y < (tiles[i].y + tiles[i].h))
    {
      return i;
    }
  }
  return -1;
}

// places pokemon on grid if click was valid
void Grid::placePokemon(int x, int y, SDL_Rect src)
{
  int index = insertIndex(x, y);

  // only draw pokemon if that position exists and is empty
  if (index != -1 && pokemons[index] == nullptr)
  {
    // determine what pokemon to draw and create it's object on heap and store it in pokemons array
    for (int j = 0; j < availablePokemons.size(); j++)
    {
      if (src.x == availablePokemons[j]->srcRect.x && src.y == availablePokemons[j]->srcRect.y)
      {
        Pokemon* newPokemon = new Pokemon(src, {tiles[index].x + availablePokemons[j]->moverRect.x, tiles[index].y + availablePokemons[j]->moverRect.y, availablePokemons[j]->moverRect.w, availablePokemons[j]->moverRect.h}, availablePokemons[j]->atkPower, availablePokemons[j]->atkRange, availablePokemons[j]->states, availablePokemons[j]->texture);
        
        pokemons[index] = newPokemon;

        break;
      }
    }
  }
}

// iterates over the grid and draws all pokemon on that grid
void Grid::drawGrid(SDL_Renderer* renderer)
{
  for (int i = 0; i < pokemons.size(); i++)
  {
    if (pokemons[i] != nullptr)
    {
      pokemons[i]->draw(renderer);
    }
  }
}

// destructor to free up heap after program ends
Grid::~Grid()
{
  for (int i = 0; i < pokemons.size(); i++)
  {
    if (pokemons[i] != nullptr)
    {
      delete pokemons[i];
      pokemons[i] = nullptr;
    }
  }

  for (int j = 0; j < availablePokemons.size(); j++)
  {
    delete availablePokemons[j];
    availablePokemons[j] = nullptr;
  }
}