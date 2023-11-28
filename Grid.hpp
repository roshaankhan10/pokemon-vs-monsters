#include<SDL.h>
#include<iostream>
#include<vector>
#include"Pokemon.hpp"
#include"Enemy.hpp"
#include"Statistics.hpp"

class Grid
{
public:
  Grid(SDL_Texture* Texture, SDL_Texture* enem, SDL_Texture* proj, SDL_Texture* pokes, int x, int y, int w, int h, int rows, int cols);
  ~Grid();
  
  // create some methods that can be utilized in other classes and for grid itself

  // for instance, to insert a new pokemon, if space in given index
  int insertIndex(int x, int y);
  bool placePokemon(int x, int y, SDL_Rect src);
  void drawGrid(SDL_Renderer* renderer);

  void spawnEnemy();
  void shouldEnemySpawn();
  void drawEnemies(SDL_Renderer* renderer);
  void cleanCharacters();
  int currCap = 0; // stores capacity of current enemies
  Statistics stats;

private:
  // the array that will store coordinates of each tile on the grid/background
  int startX, startY, tileWidth, tileHeight, numRows, numCols;
  std::vector<SDL_Rect> tiles;
  std::vector<Pokemon*> pokemons;
  std::vector<Pokemon*> availablePokemons;
  std::vector<Enemy*> enemies;
  std::vector<Enemy*> possibleEnemies;
  std::vector<Projectile*> projectiles;
  SDL_Texture* texture;
  SDL_Texture* enemyTexture;
  SDL_Texture* projTexture;
  int spawnInterval = 5000; // stores interval in ms between successive spawns, rn set to 5s
  uint32_t lastSpawnTime = 0; // stores time in ms when last spawn occurred
  int enemiesKilled = 0; // stored count of enemies killed in the particular wave
  SDL_Texture* pokeballTexture;
  
  bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2); 
};