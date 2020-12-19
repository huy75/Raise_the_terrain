
# RAISE THE TERRAIN
## About

Create a rotatable 3D grid from an input file using C programming language and the C graphics library SDL2.

## SDL2
In order to use the project, you need to install SDL2.
 - On Mac OS X, run `brew install sdl2`
 - If you need SDL2 for another platform, please visit [SDL installation guide](https://wiki.libsdl.org/Installation), along with [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html).

Compile your sources with:

```
`sdl2-config --cflags`
```
and link your compiled sources with:

```
`sdl2-config --libs`
```

You must include the backticks (`)!

## How it works

 - The program reads the input file which contains the altitude coordinates.
 - Creates and fills an array with full coordinates (x, y and z). z is the altitude. The array is the grid. 
 - Draws an isometric projection of the grid.
 - Rotates the grid to Right or Left, when the user presses on Right or Left arrow. The same logic applies with the Up and Down arrow keys.
 - Quits when the user presses ESC key or when clicks on window Quit button


## How to use it?

 1. Clone the repository
```
$ git clone https://github.com/huy75/Raise_the_terrain
```
 2. Compile the C files
 ```
$ cd Raise_the_terrain
$ gcc -Wall -Werror -Wextra -pedantic *.c -lm $(sdl2-config --cflags --libs) -o rtc
```
 3. Run the executable file with the provided input file. You could also use another input file. Reminder: the input file contains the altitude coordinates
```
$ ./rtc file
```
![Isometric projection](https://ibb.co/v4M3c72)
 4. Exit
 Press "Esc"

 
> Written with [StackEdit](https://stackedit.io/).
