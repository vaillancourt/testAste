/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#include "Simulation.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <stdlib.h>

bool Simulation::IsFromTerminate = false;
std::unique_ptr<Simulation> Simulation::Instance;

void 
Simulation::InitInstance()
{
  if ( Instance )
    std::cout << "Simulation::InitInstance() already called." << std::endl;
  else
    Instance = std::make_unique<Simulation>();
}

void 
Simulation::TerminateInstance()
{
  IsFromTerminate = true;
  Instance.reset();
}

Simulation& 
Simulation::GetInstance()
{
  return *(Instance.get());
}

Simulation::Simulation()
{
}


Simulation::~Simulation()
{
  if ( !IsFromTerminate )
    std::cout << "Kill the simulation via Simulation::TerminateInstance()" << std::endl;
}


void
Simulation::populate()
{
}


void
Simulation::simulateOneStep()
{
}


void
Simulation::draw( sf::RenderTarget& aRenderTarget )
{
}
