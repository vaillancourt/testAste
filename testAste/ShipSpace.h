/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#pragma once

#include "Ship.h"

class ShipSpace : public Ship
{
public:

  ShipSpace();
  ~ShipSpace();

  void update() override;

  void draw( sf::RenderTarget& aRenderTarget ) override;

private:

  float mSideThrustersRadPerSec;
  float mRearThrustersKmPerSec;
  float mFrontThrustersKmPerSec;
  float mVelocityMax;

  std::unique_ptr<sf::CircleShape> mShape;
  sf::Vector2f mFrontVector;
  sf::Vector2f mPosition;
  sf::Vector2f mVelocity;
  sf::Transform mTransform;
};
