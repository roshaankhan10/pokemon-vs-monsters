#include"Grid.hpp"

// vector variables to store all animation states
std::vector<SDL_Rect> pikaStates = {{1365, 0, 39, 46}, {1465, 0, 40, 46}, {1513, 2, 44, 45}, {1562, 3, 46, 44}, {1362, 49, 48, 45}, {1411, 49, 47, 45}, {1463, 48, 44, 44}, {1562, 95, 46, 44}, {1413, 140, 43, 44}, {1413, 186, 43, 45}, {1510, 187, 47, 44}, {1363, 232, 42, 44}, {1413, 186+44, 43, 45}, {1363, 278, 44, 44}, {1462, 279, 48, 44}};

std::vector<SDL_Rect> bravStates = {{11, 7, 88, 82}, {313, 10, 95, 79}, {1, 144, 95, 55}, {103, 144, 95, 55}, {215, 152, 88, 54}, {422, 151, 81, 62}, {14, 261, 81, 62}, {102, 249, 97, 59}};

// stores respective display setting of each mover to be used when creating new pokemon
SDL_Rect pikaMover = {18,21,35,35};
SDL_Rect bravMover = {10,13,50,50};

// vector variables to store animation states of all enemies
std::vector<SDL_Rect> thanosStates = {{252,4,232, 284}, {736,0,236, 288}, {244,292,228, 284}};
std::vector<SDL_Rect> monster2States = {{5589, 1, 83, 78}, {5843, 0, 79, 79}, {6256, 1, 80, 157/2}};
std::vector<SDL_Rect> monster1States = {{2289, 16, 264, 252}, {2573, 312,272 , 252}, {2269, 304, 284, 260}};
std::vector<SDL_Rect> birdStates = {{1422, 0, 66, 47}, {1221, 48, 66,45}, {1422, 0, 66, 47}};
std::vector<SDL_Rect> dragonStates = {{4081,0,352,352}, {4076,6,362,344}, {4432,4,360,346}, {4788,4,360,346}, {5148,10,360,346}, {3724,354,360,346}, {4080,352,354,346}, {4430,354,358,346}, {4788,348,362,354}};

SDL_Rect monster1 = {0, 0,55, 68};
SDL_Rect thanos = {0, 0, 70, 80};
SDL_Rect monster2 = {0, 0, 55, 55};
SDL_Rect bird = {0, 0,65, 75};
SDL_Rect dragon = {0, 0, 70, 80};

// vector variable to store animation states of projectiles
std::vector<SDL_Rect> electroBall = {{32, 43, 120, 108}, {225, 33, 120, 120}, {433, 48, 100, 96}, {615, 47, 124, 112}, {805, 37, 124, 124}};

std::vector<SDL_Rect> windBlade = {{809, 246, 112, 95}, {11, 428, 168, 112}, {202, 424, 168, 112}, {391, 427, 178, 112}, {626, 426, 112, 112}, {793, 467, 147, 63}};

// initialize each tile of grid in constructor as well as pushes nullptr for each pokemon
Grid::Grid(SDL_Texture* Texture, SDL_Texture* enem, SDL_Texture* proj, int x = 50, int y = 155, int w = 70, int h = 80, int rows = 5, int cols = 9)
  : startX(x), startY(y), tileWidth(w), tileHeight(h), numRows(rows), numCols(cols), texture(Texture), enemyTexture(enem), projTexture(proj)
{
  for (int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      tiles.push_back({x + (w * j), y + (h * i), w, h});
      pokemons.push_back(nullptr);
    }
  }

  // create all projectiles
  // Projectile(SDL_Rect src, SDL_Rect mover, std::vector<SDL_Rect> frames, SDL_Texture* Texture)
  Projectile* electroBallPtr = new Projectile(electroBall[0], {0,0,35,35}, electroBall, projTexture);
  projectiles.push_back(electroBallPtr);
  Projectile* windBladePtr = new Projectile(windBlade[0], {0,0,40,40}, windBlade, projTexture);
  projectiles.push_back(windBladePtr);

  // now insert all available pokemon pointers
  Pokemon* pika = new Pokemon(pikaStates[0], pikaMover, 30, 4, pikaStates, texture, electroBallPtr, 50);
  availablePokemons.push_back(pika);

  Pokemon* brav = new Pokemon(bravStates[0], bravMover, 50, 8, bravStates, texture, windBladePtr, 80);
  availablePokemons.push_back(brav);

  // now insert all possible enemies
  Enemy* thanosObj = new Enemy(thanosStates[0], thanos, 30, 4, thanosStates, enemyTexture, 150);
  Enemy* monster1Obj = new Enemy(monster1States[0], monster1, 30, 4, monster1States, enemyTexture, 80);
  Enemy* monster2Obj = new Enemy(monster2States[0], monster2, 30, 4, monster2States, enemyTexture, 100);
  Enemy* birdObj = new Enemy(birdStates[0], bird, 30, 4, birdStates, enemyTexture, 60);
  Enemy* dragonObj = new Enemy(dragonStates[0], dragon, 30, 4, dragonStates, enemyTexture, 200);
  possibleEnemies.push_back(thanosObj);
  possibleEnemies.push_back(monster1Obj);
  possibleEnemies.push_back(monster2Obj);
  possibleEnemies.push_back(birdObj);
  possibleEnemies.push_back(dragonObj);
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
        Pokemon* newPokemon = new Pokemon(src, {tiles[index].x + availablePokemons[j]->moverRect.x, tiles[index].y + availablePokemons[j]->moverRect.y, availablePokemons[j]->moverRect.w, availablePokemons[j]->moverRect.h}, availablePokemons[j]->atkPower, availablePokemons[j]->atkRange, availablePokemons[j]->states, availablePokemons[j]->texture, availablePokemons[j]->projectile, availablePokemons[j]->health.maxHealth);
        
        // adjust projectile mover using current tile index
        newPokemon->projectile->moverRect.x = newPokemon->moverRect.x - 20;
        newPokemon->projectile->moverRect.y = newPokemon->moverRect.y;
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
      pokemons[i]->health.draw(renderer);
      if (pokemons[i]->currProj != nullptr)
      {
        // if it's being thrown, draw it
        pokemons[i]->currProj->draw(renderer);

        // if it exceeds boundary, destroy it
        if (pokemons[i]->currProj->moverRect.x <= 10)
        {
          pokemons[i]->destroyProjectile();
          // reducing health when projectile goes offscreen to see health depletion
          pokemons[i]->health.currHealth -= 5;
        }
      }
      // if pokemon's projectile is not being thrown, throw it
      else 
      {
        pokemons[i]->throwProjectile();
      }
    }
  }
}

// spawns an enemy in a random lane
void Grid::spawnEnemy()
{
  int enemyIndex = rand() % possibleEnemies.size();
  int lane = rand() % numRows;
  Enemy* newEnemy = new Enemy(possibleEnemies[enemyIndex]->srcRect, {startX, startY+(lane*tileHeight), possibleEnemies[enemyIndex]->moverRect.w, possibleEnemies[enemyIndex]->moverRect.h}, possibleEnemies[enemyIndex]->atkPower, possibleEnemies[enemyIndex]->atkRange, possibleEnemies[enemyIndex]->states, possibleEnemies[enemyIndex]->texture, possibleEnemies[enemyIndex]->health.maxHealth);
  
  enemies.push_back(newEnemy);
}

// draws enemies 
void Grid::drawEnemies(SDL_Renderer* renderer)
{
  for (int i = 0; i < enemies.size(); i++)
  {
    enemies[i]->moveForward();
    // moves health bar of enemy along with it
    enemies[i]->health.moverRect.x = enemies[i]->moverRect.x;
    enemies[i]->draw(renderer);
    enemies[i]->health.draw(renderer);
  }
}

// destructor to free up heap after program ends
Grid::~Grid()
{
  for (int i = 0; i < pokemons.size(); i++)
  {
    if (pokemons[i] != nullptr)
    {
      // delete curr porjectile
      pokemons[i]->destroyProjectile(); 
      delete pokemons[i];
      pokemons[i] = nullptr;
    }
  }

  for (int j = 0; j < availablePokemons.size(); j++)
  {
    delete availablePokemons[j];
    availablePokemons[j] = nullptr;
  }

  for (int k = 0; k < enemies.size(); k++)
  {
    delete enemies[k];
    enemies[k] = nullptr;
  }

  for (int l = 0; l < projectiles.size(); l++)
  {
    delete projectiles[l];
    projectiles[l] = nullptr;
  }
}