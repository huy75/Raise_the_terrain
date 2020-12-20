#include "raise.h"

void draw_stuff(SDL_Instance instance)
{
  int i, j, x, y;
  
    SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0, 0, 0xFF);
    /*
    for (j = 0, y = 0; j < 9; j++, y+=75)
      {	
	for (i = 0, x = 0; i < 9; i++, x+=128)
	  {
	    SDL_RenderDrawPoint(instance.renderer, x, y);
       	  }
      }
    */
    for (j = 0, x = 10, y = 10; j < 9; j++, y+=70)
      {
	SDL_RenderDrawLine(instance.renderer, x, y, x+8*123, y);
      }

    for (i = 0, x = 10, y = 10; i < 9; i++, x+=123)
      {
	SDL_RenderDrawLine(instance.renderer, x, y, x, y+8*70);
      }
}

/**
 * draw_grid - Draw grid using coordinates.
 * @instance: Struct with common variables
 */
void draw_grid(SDL_Instance *instance)
{
	int i, j;
	float x, y, z;
	float xx, yy, XX, YY;
	float x_incl = 0.8, y_incl = 0.7;
	float Cx, Cy;

	Cx = SCREEN_WIDTH / 2.2;
	Cy = SCREEN_HEIGHT / 4.2;
	for (i = 0; i < instance->row; i++)
	{
	    for (j = 0; j < instance->col; j++)
		{
		    x = instance->array[i][j].x;
		    y = instance->array[i][j].y;
		    z = instance->array[i][j].z;
		    /* Convert 3D grid into 2D isometric grid */
		    xx = (x_incl * (x - y)) + Cx;
		    yy = ((1 - y_incl) * (x + y) - z) + Cy;

		    if (i < instance->row - 1)
			{
			    /* Take out next X coordinate */
			    x = instance->array[i + 1][j].x;
			    y = instance->array[i + 1][j].y;
			    z = instance->array[i + 1][j].z;
			    /* Convert 3D grid into 2D isometric grid */
			    YY = ((1 - y_incl) * (x + y) - z) + Cy;
			    XX = (x_incl * (x - y)) + Cx;
			    SDL_RenderDrawLine(instance->renderer, xx, yy, XX, YY);
			}
			if (j < instance->col - 1)
			{
			    /* Take out next Y coordinate */
			    x = instance->array[i][j + 1].x;
			    y = instance->array[i][j + 1].y;
			    z = instance->array[i][j + 1].z;
			    /* Convert 3D grid into 2D isometric grid */
			    YY = ((1 - y_incl) * (x + y) - z) + Cy;
			    XX = (x_incl * (x - y)) + Cx;
			    SDL_RenderDrawLine(instance->renderer, xx, yy, XX, YY);
			}
		}
	}
}

/**
 * rotate_grid - Rotate grid using coordinates.
 * @instance: Struct with common instanceiables
 * @Angle: Axis to move grid
 */
void rotate_grid(SDL_Instance *instance, int Angle)
{
	int i, j;
	float x, y, z, Cx, Cy;
	float a, Rx, Ry, Rz;
	int axis = 0;

	if (Angle == 2) /* Up */
	    axis = 1, a = 1 * M_PI / 180;
	else if (Angle == -2) /* Down */
	    axis = 1, a = -1 * M_PI / 180;
	else /* Axis = 0 */
	    a = Angle * M_PI / 180;
	Cx = SCREEN_WIDTH / 4;
	Cy = SCREEN_HEIGHT / 3;

	for (i = 0; i < instance->row; i++)
	    for (j = 0; j < instance->col; j++)
		{
		    if (axis == 0) /* Move left or right */
		    {
			x = instance->array[i][j].x;
			y = instance->array[i][j].y;
			Rx = (x - Cx) * cos(a) - (y - Cy) * sin(a) + Cx;
			Ry = (x - Cx) * sin(a) + (y - Cy) * cos(a) + Cy;
			instance->array[i][j].x = Rx;
			instance->array[i][j].y = Ry;
		    }
		    else /* Move up or down */
		       {
			   y = instance->array[i][j].y;
			   z = instance->array[i][j].z;
			   Ry = y * cos(a) - z * sin(a);
			   Rz = y * sin(a) + z * cos(a);
			   instance->array[i][j].y = Ry;
			   instance->array[i][j].z = Rz;
			}
		}
}
