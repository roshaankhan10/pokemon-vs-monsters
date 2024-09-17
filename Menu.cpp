#include"Menu.hpp"

// draws all pokemon Icons in the menu
void Menu::drawMenu(SDL_Renderer* gRnderer)
{
  for (int i = 0; i < pokemonIcons.size(); i++)
  {
    pokemonIcons[i]->draw(gRnderer);
  }

  for (int i = 0; i < pokemonCosts.size(); i++)
  {
    pokemonCosts[i]->draw(gRnderer);

    std::string qty = "x " + std::to_string(pokemonCosts[i]->ball.amount);
    TTF_Font* font = displayer.loadFont("assets/16020_FUTURAM.ttf", 14);
    if (font == NULL) 
      printf("Unable to run due to error: %s\n",TTF_GetError());
    else
      displayer.displayText(gRnderer, font, qty, pokemonCosts[i]->moverRect.x+15, pokemonCosts[i]->moverRect.y-5);
  }
}