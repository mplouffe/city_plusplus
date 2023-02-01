#ifndef GLOBALS_H
#define GLOBALS_H

#include "LTexture.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// Globals
// (using globals while learning and doing tutorials)
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture* gCurrentTexture = NULL;
LTexture* gPlaneTexture = NULL;
LTexture* gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];

#endif