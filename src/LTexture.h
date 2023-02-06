#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path, SDL_Renderer* renderer);
        bool loadFromRenderedText(std::string aTextureText, SDL_Color aTextColor, SDL_Renderer* aRenderer, TTF_Font* aFont);
        void free();
        // void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 newAlpha);
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