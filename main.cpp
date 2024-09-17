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

    // w is used to ensure game keeps running
    bool w=true;

    while(w){
        // passed by reference so it can manipulated and used for screen transitioning
        game.run(&w);
    }


    // close game when running stops
    game.close();

    return 0;
}