#include "Game.hpp"

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Pokemon vs Monsters", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				
				// Initialize SDL_ttf
				else if (TTF_Init() == -1) 
				{
					printf( "SDL_ttf initialization failed: %s\n", TTF_GetError() );
					// std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
					success = false;
				}

				// initialize mixer
				else if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}

			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	
  gTexture = loadTexture("assets/backgroundd.png");
	pokemons = loadTexture("assets/pokemons.png");
  monsters = loadTexture("assets/enemies.png");
  projectiles = loadTexture("assets/projectiles.png");
  pokeballSprites = loadTexture("assets/pokeballs.png");
	projectilesE = loadTexture("assets/enemProjectiles.png");

	if (pokemons == NULL || gTexture == NULL || monsters == NULL || projectiles == NULL || pokeballSprites == NULL || projectilesE == NULL)
	{
			printf("Unable to run due to error: %s\n",SDL_GetError());
			success =false;
	} 

	// if all pictures loaded, load background music
	else 
	{
		bgMusic = Mix_LoadMUS("assets/backMusicStart.wav");
		if (bgMusic == NULL)
		{
			printf("Unable to run due to error: %s\n",Mix_GetError());
			success =false;
		}

		// if sound also loaded, load font
		else 
		{
			font = displayer.loadFont("assets/16020_FUTURAM.ttf", 24);
			if (font == NULL) 
			{
				printf("Unable to run due to error: %s\n",TTF_GetError());
				success = false;
			}
		}
	}
	
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(pokemons);
	SDL_DestroyTexture(monsters);
	SDL_DestroyTexture(pokeballs);
	SDL_DestroyTexture(projectiles);
	SDL_DestroyTexture(pokeballSprites);
	SDL_DestroyTexture(projectilesE);
	pokemons = NULL;
	monsters = NULL;
	pokeballs = NULL;
	projectiles = NULL;
	pokeballSprites = NULL;
	projectilesE = NULL;

	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	if (font != NULL) 
	{
			TTF_CloseFont(font);
	}
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//destroy Music
	Mix_FreeMusic(bgMusic);
	bgMusic = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

bool Game::IsMouseOverDraggableObject(int x, int y, std::vector<DraggableObject*> objects, DraggableObject*& selectedObject, int& index) {
	for (int i = 0; i < objects.size(); i++)
	{
		// Check if the mouse coordinates are within the object's bounding box
		if (x >= objects[i]->moverRect.x && x <= objects[i]->moverRect.x + objects[i]->moverRect.w && y >= objects[i]->moverRect.y && y <= objects[i]->moverRect.y + objects[i]->moverRect.h) 
		{ 
			// Store the selected object for future reference
			selectedObject = objects[i];
			index = i;
			return true;
		}
	}
	return false;
}

bool Game:: StartScreen(){
	SDL_Event e;
	SDL_Texture* startbutton = NULL;
	startbutton = loadTexture("assets/download1.png");
	SDL_Texture* startbackground = NULL; 
	startbackground = loadTexture("assets/intro.png");

	// if we are unable to load textures, we can't display start screen so return false
	if (startbutton == NULL || startbackground == NULL)
	{
			printf("Unable to run due to error: %s\n",SDL_GetError());
			return false;
	} 

	// render background and start button
	SDL_Rect startbuttonrect={450,275,100,50};
	SDL_Rect startbackgroundrect={0,0,1000,600};
	SDL_RenderCopy(gRenderer,startbackground,NULL,&startbackgroundrect);
	SDL_RenderCopy(gRenderer,startbutton,NULL,&startbuttonrect);

	// loop runs to keep displaying start screen until user clicks on start button
	bool quitStart = false;
	while(!quitStart)
	{
		while(SDL_PollEvent( &e ) != 0 )
		{
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x >= startbuttonrect.x && x <= startbuttonrect.x+100 && y >= startbuttonrect.y && y<= startbuttonrect.y+50){
					quitStart = true;
				}
			}
		}
		SDL_RenderCopy(gRenderer, startbutton, NULL, &startbuttonrect);
		SDL_RenderPresent(gRenderer);
	}

	// destroy textures as not needed anymore
	SDL_DestroyTexture(startbutton);
	SDL_DestroyTexture(startbackground);
	
	// now that screen worked fine, return true
	return true;
}

bool Game::GOScreen(bool* w){
	SDL_Event e;
	SDL_Texture* background = NULL; 
	background = loadTexture("assets/GameOverScreen.png");

	// if we are unable to load textures, we can't display GameOver screen so return false
	if (background == NULL)
	{
			printf("Unable to run due to error: %s\n",SDL_GetError());
			return false;
	} 

	// render background
	SDL_Rect backgroundrect={0,0,1000,600};
	SDL_RenderCopy(gRenderer,background,NULL,&backgroundrect);

	// loop runs to keep displaying GameOver screen until user clicks on exit button
	bool quitGameOver = false;
	while(!quitGameOver)
	{
		while(SDL_PollEvent( &e ) != 0 )
		{
			if (e.type == SDL_QUIT)
			{
				quitGameOver = true;
			}

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x >= 220 && x <= 420 && y >= 345 && y<= 375){
					*w=true;
					quitGameOver = true;
				}
				if (x >= 625 && x <= 750 && y >= 345 && y<= 375){
					*w=false;
					quitGameOver = true;
				}
			}
		}
		SDL_RenderCopy(gRenderer,background,NULL,&backgroundrect);
		SDL_RenderPresent(gRenderer);
	}

	// destroy textures as not needed anymore
	SDL_DestroyTexture(background);
	
	// now that screen worked fine, return true
	return true;
}

void Game::run( bool* x )
{
	bool quit = false;
	SDL_Event e;
	
	// creates an object which will store pointer to the current object being dragged
	DraggableObject* selectedPokemon = nullptr;

	// declares variable of menu which will store all avaialable pokemon and their costs (costs not implemented yet)
	Menu pokemonMenu;
	
	// creates draggable objects for each pokemon and push in pokemonMenu's icons
	DraggableObject* braviary = new DraggableObject(pokemons, {11, 7, 88, 82}, {250, 40, 50, 50});
	DraggableObject* charizard = new DraggableObject(pokemons, {511,5,75,85}, {310, 30, 60, 60});
	DraggableObject* metagross = new DraggableObject(pokemons, {949, 6, 77, 52}, {380, 50, 60, 40});
	DraggableObject* pikachu = new DraggableObject(pokemons, {1365, 0, 39, 46}, {450, 50, 35, 35});
	DraggableObject* azumarill = new DraggableObject(pokemons, {1619,2,61,60}, {490, 40, 50, 50});
	
	pokemonMenu.pokemonIcons.push_back(pikachu);
	pokemonMenu.pokemonIcons.push_back(azumarill);
	pokemonMenu.pokemonIcons.push_back(braviary);
	pokemonMenu.pokemonIcons.push_back(charizard);
	pokemonMenu.pokemonIcons.push_back(metagross);

	PokeballUnit* pikaball = new PokeballUnit({54, 6, 36, 36}, {450, 95, 10, 10}, "pokeball", pokeballSprites, 3);
	PokeballUnit* azuball = new PokeballUnit({54, 6, 36, 36}, {500, 95, 10, 10}, "pokeball", pokeballSprites, 5);
	PokeballUnit* bravball = new PokeballUnit({6, 6, 36, 36}, {260, 95, 10, 10}, "greatball", pokeballSprites, 3);
	PokeballUnit* charball = new PokeballUnit({6, 6, 36, 36}, {320, 95, 10, 10}, "greatball", pokeballSprites, 5);
	PokeballUnit* metaball = new PokeballUnit({102, 6, 36, 36}, {390, 95, 10, 10}, "ultraball", pokeballSprites, 2);

	pokemonMenu.pokemonCosts.push_back(pikaball);
	pokemonMenu.pokemonCosts.push_back(azuball);
	pokemonMenu.pokemonCosts.push_back(bravball);
	pokemonMenu.pokemonCosts.push_back(charball);
	pokemonMenu.pokemonCosts.push_back(metaball);

	// creating grid to store all pokemon
	Grid grid{pokemons, monsters, projectiles, pokeballSprites, projectilesE, 50, 155, 73, 83, 5, 9};	

	// to check if game over or not
	bool gameOver = false;

	// to overlay red rect when player doesn't have enough pokeballs to deploy a pokemon
	bool doOverlay = false;

	// keeps tracks of the index of selected pokemon from menu				
	int index;

	// displays start screen, if it works fine, returns true, else false
	if (!StartScreen())
	{
		// if start screen doesn't work, quit the game
		quit = true;
	}

	while( !quit )
	{

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				Mix_HaltMusic();
				if (!GOScreen(x))
					{
						// if gameover screen doesn't work, quit the game
						quit = true;
					}
				quit = true;
			}

			//User selects a draggable object
			if (e.type == SDL_MOUSEBUTTONDOWN) 
			{
      	if (e.button.button == SDL_BUTTON_LEFT) 
				{
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					
					// Check if the mouse click is on a draggable object
					if (IsMouseOverDraggableObject(xMouse, yMouse, pokemonMenu.pokemonIcons, selectedPokemon, index)) 
					{
						// ensures pokemon is not on cooldown
						if (!selectedPokemon->isCoolingdown())
						{
							// ensures player has enough pokeballs to deploy it
						  if (grid.stats.haveBalls(pokemonMenu.pokemonCosts[index]->ball))
							{
								// You can now track that selectedPokemon is being dragged
								selectedPokemon->StartDragging();
							}
							else
							{
								// sets doOverlay to true which will later display a block indicating cost don't match after menu is drawn
								doOverlay = true;
							}
						}
          }
        } 
				// enemy no longer spawn due to right click
      }
			
			// User moves a draggable object
			if (e.type == SDL_MOUSEMOTION && selectedPokemon != nullptr) 
			{
				if (selectedPokemon->IsBeingDragged()) 
				{
					// Update the position of the dragged selectedPokemon
					selectedPokemon->UpdatePosition(e.motion.x, e.motion.y);
				}
      } 

			// when user drops a draggable object
			if (e.type == SDL_MOUSEBUTTONUP && selectedPokemon != nullptr) 
			{
				if (selectedPokemon->IsBeingDragged() && e.button.button == SDL_BUTTON_LEFT) 
				{
					// These are the coordinates where the selectedPokemon was dropped
					// hence, these coordinates will be utilized later to insert pokemon in grid
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					if (grid.placePokemon(xMouse, yMouse, selectedPokemon->srcRect))
					{
						selectedPokemon->startCooldown();
						grid.stats.updateBalls(pokemonMenu.pokemonCosts[index]->ball.ballType, 
						-pokemonMenu.pokemonCosts[index]->ball.amount);
					}

					// Now we can stop dragging the selectedPokemon and return it to it's original position
					selectedPokemon->StopDragging();

					// since no pokemon is selected, change it back to nullptr
					selectedPokemon = nullptr;
				}
      }
		}

		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer

		if (!quit)
		{

			//***********************draw the objects here********************
			
			// Create a rectangle with white color 
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_Rect whiteRect = {240, 30, 300, 80};
			SDL_RenderFillRect(gRenderer, &whiteRect);
			
			// draws the menu, including the selectedPokemon as it is coordinates are changed by reference through selectedPokemon
			pokemonMenu.drawMenu(gRenderer);

			// overlays a red rect when stats are not enough to deploy selected pokemon
			if (doOverlay)
			{
				SDL_SetRenderDrawColor( gRenderer, 0x63, 0x03, 0x11, 0x05 );
				SDL_RenderFillRect(gRenderer, &selectedPokemon->moverRect);
				doOverlay = false;
			}

			// clears all dead characters
			grid.cleanCharacters();

			// draws all pokemons placed on grid
			grid.drawGrid(gRenderer);

			// spawn enemy randomly
			grid.shouldEnemySpawn();

			// draws all enemies
			grid.drawEnemies(gRenderer);

			// draws stats
			grid.stats.displayStats(gRenderer);

			// draws capacity of enemies that can spawn, may need to move this to grid class
			std::string capacity = "Wave no. " + std::to_string(grid.currCap);
			displayer.displayText(gRenderer, font, capacity, 800, 150);
			
			// need to load font again as deleted in displayer
			font = displayer.loadFont("assets/16020_FUTURAM.ttf", 24);

			// checks if game is over or not
			gameOver = grid.isGameOver();
					
			//****************************************************************
			SDL_RenderPresent(gRenderer); //displays the updated renderer

			// reduced delay to 120 ms for smooth transitions
			SDL_Delay(120);	//causes sdl engine to delay for specified miliseconds
			
			// play the music 
			if(Mix_PlayingMusic()==0){
				Mix_PlayMusic(bgMusic,2);
			}
		}

	
		// checks game over condition
		if (gameOver)
		{
			Mix_HaltMusic();
			if (!GOScreen(x))
					{
						// if gameover screen doesn't work, quit the game
						quit = true;
					}
			quit = true;
		}
		
	}

	// free heap to prevent memory leakages
	delete braviary;
	delete charizard;
	delete azumarill;
	delete metagross;
	delete pikachu;

	delete bravball;
	delete charball;
	delete azuball;
	delete metaball;
	delete pikaball;

	for (int i = 0; i < pokemonMenu.pokemonIcons.size(); i++)
	{
		// initialize them to nullptr to prevent dangling pointers
		pokemonMenu.pokemonIcons[i] = nullptr ;
	}
	
	for (int i = 0; i < pokemonMenu.pokemonCosts.size(); i++)
	{
		// initialize them to nullptr to prevent dangling pointers
		pokemonMenu.pokemonCosts[i] = nullptr ;
	}
		
	// initialized to nullptr to prevent dangling pointers
	selectedPokemon = nullptr;
}
