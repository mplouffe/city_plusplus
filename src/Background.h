#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "LTexture.h"

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

class Background
{
public:
    Background();
    ~Background();
    bool init(SDL_Renderer* aRenderer);
    void close();
    void setBackground(KeyPressSurfaces currentBackground);
    void triggerCrossFade(KeyPressSurfaces newBackground, int fadeDuration = 40);
    void update();
    void render(SDL_Renderer* aRenderer);

private:
    LTexture* mCurrentBackground;
    LTexture* mTransitioningBackground;
    LTexture* mKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];
    bool mIsCrossFading;
    int mCurrentFadeDuration;
    int mTargetFadeDuration;
};
#endif