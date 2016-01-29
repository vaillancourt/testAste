/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#include "Global.h"
#include "Simulation.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>


int 
main(void)
{
  Global::InitInstance();
  Simulation::InitInstance();
  Simulation::GetInstance().populate();

  sf::RenderWindow window(
    sf::VideoMode(
    Global::GetInstance().getWindowWidth(), Global::GetInstance().getWindowHeight()), 
    "SFML works!");

  std::chrono::milliseconds frameDurationMs( static_cast<int>(Global::GetInstance().getFrameTime() * 1000.0f ) );

  int frameCount = 0;

  auto secondEnd = std::chrono::high_resolution_clock::now() + std::chrono::seconds( 1 );

  while (window.isOpen())
  {
    auto startTimePoint = std::chrono::high_resolution_clock::now();
    auto endTimePoint   = startTimePoint + frameDurationMs;

    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    Simulation::GetInstance().simulateOneStep();
    window.clear();
    Simulation::GetInstance().draw( window );
    window.display();
    
    auto now = std::chrono::high_resolution_clock::now();
    if ( now < endTimePoint )
    {
      std::this_thread::sleep_until( endTimePoint );
    }
    ++frameCount;
    if ( std::chrono::high_resolution_clock::now() > secondEnd )
    {
      std::cout << frameCount << std::endl;
      frameCount = 0;
      secondEnd = std::chrono::high_resolution_clock::now() + std::chrono::seconds( 1 );
    }
  }

  Simulation::TerminateInstance();
  Global::TerminateInstance();
  return 0;
}