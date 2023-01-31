#pragma once

#include <string>
#include <SDL.h>

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path);
        void free();
        void render(int x, int y);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};