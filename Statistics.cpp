#include"Statistics.hpp"

Statistics::Statistics(SDL_Rect scoreSrc, SDL_Rect scoreMover, SDL_Texture* texture)
  : scores(scoreSrc, scoreMover)
{
  PokeballUnit* pokeball = new PokeballUnit ({54, 6, 36, 36}, {800, 20, 36, 36}, "pokeball", texture, 10);
  PokeballUnit* greatball = new PokeballUnit ({6, 6, 36, 36}, {850, 20, 36, 36}, "greatball", texture, 3);
  PokeballUnit* ultraball = new PokeballUnit ({102, 6, 36, 36}, {900, 20, 36, 36}, "ultraball", texture);
  pokeballs.push_back(pokeball);
  pokeballs.push_back(greatball);
  pokeballs.push_back(ultraball);
}

// display stats on screen
void Statistics::displayStats(SDL_Renderer* renderer)
{		
  // draws white canvas on which stats will be displayed
  SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_Rect whiteRect = {780, 10, 180, 180};
  SDL_RenderFillRect(renderer, &whiteRect);

  // iterates over pokeballs to draw them and their quantity
  for (PokeballUnit* pu: pokeballs)
  {
    pu->draw(renderer);
    std::string qty = "x" + std::to_string(pu->ball.amount);
    TTF_Font* font = displayer.loadFont("assets/16020_FUTURAM.ttf", 24);
    displayer.displayText(renderer, font, qty, pu->moverRect.x, pu->moverRect.y+50);
  }  

  // displays score
  scores.draw(renderer);
}

// updates pokeballs of player based on the type and qty of pokeball which enemy drops
void Statistics::updateBalls(std::string ballType, int qty)
{
  if (ballType == "pokeball")
    pokeballs[0]->ball.amount += qty;
  else if (ballType == "greatball")
    pokeballs[1]->ball.amount += qty;
  else
    pokeballs[2]->ball.amount += qty;
}

// determines if player has enough pokeballs to deploy the selected pokemon from menu 
// (whose pokeball is passed here)
bool Statistics::haveBalls(Pokeball ball)
{
  for (int i = 0; i < pokeballs.size(); i++)
  {
    if (pokeballs[i]->ball.ballType == ball.ballType)
    {
      return pokeballs[i]->ball.amount >= ball.amount;
    }
  }
  return false;
}