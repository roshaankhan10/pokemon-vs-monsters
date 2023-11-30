#include "game.hpp"

int main(int argc, char *argv[]){
    Game game;
    srand(time(NULL));
    // Initialize game, if throws an error during initialization, print error
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
		
    // Load media, if throws an error during loading, print error
    if( !game.loadMedia() ){
        printf( "Failed to load media!\n" );
        return 0;
    }

    // if (game.StartScreen() == false){
    //     game.close();
    // }

    // after initializing and loading, start running the game
    game.run();

    // close game when running stops
    game.close();

    return 0;
}