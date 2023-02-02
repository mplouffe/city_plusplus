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
        void render(int x, int y, SDL_Rect* clip = NULL);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;
        SDL_Renderer* mRenderer;
        int mWidth;
        int mHeight;
};
#endif