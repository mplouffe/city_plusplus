#ifndef GLOBALS_H
#define GLOBALS_H

#include "LTexture.h"
#include "Background.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// Globals
// (using globals while learning and doing tutorials)
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
Background gBackground;
LTexture gCurrentTexture;
LTexture gSwappingTexture;
LTexture gPlaneTexture;
LTexture gRobotTexture;
LTexture gTextTexture;
LTexture gTextShadow;


#endif