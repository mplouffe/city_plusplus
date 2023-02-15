#include <SDL_image.h>

#include "Sprite.h"

Sprite::Sprite()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Sprite::~Sprite()
{
    // Deallocate
    free();
}

ComponentType Sprite::getComponentType()
{
    return ComponentType::SPRITE;
}

bool Sprite::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    // get rid of pre-existing texture
    free();

    // the final texture
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    // return sucess
    mTexture = newTexture;
    mRenderer = renderer;
    return mTexture != NULL;
}

bool Sprite::loadFromRenderedText(std::string aTextureText, SDL_Color aTextColor, SDL_Renderer* aRenderer, TTF_Font* aFont)
{
    // Get rid of preexisting texture
    free();

    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(aFont, aTextureText.c_str(), aTextColor);
    if (textSurface == NULL)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(aRenderer, textSurface);
        if (mTexture == NULL)
        {
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    mRenderer = aRenderer;
    return mTexture != NULL;
}

void Sprite::free()
{
    // free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Sprite::setAlpha(Uint8 newAlpha)
{
    SDL_SetTextureAlphaMod(mTexture, newAlpha);
}

void Sprite::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void Sprite::render(std::tuple<int, int> position, SDL_Rect* clip)
{
    // set rendering pspace and render to screen
    int x;
    int y;
    std::tie(x, y) = position;
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(mRenderer, mTexture, clip, &renderQuad);
}

int Sprite::getWidth()
{
    return mWidth;
}

int Sprite::getHeight()
{
    return mHeight;
}