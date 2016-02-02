/**
 * Copyright (c) 2016 Alexandre Vaillancourt. See full MIT license at the root of the repository.
 */
#pragma once

#define COLOUR_BACKGROUND 127, 255, 127

class Global
{
  Global(const Global& that) = delete;
  Global& operator=(const Global&) = delete;
public:
  static void InitInstance();
  static void TerminateInstance();
  static Global& GetInstance();

  int   getWindowWidth() const { return 512; }
  int   getWindowHeight() const { return getWindowWidth() / 4 * 3; }
  int   getFrameRateInt() const { return 120; }
  float getFrameRateFloat() const { return static_cast<float>(getFrameRateInt()); }
  float getFrameTime() const { return 1.0f / getFrameRateFloat(); }
  float getWorldWidth() const { return 1.6f; }
  float getWorldHeight() const { return getWorldWidth() / 4.0f * 3.0f; }
  float getWorldToGraphicsRatio() const { return getWindowWidth() / getWorldWidth(); }

  ~Global();
  Global();

private:
  static std::unique_ptr<Global> Instance;
  static bool                    IsFromTerminate;
};
