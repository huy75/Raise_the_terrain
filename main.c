#include "raise.h"

/**
 * init_instance - Initialize General User Interface.
 * Return: 0 Success, 1 Failed.
 */
int init_instance(SDL_Instance *instance, char *av)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL. */
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/* Create the window where we will draw. */
	instance->window = SDL_CreateWindow("Raise the Terrain \\0/",
				       SDL_WINDOWPOS_CENTERED,
				       SDL_WINDOWPOS_CENTERED,
				       SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow() Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* Call SDL_CreateRenderer in order for draw calls to affect this window. */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
					   SDL_RENDERER_ACCELERATED |
					   SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer() Error: %s\n",
			SDL_GetError());
		SDL_DestroyWindow(instance->window);
		SDL_Quit();
		return (1);
	}
	instance->fName = av;
	instance->array = NULL;
	instance->row = 0;
	instance->col = 0;
	
	return (0);
}

/**
 * poll_events - Handle user inputs.
 * Return: 0 Success, 1 Failed.
 */
int poll_events(SDL_Instance *instance)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
		    key = event.key;
			switch (key.keysym.scancode)
			{
			case 0x29:
				return (1);
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				rotate_grid(instance, 2);
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				rotate_grid(instance, -2);
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				rotate_grid(instance, 1);
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				rotate_grid(instance, -1);
				break;
			default:
				break;
			}
		}
	}
	return (0);
}

/**
 * main - Visualize a 3D grid.
 * @ac: Number of arguments.
 * @av: Pointer to arguments
 * Return: 0 Success, 1 Failed.
 */
int main(int ac, char **av)
{
    SDL_Instance instance;

	if (ac != 2)
	{
		fprintf(stderr, "Usage <file> <coordinates file>\n");
		return (1);
	}
	
	if (init_instance(&instance, av[1]) != 0)
		return (1);

	if (file_to_array(&instance) != 0)
		return (1);
	
	while ("Running...")
	{
		SDL_SetRenderDrawColor(instance.renderer, 255, 0, 0, 255);
		SDL_RenderClear(instance.renderer);
		if (poll_events(&instance) == 1)
			break;

		SDL_SetRenderDrawColor(instance.renderer, 0, 255, 255, 255);
		/*
		draw_stuff(instance);
		*/
		draw_grid(&instance);
		
		SDL_RenderPresent(instance.renderer);
	}

	free_array(&instance);
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();

	return (0);
}

