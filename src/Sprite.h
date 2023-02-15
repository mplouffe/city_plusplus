#include "Component.h"

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Sprite : public Component
{
    public:
        Sprite();
        ~Sprite();
        ComponentType getComponentType();
        bool loadFromFile(std::string aPath, SDL_Renderer* aRenderer);
        bool loadFromRenderedText(std::string aTextureText, SDL_Color aTextColor, SDL_Renderer* aRenderer, TTF_Font* aFont);
        void free();
        // void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode aBlending);
        void setAlpha(Uint8 aNewAlpha);
        void render(std::tuple<int, int> aPosition, SDL_Rect* aClip = NULL);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture* mTexture;
        SDL_Renderer* mRenderer;
        int mWidth;
        int mHeight;
};