#include "DraggableObject.hpp"
#include<cmath>

DraggableObject::DraggableObject(SDL_Texture* Texture, SDL_Rect SrcRect, SDL_Rect MoverRect) 
  : texture(Texture), Unit(SrcRect, MoverRect), origPosition(MoverRect), isDragged(false)
{}
       
// When the object is being dragged, update its position based on the mouse cursor's movement.
void DraggableObject::UpdatePosition(int mouseX, int mouseY) 
{
  moverRect.x = mouseX - (moverRect.w / 2);
  moverRect.y = mouseY - (moverRect.h / 2);
}

// draws the draggable object at its current position
void DraggableObject::draw(SDL_Renderer* renderer) 
{
  // draw draggable object
  SDL_RenderCopy(renderer, texture, &srcRect, &moverRect);

  // cooldown drawing
  if (timer > 0.0)
  {
    // y and h are taken from menu box while x and w is of character
    renderShrinkingRectangle(renderer, origPosition.x-2, 30, origPosition.w+2, 63, timer);
    timer -= 0.01;
  }
  if (timer <= 0.0 && onCooldown)
  {
    onCooldown = false;
  }
}

// tells if it's being dragged or not
bool DraggableObject::IsBeingDragged() const 
{
  return isDragged;
}

// starts dragging the object
void DraggableObject::StartDragging() 
{
  isDragged = true;
}

// stops dragging the object and returns it back to orginal position
void DraggableObject::StopDragging() 
{
  isDragged = false;
  moverRect = origPosition;
}

bool DraggableObject::isCoolingdown() const
{
  return onCooldown;
}

void DraggableObject::startCooldown()
{
  timer = 1.0;
  onCooldown = true;
}

void DraggableObject::renderCooldownRing(SDL_Renderer* renderer, int x, int y, int radius, double cooldownPercentage) 
{
    // Set the drawing color for the cooldown ring (e.g., black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Calculate the start and end angles based on the cooldown percentage
    double startAngle = 0;
    double endAngle = 2 * M_PI * cooldownPercentage;

    /// Calculate the outer and inner radii based on thickness, for now, thickness is 2
    int outerRadius = radius + 2 / 2;
    int innerRadius = radius - 2 / 2;

    // Draw the filled portion of the cooldown ring
    for (double angle = startAngle; angle < endAngle; angle += 0.01) {
        int outerX = static_cast<int>(x + outerRadius * std::cos(angle));
        int outerY = static_cast<int>(y + outerRadius * std::sin(angle));

        int innerX = static_cast<int>(x + innerRadius * std::cos(angle));
        int innerY = static_cast<int>(y + innerRadius * std::sin(angle));

        SDL_RenderDrawLine(renderer, innerX, innerY, outerX, outerY);
    }
    
    // Set the drawing color back to default (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void DraggableObject::renderShrinkingRectangle(SDL_Renderer* renderer, int x, int y, int width, int height, double cooldownPercentage) 
{
    // Set the drawing color for the shrinking rectangle (translucent gray)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 5);

    // Calculate the position and size of the shrinking rectangle
    SDL_Rect rect = {
        static_cast<int>(x),
        static_cast<int>(y + height * (1.0 - cooldownPercentage)),
        static_cast<int>(width),
        static_cast<int>(height * cooldownPercentage)
    };

    // Render the rectangle
    SDL_RenderFillRect(renderer, &rect);

    // Set the drawing color back to default (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}