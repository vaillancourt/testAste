/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#pragma once

class Ship;

class Simulation
{
  Simulation(const Simulation& that) = delete;
  Simulation& operator=(const Simulation&) = delete;
public:

  static void InitInstance();
  static void TerminateInstance();
  static Simulation& GetInstance();

  void populate();

  void simulateOneStep();
  void draw( sf::RenderTarget& aRenderTarget );

  ~Simulation();
  Simulation();

private:

  std::unique_ptr<Ship> mShip;

  static std::unique_ptr<Simulation> Instance;
  static bool                        IsFromTerminate;;
};
