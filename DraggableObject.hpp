// #pragma once
#include"Unit.hpp"

class DraggableObject : public Unit
{
  // it already has srcRect, moverRect inherited from Unit
  public:
    DraggableObject(SDL_Texture* Texture, SDL_Rect SrcRect, SDL_Rect MoverRect);
    bool IsBeingDragged() const;
    void StartDragging();
    void StopDragging();
    void UpdatePosition(int x, int y);
    void draw(SDL_Renderer* renderer) override;
      
  private:
    SDL_Texture* texture;
    // this is used to original values of moverRect so it can be restored back after dropping
    SDL_Rect origPosition;
    bool isDragged;
};