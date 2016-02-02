/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#include "precomp.h"

#include "Simulation.h"
#include "Ship.h"
#include "ShipStiff.h"
#include "ShipSpace.h"

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
  mShip.reset( new ShipSpace() );
}


void
Simulation::simulateOneStep()
{
  if ( mShip )
    mShip->update();
}


void
Simulation::draw( sf::RenderTarget& aRenderTarget )
{
  mShip->draw( aRenderTarget );
}
