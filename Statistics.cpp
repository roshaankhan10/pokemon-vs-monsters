#include"Statistics.hpp"

Statistics::Statistics(SDL_Rect scoreSrc, SDL_Rect scoreMover, SDL_Texture* texture)
  : scores(scoreSrc, scoreMover)
{
  // pokeball: = {54, 6, 36, 36}
  // greatball: = {6, 6, 36, 36}
  // ultraball: = {102, 6, 36, 36}

  PokeballUnit* pokeball = new PokeballUnit ({54, 6, 36, 36}, {800, 20, 36, 36}, "pokeball", texture);
  PokeballUnit* greatball = new PokeballUnit ({6, 6, 36, 36}, {850, 20, 36, 36}, "greatball", texture);
  PokeballUnit* ultraball = new PokeballUnit ({102, 6, 36, 36}, {900, 20, 36, 36}, "ultraball", texture);
  pokeballs.push_back(pokeball);
  pokeballs.push_back(greatball);
  pokeballs.push_back(ultraball);
}

void Statistics::displayText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y)
{
  SDL_Color textColor = {0, 0, 0}; // White color

  // creates a surface which will be used for creating texture
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
  if (surface == nullptr) {
      std::cerr << "Text rendering failed: " << TTF_GetError() << std::endl;
  }

  // texture created, now just need to display it at certain position
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface); // free up memory

  // Destination rectangle where text is to be drawn
  SDL_Rect destRect = {x, y, 0, 0}; 
  
  // Render the text texture
  SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
  SDL_RenderCopy(renderer, texture, nullptr, &destRect);

}

void Statistics::displayStats(SDL_Renderer* renderer, TTF_Font* font)
{		
  // draws white canvas on which stats will be displayed
  SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_Rect whiteRect = {780, 10, 180, 180};
  SDL_RenderFillRect(renderer, &whiteRect);
  
  // may need to make score a pointer since draw is empty and we may just not override it and leave it as abstract?
  // scores.draw(renderer);

  // iterates over pokeballs to draw them and their quantity
  for (PokeballUnit* pu: pokeballs)
  {
    pu->draw(renderer);
    std::string qty = "x" + std::to_string(pu->ball.amount);
    displayText(renderer, font, qty, pu->moverRect.x, pu->moverRect.y+50);
  }  

  // displays score
  std::string scoreText = "Score: " + std::to_string(scores.points);
  displayText(renderer, font, scoreText, 800, 110);
}

