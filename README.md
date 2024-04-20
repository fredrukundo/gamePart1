# gamePart1
it's time for building something fun.

## what to know

- The W, A, S, and D keys must allow you to move the point of view through the maze.
- Pressing ESC must close the window and quit the program cleanly.
- The map may not be rectangular, but it must be surrounded by walls
- Spaces are allowed but the player cannot walk on them, thus every space must also be closed/surrounded by walls
- There must be a single player on the map

## how to compile

```bash
gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit libft/src/*.c src/*.c -o output
./output maps/1.cub
