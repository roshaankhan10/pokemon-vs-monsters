#pragma once
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
    bool isCoolingdown() const;
    void startCooldown();
      
  private:
    SDL_Texture* texture;
    // this is used to original values of moverRect so it can be restored back after dropping
    SDL_Rect origPosition;
    bool isDragged;
    
    double timer = 0.0;
    bool onCooldown = false;
    void renderCooldownRing(SDL_Renderer* renderer, int x, int y, int radius, double cooldownPercentage);
    void renderShrinkingRectangle(SDL_Renderer* renderer, int x, int y, int width, int height, double cooldownPercentage);
};