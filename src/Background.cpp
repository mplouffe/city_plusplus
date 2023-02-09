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
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT]->loadFromFile("../assets/img/city.png", aRenderer))
	{
		SDL_Log("Failed to load DEFAULT image.\n");
		success = false;
	}

	// Load Up surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_UP]->loadFromFile("../assets/img/sky.png", aRenderer))
	{
		SDL_Log("Failed to load UP image.\n");
		success = false;
	}

	// Load DOWN surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_DOWN]->loadFromFile("../assets/img/infrastructure.png", aRenderer))
	{
		SDL_Log("Failed to load DOWN image.\n");
		success = false;
	}

	// Load LEFT surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_LEFT]->loadFromFile("../assets/img/industrial.png", aRenderer))
	{
		SDL_Log("Failed to load LEFT image.\n");
		success = false;
	}

	// Load RIGHT surface
	if (!mKeyPressTextures[KEY_PRESS_SURFACE_RIGHT]->loadFromFile("../assets/img/residental.png", aRenderer))
	{
		SDL_Log("Failed to load RIGHT image.\n");
		success = false;
	}

	return success;
}

void Background::setBackground(KeyPressSurfaces newBackground)
{
    mCurrentBackground = mKeyPressTextures[newBackground];
}

void Background::triggerCrossFade(KeyPressSurfaces newBackground, int fadeDuration)
{
	if (mCurrentBackground != mKeyPressTextures[newBackground])
	{
		if (mIsCrossFading)
		{
			mTransitioningBackground->setAlpha(255);
			mTransitioningBackground->setBlendMode(SDL_BLENDMODE_NONE);
		}
		mTargetFadeDuration = fadeDuration;
		mTransitioningBackground = mCurrentBackground;
		mTransitioningBackground->setBlendMode(SDL_BLENDMODE_BLEND);
		mCurrentBackground = mKeyPressTextures[newBackground];
		mIsCrossFading = true;
		mCurrentFadeDuration = 0;
	}
}

void Background::render()
{
    mCurrentBackground->render(0, 0);
	if(mIsCrossFading)
	{
		mTransitioningBackground->render(0, 0);
	}
}

void Background::update()
{
	if (mIsCrossFading)
	{
		mCurrentFadeDuration++;
		if (mCurrentFadeDuration >= mTargetFadeDuration)
		{
			mIsCrossFading = false;
			mTransitioningBackground->setAlpha(255);
			mTransitioningBackground->setBlendMode(SDL_BLENDMODE_NONE);
			mTransitioningBackground = NULL;
		}
		else
		{
			float percentComplete = (float)mCurrentFadeDuration/(float)mTargetFadeDuration;
			int currentFadeAlpha = (1 - percentComplete) * 255;
			mTransitioningBackground->setAlpha(currentFadeAlpha);
		}
	}
}