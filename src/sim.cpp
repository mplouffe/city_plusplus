#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

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
LTexture gCurrentTexture;
LTexture gPlaneTexture;
LTexture gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];

LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    // Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    // get rid of pre-existing texture
    free();

    // the final texture
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
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
    return mTexture != NULL;
}

void LTexture::free()
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

void LTexture::render(int x, int y)
{
    // set rendering pspace and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

// Declarations
bool init();									// starts up SDL and creates window
bool loadMedia();								// load media
void close();									// frees media and shuts down SDL

// Defintions
bool init()
{
	// Initialzation flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("City++: Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initalize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load default surface
	if (!gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT].loadFromFile("../img/city.png"))
	{
		printf("Failed to load DEFAULT image.\n");
		success = false;
	}

	// Load Up surface
	if (!gKeyPressTextures[KEY_PRESS_SURFACE_UP].loadFromFile("../img/sky.png"))
	{
		printf("Failed to load UP image.\n");
		success = false;
	}

	// Load DOWN surface
	if (!gKeyPressTextures[KEY_PRESS_SURFACE_DOWN].loadFromFile("../img/infrastructure.png"))
	{
		printf("Failed to load DOWN image.\n");
		success = false;
	}

	// Load LEFT surface
	if (!gKeyPressTextures[KEY_PRESS_SURFACE_LEFT].loadFromFile("../img/industrial.png"))
	{
		printf("Failed to load LEFT image.\n");
		success = false;
	}

	// Load RIGHT surface
	if (!gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT].loadFromFile("../img/residental.png"))
	{
		printf("Failed to load RIGHT image.\n");
		success = false;
	}

	if (!gPlaneTexture.loadFromFile("../img/plane.png"))
	{
		printf("Failed to load PLANE image.\n");
		success = false;
	}

	return success;
}

void close()
{
	// Deallocate surface
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
	{
		gKeyPressTextures[i].free();
	}

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Initialize SDL
	if(!init())
	{
		printf("Failed to initialize.\n");
		// return 0;
	}

	if(!loadMedia())
	{
		printf( "Failed to load media.\n");
		// return -5;
	}

	// Keep window open until quit
	SDL_Event e;
	bool quit = false;
	int planeXPosition = -gPlaneTexture.getWidth();
	int planePositionUpdaterCounter = 0;

	gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];
	
	while(!quit)
	{ 
		while(SDL_PollEvent(&e))
		{ 
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_UP];
						break;
					case SDLK_DOWN:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DOWN];
						break;
					case SDLK_LEFT:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_LEFT];
						break;
					case SDLK_RIGHT:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT];
						break;
					case SDLK_HOME:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];
						break;
				}
			}
		}

		// Clear Screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// Render texture to screen
		gCurrentTexture.render(0, 0);
		gPlaneTexture.render(planeXPosition, 50);

		planePositionUpdaterCounter++;
		if (planePositionUpdaterCounter > 20)
		{
			planeXPosition++;
			if (planeXPosition > SCREEN_WIDTH)
			{
				planeXPosition = -gPlaneTexture.getWidth();
			}
			planePositionUpdaterCounter = 0;
		}

		// Update Screen
		SDL_RenderPresent(gRenderer);
	}
	
	close();

	return 0;
}
