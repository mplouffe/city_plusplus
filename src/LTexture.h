#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>
#include <SDL.h>

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path, SDL_Renderer* renderer);
        void free();
        void render(int x, int y, SDL_Renderer* renderer);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};
#endif