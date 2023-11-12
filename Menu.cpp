#include"Menu.hpp"

// draws all pokemon Icons in the menu
void Menu::drawMenu(SDL_Renderer* gRnderer)
{
  for (int i = 0; i < pokemonIcons.size(); i++)
  {
    pokemonIcons[i]->draw(gRnderer);
  }
}