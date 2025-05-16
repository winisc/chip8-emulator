#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "SDL.h"

typedef struct	sdl_s 
{
	SDL_Window *window;
	SDL_Renderer
} sdl_t; 

typedef struct	config_s 
{
	uint32_t window_width; //SDL Window width
	uint32_t window_height; //SDL Window height
} config_t; 

// initialize SDL
bool	init_sdl(sdl_t *sdl, const config_t config)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO |SDL_INIT_TIMER) != 0)
	{
		SDL_Log ("Could not initialize SDL subsystems! %s\n", SDL_GetError());
		return false;
	}
	sdl->window = SDL_CreateWindow("CHIP8 Emulator", SDL_WINDOWPOS_CENTERED, 
									SDL_WINDOWPOS_CENTERED, 
									config.window_width, config.window_height, 0);
	if (!sdl->window)
	{
		SDL_Log ("Could not create SDL window! %s\n", SDL_GetError());
		return false;
	}
	return true; // Success
}

// Set up initial wmulator configuration from passed in arguments
bool	set_config_from_args(config_t *config, const int argc, char **argv)
{
	int	i;

	i = 1;
	// Set defaults
	*config = (config_t)
	{
		.window_width = 64,	// CHIP8 original X resolution
		.window_height = 32,	// CHIP8 original Y resolution
	};
	// Override defaults from passed in arguments
	while (i < argc)
	{
		(void)argv[i];	// Prevent compiler error from unused variables argc/argv
		// ...
		i++;
	}
	return true;	// Success
}

// Finish cleanup
void	finish_cleanup(const sdl_t sdl)
{
	SDL_DestroyWindow(sdl.window);	// Close and destroy window
	SDL_Quit();	// Shut down SDL subsystem
}

// Da main squeeze
int	main(int argc, char **argv)
{
	// initialize emulator configs/optins
	config_t config = {0};
	if (!set_config_from_args(&config, argc, argv)) exit(EXIT_FAILURE);
	// initialize SDL
	sdl_t sdl = {0};
	if (!init_sdl(&sdl, config)) exit(EXIT_FAILURE);
	// Finish cleanup
	finish_cleanup(sdl);
	exit(EXIT_SUCCESS);
}
