#include"Grid.hpp"

// vector variables to store all animation states
std::vector<SDL_Rect> pikaStates = {{1365, 0, 39, 46}, {1465, 0, 40, 46}, {1513, 2, 44, 45}, {1562, 3, 46, 44}, {1362, 49, 48, 45}, {1411, 49, 47, 45}, {1463, 48, 44, 44}, {1562, 95, 46, 44}, {1413, 140, 43, 44}, {1413, 186, 43, 45}, {1510, 187, 47, 44}, {1363, 232, 42, 44}, {1413, 186+44, 43, 45}, {1363, 278, 44, 44}, {1462, 279, 48, 44}};

std::vector<SDL_Rect> bravStates = {{11, 7, 88, 82}, {313, 10, 95, 79}, {1, 144, 95, 55}, {103, 144, 95, 55}, {215, 152, 88, 54}, {422, 151, 81, 62}, {14, 261, 81, 62}, {102, 249, 97, 59}};

std::vector<SDL_Rect> charStates = {{511,5,75,85},{597,5,75,85},{684,5,75,85},{772,5,75,85},{859,5,75,85},{506,90,75,85},{597,90,75,85},{684,90,75,85},{772,90,75,85},{859,90,75,85},{506,178,75,88},{597,178,75,88},{684,178,75,88},{772,178,75,88},{859,178,75,88},{508,267,75,85},{597,267,75,85},{684,267,75,85},{772,267,75,85},{859,267,75,85}};

std::vector<SDL_Rect> metaStates = {{949,6,80,52},{1032,6,80,52},{1115,6,80,52},{1198,6,80,52},{1281,6,80,52},{949,64,80,52},{1032,64,80,52},{1115,64,80,52},{1198,64,80,52},{1281,64,80,52},{949,122,80,52},{1032,122,80,52},{1115,122,80,52},{1198,122,80,52},{1281,122,80,52},{949,180,80,52},{1032,180,80,52},{1115,180,80,52},{1198,180,80,52},{1281,180,80,52},{949,238,80,52},{1032,238,80,52},{1115,238,80,52},{1198,238,80,52},{1281,238,80,52},{949,296,80,52},{1032,296,80,52},{1115,296,80,52},{1198,296,80,52},{1281,296,80,52},{949,354,80,52},{1032,354,80,52},{1115,354,80,52},{1198,354,80,52},{1281,354,80,52}};

std::vector<SDL_Rect> azuStates = {{1619,2,61,60},{1692,2,65,60},{1765,2,65,60},{1838,2,65,60},{1911,2,65,60},{1619,66,61,60},{1692,65,65,60},{1765,65,65,60},{1838,63,65,60},{1911,63,65,60},{1619,124,61,60},{1692,125,65,60},{1765,126,65,60},{1838,128,65,60},{1911,126,65,60},{1619,186,61,60},{1692,185,65,60}};

// stores respective display setting of each mover to be used when creating new pokemon
SDL_Rect pikaMover = {18,21,35,35};
SDL_Rect bravMover = {10,13,50,50};
SDL_Rect charMover = {3, 3, 65, 65};
SDL_Rect metaMover = {5,10,65,45};
SDL_Rect azuMover = {10,10,50,50};

// vector variables to store animation states of all enemies
std::vector<SDL_Rect> thanosStates = {{252,4,232, 284}, {736,0,236, 288}, {244,292,228, 284}};
std::vector<SDL_Rect> southpawStates = {{5589, 1, 83, 78}, {5843, 0, 79, 79}, {6256, 1, 80, 157/2}};
std::vector<SDL_Rect> jellaquidStates = {{2289, 16, 264, 252}, {2573, 312,272 , 252}, {2269, 304, 284, 260}};
std::vector<SDL_Rect> birdStates = {{1422, 0, 66, 47}, {1221, 48, 66,45}, {1422, 0, 66, 47}};
std::vector<SDL_Rect> dragonStates = {{4081,0,352,352}, {4076,6,362,344}, {4432,4,360,346}, {4788,4,360,346}, {5148,10,360,346}, {3724,354,360,346}, {4080,352,354,346}, {4430,354,358,346}, {4788,348,362,354}};

SDL_Rect jellaquid = {0, 0,55, 68};
SDL_Rect thanos = {0, 0, 70, 80};
SDL_Rect southpaw = {0, 0, 55, 55};
SDL_Rect bird = {0, 0,65, 75};
SDL_Rect dragon = {0, 0, 70, 80};

// vector variable to store animation states of projectiles
std::vector<SDL_Rect> electroBall = {{1457,98,42,42},{1375,97,40,44},{1295,98,46,45},{1211,92,52,51},{1535,15,50,54},{1455,18,54,50},{1379,19,44,42},{1292,12,53,53},{1211,17,53,47}};

std::vector<SDL_Rect> windBlade = {{1284,176,70,47},{1362,177,76,45},{1461,176,48,49},{1530,191,63,31}};

std::vector<SDL_Rect> fireRing = {{13,19,56,42},{93,20,54,42},{173,20,54,41},{253,19,54,43}};

std::vector<SDL_Rect> whirlpool = {{747,140,29,21},{667,132,28,29},{587,125,30,36},{508,126,29,35},{427,127,29,34},{747,48,29,33},{667,48,28,33},{587,48,30,33},{508,52,29,29},{427,57,29,24}};

std::vector<SDL_Rect> purpleRing = {{1133,172,58,57},{1057,175,50,49},{977,175,50,49},{897,175,50,49},{803,168,73,75},{897,175,50,49},{1042,80,80,80},{965,82,75,76},{882,79,73,79},{803,79,73,82},{1120,7,71,62},{1042,0,80,78},{971,0,80,78},{885,0,80,78},{814,0,80,78}};

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
  Projectile* electroBallPtr = new Projectile(electroBall[0], {0,0,35,35}, electroBall, projTexture);
  projectiles.push_back(electroBallPtr);
  Projectile* windBladePtr = new Projectile(windBlade[0], {0,0,40,40}, windBlade, projTexture);
  projectiles.push_back(windBladePtr);
  Projectile* fireRingPtr = new Projectile(fireRing[0],{0,0,40,40},fireRing,projTexture);
  projectiles.push_back(fireRingPtr);
  Projectile* whirlpoolPtr = new Projectile(whirlpool[0],{0,0,40,40},whirlpool,projTexture);
  projectiles.push_back(whirlpoolPtr);
  Projectile* purpleRingPtr = new Projectile(purpleRing[0],{0,0,40,40},purpleRing,projTexture);
  projectiles.push_back(purpleRingPtr);

  // now insert all available pokemon pointers
  Pokemon* pika = new Pokemon(pikaStates[0], pikaMover, 30, 4, pikaStates, texture, electroBallPtr, 50);
  availablePokemons.push_back(pika);

  Pokemon* brav = new Pokemon(bravStates[0], bravMover, 50, 8, bravStates, texture, windBladePtr, 80);
  availablePokemons.push_back(brav);

  Pokemon* charz = new Pokemon(charStates[0], charMover,50,8,charStates, texture ,fireRingPtr,100);
  availablePokemons.push_back(charz);

  Pokemon* meta = new Pokemon(metaStates[0],metaMover,50,8,metaStates,texture,purpleRingPtr,100);
  availablePokemons.push_back(meta);

  Pokemon* azu = new Pokemon(azuStates[0], azuMover,50,8,azuStates,texture,whirlpoolPtr,50);
  availablePokemons.push_back(azu);

  // now insert all possible enemiesm, in order of weak to strong, i.e. weak inserted at lower index
  Enemy* southpawObj = new Enemy(southpawStates[0], southpaw, 10, 1, 3, southpawStates, enemyTexture, 70);
  Enemy* birdObj = new Enemy(birdStates[0], bird, 7, 4, 6, birdStates, enemyTexture, 60);
  Enemy* jellaquidObj = new Enemy(jellaquidStates[0], jellaquid, 10, 6, 4, jellaquidStates, enemyTexture, 100);
  Enemy* thanosObj = new Enemy(thanosStates[0], thanos, 29, 3, 1, thanosStates, enemyTexture, 200);
  Enemy* dragonObj = new Enemy(dragonStates[0], dragon, 30, 2, 2, dragonStates, enemyTexture, 180);
  possibleEnemies.push_back(southpawObj);
  possibleEnemies.push_back(birdObj);
  possibleEnemies.push_back(jellaquidObj);
  possibleEnemies.push_back(thanosObj);
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
  uint32_t elapsedTime = SDL_GetTicks();
  // interval (in ms) at which difficulty increases by 1, will standardize it later, kept 5s for testing purposes
  uint32_t interval = 5000; 

  int enemyIndex;

  double chance = (double(elapsedTime) / double(interval)) / 100;

  int enemProb = rand() % 1000;

  // decides which enemy should be spawned based on probabiity which changes with time
  if (enemProb < (100 + chance))
    enemyIndex = 4;
  else if (enemProb < (220 + chance))
    enemyIndex = 3;
  else if (enemProb < (370 + chance))
    enemyIndex = 2;
  else if (enemProb < (570 + chance))
    enemyIndex = 1;
  else 
    enemyIndex = 0;

  int lane = rand() % numRows;
  Enemy* newEnemy = new Enemy(possibleEnemies[enemyIndex]->srcRect, {startX, startY+(lane*tileHeight), possibleEnemies[enemyIndex]->moverRect.w, possibleEnemies[enemyIndex]->moverRect.h}, possibleEnemies[enemyIndex]->atkPower, possibleEnemies[enemyIndex]->atkRange, possibleEnemies[enemyIndex]->movingSpeed, possibleEnemies[enemyIndex]->states, possibleEnemies[enemyIndex]->texture, possibleEnemies[enemyIndex]->health.maxHealth);

  enemies.push_back(newEnemy);
}

// function that decides if enemy should spawn or not and does so
void Grid::shouldEnemySpawn()
{
  // increase current capacity when all current enemies killed
  if (enemiesKilled == currCap)
  {
    currCap += 1;
    enemiesKilled = 0;
    if (spawnInterval > 1000) // spawnInterval will decrease by 0.5s, until it reaches lowest (1s)
    {
      spawnInterval -= 500;
    }
  }  

  // only spawn if currCap is not reached
  if (enemies.size() < currCap)
  {
    // check if spawnInterval has reached, only then spawn an enemy
    if (SDL_GetTicks() - lastSpawnTime >= spawnInterval)
      {
        spawnEnemy();
        lastSpawnTime = SDL_GetTicks();
      }
  }
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

void Grid::cleanCharacters()
{
  // sets all dead pokemon to nullptr after freeing memory
  for (int i = 0; i < pokemons.size(); i++)
  {
    if (pokemons[i] != nullptr)
    {
      if (pokemons[i]->isDead())
      {
        pokemons[i]->destroyProjectile(); 
        delete pokemons[i];
        pokemons[i] = nullptr;
      }
    }
  }

  // sets all dead enemies to nullptr after freeing memory
  for (int k = 0; k < enemies.size(); k++)
  {
    // for testing purposes, enemies are killed if they cross 500 units distance
    if (enemies[k]->isDead() || enemies[k]->moverRect.x > 500)
    {
      delete enemies[k];
      enemies[k] = nullptr;
    }
  }
  // now removes all nullptr from enemies
  for (auto it = enemies.begin(); it != enemies.end(); ) 
  {
    if (*it == nullptr)
    {
      it = enemies.erase(it);
      // incremented enemiesKilled for spawn purposes
      enemiesKilled += 1;
    }
    else
      ++it;
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