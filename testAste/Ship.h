/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#pragma once

#include "Global.h"

class Ship
{
public:

  virtual void update() = 0;

  virtual void draw( sf::RenderTarget& aRenderTarget ) = 0;

  void ApplyTorusWorld( sf::Vector2f& aPosition )
  {
    if ( aPosition.x < 0.0f )
      aPosition.x = Global::GetInstance().getWorldWidth();
    else if ( aPosition.x > Global::GetInstance().getWorldWidth() )
      aPosition.x = 0.0f;
    if ( aPosition.y < 0.0f )
      aPosition.y = Global::GetInstance().getWorldHeight();
    else if ( aPosition.y > Global::GetInstance().getWorldHeight() )
      aPosition.y = 0.0f;
  }
};
