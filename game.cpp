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

	if (pokemons == NULL || gTexture == NULL || monsters == NULL || projectiles == NULL || pokeballSprites == NULL)
	{
			printf("Unable to run due to error: %s\n",SDL_GetError());
			success =false;
	} 

	font = loadFont("assets/16020_FUTURAM.ttf", 24);
	if (font == NULL) 
	{
		printf("Unable to run due to error: %s\n",TTF_GetError());
		success = false;
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
	pokemons = NULL;
	monsters = NULL;
	pokeballs = NULL;
	projectiles = NULL;
	pokeballSprites = NULL;

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

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

// Function to load a font
TTF_Font* Game::loadFont(const std::string& fontPath, int fontSize) 
{
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Font loading failed: " << TTF_GetError() << std::endl;
    }
    return font;
}

// Function to render text
SDL_Texture* Game::renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color) 
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        std::cerr << "Text rendering failed: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
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

bool Game::IsMouseOverDraggableObject(int x, int y, std::vector<DraggableObject*> objects, DraggableObject*& selectedObject) {
	for (int i = 0; i < objects.size(); i++)
	{
		// Check if the mouse coordinates are within the object's bounding box
		if (x >= objects[i]->moverRect.x && x <= objects[i]->moverRect.x + objects[i]->moverRect.w && y >= objects[i]->moverRect.y && y <= objects[i]->moverRect.y + objects[i]->moverRect.h) 
		{ 
			// Store the selected object for future reference
			selectedObject = objects[i];
			return true;
		}
	}
	return false;
}

void Game::run( )
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
	
	pokemonMenu.pokemonIcons.push_back(braviary);
	pokemonMenu.pokemonIcons.push_back(charizard);
	pokemonMenu.pokemonIcons.push_back(metagross);
	pokemonMenu.pokemonIcons.push_back(pikachu);
	pokemonMenu.pokemonIcons.push_back(azumarill);

	// creating grid to store all pokemon
	Grid grid{pokemons, monsters, projectiles, pokeballSprites, 50, 155, 73, 83, 5, 9};	

	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
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
					if (IsMouseOverDraggableObject(xMouse, yMouse, pokemonMenu.pokemonIcons, selectedPokemon)) 
					{
						// You can now track that selectedPokemon is being dragged
						if (!selectedPokemon->isCoolingdown())
						selectedPokemon->StartDragging();
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

		//***********************draw the objects here********************
		
    // Create a rectangle with white color 
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_Rect whiteRect = {240, 30, 300, 60};
    SDL_RenderFillRect(gRenderer, &whiteRect);
		
		// draws the menu, including the selectedPokemon as it is coordinates are changed by reference through selectedPokemon
		pokemonMenu.drawMenu(gRenderer);

		// clears all dead characters
		grid.cleanCharacters();

		// draws all pokemons placed on grid
		grid.drawGrid(gRenderer);

		// spawn enemy randomly
		grid.shouldEnemySpawn();

		// draws all enemies
		grid.drawEnemies(gRenderer);

		// draws stats
		grid.stats.displayStats(gRenderer, font);

		// draws capacity of enemies that can spawn, may need to move this to grid class
		std::string capacity = "Wave no. " + std::to_string(grid.currCap);
		grid.stats.displayText(gRenderer, font, capacity, 800, 150);
				
		//****************************************************************
		SDL_RenderPresent(gRenderer); //displays the updated renderer

		// reduced delay to 50 ms for smooth transitions
		SDL_Delay(120);	//causes sdl engine to delay for specified miliseconds
	}

	// free heap to prevent memory leakages
	delete braviary;
	delete charizard;
	delete azumarill;
	delete metagross;
	delete pikachu;

	for (int i = 0; i < pokemonMenu.pokemonIcons.size(); i++)
	{
		// initialize them to nullptr to prevent dangling pointers
		pokemonMenu.pokemonIcons[i] = nullptr ;
	}
	
	// initialized to nullptr to prevent dangling pointers
	selectedPokemon = nullptr;
}
