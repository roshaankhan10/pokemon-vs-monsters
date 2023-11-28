#pragma once
#include<string>

class Pokeball
{
  public:
    Pokeball(std::string ball, int amt);

  // private:
    std::string ballType;
    int amount;
};

// pokeball: = {54, 6, 36, 36}
// greatball: = {6, 6, 36, 36}
// ultraball: = {102, 6, 36, 36}