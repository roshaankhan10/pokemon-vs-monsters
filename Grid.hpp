#include<SDL.h>
#include<iostream>
#include<vector>
#include"Pokemon.hpp"
#include"Enemy.hpp"
#include"Statistics.hpp"

class Grid
{
public:
  // Grid(SDL_Texture* Texture, SDL_Texture* enem, SDL_Texture* proj, SDL_Texture* pokes, int x, int y, int w, int h, int rows, int cols); 
  Grid(SDL_Texture* Texture, SDL_Texture* enem, SDL_Texture* proj, SDL_Texture* pokes, SDL_Texture* projE, int x, int y, int w, int h, int rows, int cols);
  ~Grid();
  
  // create some methods that can be utilized in other classes and for grid itself

  // for instance, to insert a new pokemon, if space in given index
  int insertIndex(int x, int y);
  bool placePokemon(int x, int y, SDL_Rect src);
  // void placePokemon(int x, int y, SDL_Rect src); roshaan's commit
  void drawGrid(SDL_Renderer* renderer);

  void spawnEnemy();
  void shouldEnemySpawn();
  void drawEnemies(SDL_Renderer* renderer);
  void cleanCharacters();
  int currCap = 0; // stores capacity of current enemies
  Statistics stats;

  // handles game over logic
  bool isGameOver();

private:
  // the array that will store coordinates of each tile on the grid/background
  int startX, startY, tileWidth, tileHeight, numRows, numCols;

  // stores health of player house
  Healthbar playerHealth;

  // multiple arrays, each for a purpose indicated by their name
  std::vector<SDL_Rect> tiles; // for each tile on the grid and it's coordinates
  std::vector<Pokemon*> pokemons; // pointers for each pokemon on the grid
  std::vector<Pokemon*> availablePokemons; // pointers for pokemon users can deploy
  std::vector<Enemy*> enemies; // pointers for enemies on the grid
  std::vector<Enemy*> possibleEnemies; // pointers for all possible enemies
  std::vector<Projectile*> projectiles; // pointers for pokemon projectiles
  std::vector<Projectile*> projectilesE; // pointers for enemy projectiles
  
  // textures for sprite sheets
  SDL_Texture* texture; // texture for pokemon
  SDL_Texture* enemyTexture; // texture for enemy
  SDL_Texture* projTexture; // texture for pokemon projectile
  SDL_Texture* projTextureE; // texture for enemy projectile
  SDL_Texture* pokeballTexture; // texture for pokeball

  int spawnInterval = 10000; // stores interval in ms between successive spawns, rn set to 10s
  uint32_t lastSpawnTime = 0; // stores time in ms when last spawn occurred
  int enemiesKilled = 0; // stored count of enemies killed in the particular wave
  
  bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2); 
  bool checkInRange(const SDL_Rect& rect, const int range, const bool isPokemon);
};