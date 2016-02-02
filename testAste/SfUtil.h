/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#pragma once

namespace sfUtil
{
  static const float PI = 3.141592654f;
  static float degreesToRatians( float aDegrees ) { return aDegrees * PI / 180.0f; }
  static float radiansToDegrees( float aRadians ) { return aRadians / PI * 180.0f; }
  template<class T>
  static T lenght( sf::Vector2<T> aVector ){ return std::sqrt(aVector.x * aVector.x + aVector.y + aVector.y); }
  template<class T>
  static T lenghtSquare( sf::Vector2<T> aVector ){ return aVector.x * aVector.x + aVector.y + aVector.y; }
}
