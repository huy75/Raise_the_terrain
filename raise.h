#ifndef _RAISE_H_
#define _RAISE_H_

/* ============================================ */
/* LIBRARIES */
/* ============================================ */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ============================================ */
/* STRUCTURES */
/* ============================================ */

/**
 * struct coordinates - Store graph coordinates
 * @x: x axis value
 * @y: y axis value
 * @z: z axis value
 *
 * Description: Grid 3D coordinates
 */
typedef struct coordinates
{
	float x;
	float y;
	float z;
} coord;

/**
 * struct variables - Global variables
 * @window: Windows program
 * @renderer: Render program
 * @fName: File name with coordinates
 * @array: Struct containing graph coordinates
 * @col: Graph width
 * @row: Graph height
 *
 * Description: Structure containing common variables
 * in project
 *
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
        char *fName;
	coord **array;
	int col;
	int row;
} SDL_Instance;

/* ============================================ */
/* WINDOW SIZE */
/* ============================================ */
#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 1024
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 600
#endif

/* ============================================ */
/* array.c */
/* ============================================ */
int file_to_array(SDL_Instance *instance);
void data_to_array(SDL_Instance *instance);
void free_array(SDL_Instance *instance);

/* ============================================ */
/* drawRotate.c */
/* ============================================ */
void draw_grid(SDL_Instance *instance);
void draw_stuff(SDL_Instance instance);
void rotate_grid(SDL_Instance *instance, int Angle);

/* ============================================ */
/* main.c */
/* ============================================ */
int init_instance(SDL_Instance *instance, char *av);
int poll_events(SDL_Instance *instance);
int main(int ac, char **av);

#endif
