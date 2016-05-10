#include <SDL.h>
#include <stdio.h>

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;



bool initSDL()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Get surface window
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia()
{
	// Loading flag
	bool success = true;

	// Load splash image
	gHelloWorld = SDL_LoadBMP("Images/hello_world.bmp");
	if(gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "Images/hello_world.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	// Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

// These arguments are necessary for SDL's compatability
int main(int argc, char* args[])
{
	// Start up SDL and create window
	if (!initSDL())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// Apply the image
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

			//Update the surface
			SDL_UpdateWindowSurface(gWindow);

			// Quit flag
			bool quit = false;

			// Quit event handler
			SDL_Event e;

			// While aplication is running
			while (!quit)
			{
				// Handle events
				while(SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}