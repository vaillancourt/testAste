/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#include "precomp.h"

#include "ShipStiff.h"
#include "Global.h"
#include "SfUtil.h"

ShipStiff::ShipStiff()
  : mShape(new sf::CircleShape(20.0f, 3u))
  , mFrontVector( 0.0f, -1.0f )
  , mPosition(Global::GetInstance().getWorldWidth() / 2.0f, Global::GetInstance().getWorldHeight() / 2.0f )
  , mSideThrustersRadPerSec( sfUtil::PI )
  , mRearThrustersKmPerSec( 0.250 )
{
  mShape->setFillColor( sf::Color( 255, 255, 255, 255 ) );

  float radiusKm = 0.0400f;
  float radiusP = radiusKm * Global::GetInstance().getWorldToGraphicsRatio();

  std::cout << radiusP << std::endl;

  mShape->setRadius( radiusP );


  mShape->setOrigin( radiusP, radiusP );
}


ShipStiff::~ShipStiff()
{}

void
ShipStiff::update()
{
  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
  {
    mTransform = mTransform.rotate( sfUtil::radiansToDegrees( -mSideThrustersRadPerSec * Global::GetInstance().getFrameTime() ) );
  }

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
  {
    mTransform = mTransform.rotate( sfUtil::radiansToDegrees( mSideThrustersRadPerSec * Global::GetInstance().getFrameTime() ) );
  }

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
  {
    sf::Vector2f offset = mFrontVector * ( mRearThrustersKmPerSec * Global::GetInstance().getFrameTime() );
    sf::Vector2f orientedOffset = mTransform * offset;

    mPosition = mPosition + orientedOffset;
  }

  ApplyTorusWorld( mPosition );
}


void 
ShipStiff::draw( sf::RenderTarget& aRenderTarget )
{

  sf::Vector2f position( mPosition.x, mPosition.y );
  position.x = position.x * Global::GetInstance().getWorldToGraphicsRatio();
  position.y = position.y * Global::GetInstance().getWorldToGraphicsRatio();

  // Get the angle
  sf::Vector2f angleTrans = mTransform * mFrontVector;
  float angle = std::atan2( angleTrans.y, angleTrans.x ) - std::atan2( mFrontVector.y, mFrontVector.x );
  
  mShape->setRotation( sfUtil::radiansToDegrees( angle ) );
  mShape->setPosition( position.x, position.y );
  aRenderTarget.draw( *mShape );

}
