/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#pragma once

#include "Ship.h"

class ShipStiff : public Ship
{
public:

  ShipStiff();
  ~ShipStiff();

  void update() override;

  void draw( sf::RenderTarget& aRenderTarget ) override;

private:

  float mSideThrustersRadPerSec;
  float mRearThrustersKmPerSec;

  std::unique_ptr<sf::CircleShape> mShape;
  sf::Vector2f mFrontVector;
  sf::Vector2f mPosition;
  sf::Transform mTransform;
};
