#include "Background.h"

Background::Background()
{
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
    {
        mKeyPressTextures[i] = new LTexture();
    }
}

Background::~Background()
{ }

void Background::close()
{
    for (int i = 0; i< KEY_PRESS_SURFACE_TOTAL; i++)
	{
        mKeyPressTextures[i]->~LTexture();
        mKeyPressTextures[i] = NULL;
	}
}

bool Background::init(SDL_Renderer* aRenderer)
{
	// Loading success flag
	bool success = true;

	// Load default surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT]->loadFromFile("../img/city.png", aRenderer))
	{
		printf("Failed to load DEFAULT image.\n");
		success = false;
	}

	// Load Up surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_UP]->loadFromFile("../img/sky.png", aRenderer))
	{
		printf("Failed to load UP image.\n");
		success = false;
	}

	// Load DOWN surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_DOWN]->loadFromFile("../img/infrastructure.png", aRenderer))
	{
		printf("Failed to load DOWN image.\n");
		success = false;
	}

	// Load LEFT surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_LEFT]->loadFromFile("../img/industrial.png", aRenderer))
	{
		printf("Failed to load LEFT image.\n");
		success = false;
	}

	// Load RIGHT surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_RIGHT]->loadFromFile("../img/residental.png", aRenderer))
	{
		printf("Failed to load RIGHT image.\n");
		success = false;
	}

	return success;
}

void Background::setBackground(KeyPressSurfaces newBackground)
{
    mCurrentBackground = mKeyPressTextures[newBackground];
}

void Background::render(SDL_Renderer* aRenderer)
{
    mCurrentBackground->render(0, 0);
}

void Background::update()
{

}