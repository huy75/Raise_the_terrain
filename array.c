#include "raise.h"

/**
 * data_to_array - Take out file data into an array.
 * @instance: Struct with common variables.
 * Return: 0 Success, 1 Failed.
 */
void data_to_array(SDL_Instance *instance)
{
	FILE *file;
	char *buff = NULL, *token;
	size_t num = 0;
	int i, j;

	file = fopen(instance->fName, "r"); /* Assign coordinates */
	if (!file)
	{
		fprintf(stderr, "Could not open file\n");
		return;
	}
	for (i = 0; getline(&buff, &num, file) != -1; i++)
	{
		token = strtok(buff, " \n");
		for (j = 0; token; j++)
		{
			instance->array[i][j].x = (SCREEN_WIDTH / (instance->col + 8)) * (i + 1);
			instance->array[i][j].y = (SCREEN_HEIGHT / (instance->row + 2)) * (j + 1);
			instance->array[i][j].z = atof(token);
			token = strtok(NULL, " \n");
		}
	}
	free(buff);
	fclose(file);
}

/**
 * file_to_array - Take out file data into an array.
 * @instance: Struct with common variables.
 * Return: 0 Success, 1 Failed.
 */
int file_to_array(SDL_Instance *instance)
{
	FILE *file;
	char *buff = NULL, *token;
	size_t num = 0;
	int i;

	if (instance->fName == NULL)
	{
		fprintf(stderr, "Invalid file name\n");
		return (1);
	}
	file = fopen(instance->fName, "r");
	if (!file)
	{
		fprintf(stderr, "Could not open file\n");
		return (1);
	}
	/* Get number of rows & columns */
	for (; getline(&buff, &num, file) != -1; instance->row++)
	    if (instance->row == 0)
	    {
	      token = strtok(buff, " \n");
	      for (; token; instance->col++)
		  token = strtok(NULL, " \n");
	    }
	/* malloc the right number of rows */
	instance->array = malloc(sizeof(coord *) * instance->row);
	if (!instance->array)
	{
		fprintf(stderr, "Error creating malloc Row\n");
		return (1);
	}
	/* malloc the right number of columns */
	for (i = 0; i < instance->row; i++)
	{
	    instance->array[i] = malloc(sizeof(coord) * instance->col);
	    if (!instance->array[i])
		{
		  fprintf(stderr, "Error creating malloc Column\n");
		  return (1);
		}
	}
	free(buff), fclose(file), data_to_array(instance);
	return (0);
}

/**
 * free_array - Free.
 * @instance: Struct with common variables.
 * Return: 0 Success, 1 Failed.
 */
void free_array(SDL_Instance *instance)
{
	int i;

	for (i = 0; i < instance->row; i++)
	{
	    free(instance->array[i]);
	}
	free(instance->array);
}
