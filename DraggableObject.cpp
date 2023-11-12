#include "DraggableObject.hpp"

DraggableObject::DraggableObject(SDL_Texture* Texture, SDL_Rect SrcRect, SDL_Rect MoverRect) 
  : texture(Texture), Unit(SrcRect, MoverRect), origPosition(MoverRect), isDragged(false)
{
}
       
// When the object is being dragged, update its position based on the mouse cursor's movement.
void DraggableObject::UpdatePosition(int mouseX, int mouseY) 
{
  moverRect.x = mouseX - (moverRect.w / 2);
  moverRect.y = mouseY - (moverRect.h / 2);
  // call draw here if not working outside?
}

// draws the draggable object at its current position
void DraggableObject::draw(SDL_Renderer* renderer) 
{
  SDL_RenderCopy(renderer, texture, &srcRect, &moverRect);
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