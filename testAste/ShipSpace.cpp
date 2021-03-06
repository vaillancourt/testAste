/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */

#include "precomp.h"

#include "ShipSpace.h"

#include "Global.h"
#include "SfUtil.h"

ShipSpace::ShipSpace()
  : mShape(new sf::CircleShape(20.0f, 3u))
  , mFrontVector( 0.0f, -1.0f )
  , mPosition(Global::GetInstance().getWorldWidth() / 2.0f, Global::GetInstance().getWorldHeight() / 2.0f )
  , mSideThrustersRadPerSec( sfUtil::PI )
  , mRearThrustersKmPerSec( 0.0010 )
  , mFrontThrustersKmPerSec( 0.0005 )
  , mSpeedMax( 0.00750 )
{
  mShape->setFillColor( sf::Color( 255, 255, 255, 255 ) );

  float radiusKm = 0.0400f;
  float radiusPixels = radiusKm * Global::GetInstance().getWorldToGraphicsRatio();

  mShape->setRadius( radiusPixels );
  mShape->setOrigin( radiusPixels, radiusPixels );
}


ShipSpace::~ShipSpace()
{}

void
ShipSpace::update()
{


  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
  {
    mTransform = mTransform.rotate( sfUtil::radiansToDegrees( -mSideThrustersRadPerSec * Global::GetInstance().getFrameTime() ) );
  }

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
  {
    mTransform = mTransform.rotate( sfUtil::radiansToDegrees( mSideThrustersRadPerSec * Global::GetInstance().getFrameTime() ) );
  }

  bool shouldApplyOffset = false;

  sf::Vector2f offset;

  if (
       sf::Keyboard::isKeyPressed( sf::Keyboard::Up )
    && sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
  {
    offset =
        (  mFrontVector * ( mRearThrustersKmPerSec  * Global::GetInstance().getFrameTime() ) )
      + ( -mFrontVector * ( mFrontThrustersKmPerSec * Global::GetInstance().getFrameTime() ) );
    shouldApplyOffset = true;
  }
  else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
  {
    offset = mFrontVector * ( mRearThrustersKmPerSec  * Global::GetInstance().getFrameTime() );
    shouldApplyOffset = true;
  }
  else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
  {
    offset = -mFrontVector * ( mFrontThrustersKmPerSec * Global::GetInstance().getFrameTime() );
    shouldApplyOffset = true;
  }

  if ( shouldApplyOffset )
  {
    sf::Vector2f orientedOffset = mTransform * offset;

    mVelocity += orientedOffset;

    float currentSpeed = sfUtil::lenght( mVelocity );

    if ( currentSpeed > mSpeedMax )
    {
      sf::Vector2f direction = mVelocity / currentSpeed;
      mVelocity = direction * mSpeedMax;
    }
  }

  mPosition = mPosition + mVelocity;

  ApplyTorusWorld( mPosition );
}


void 
ShipSpace::draw( sf::RenderTarget& aRenderTarget )
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
