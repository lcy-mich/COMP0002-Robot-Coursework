# COMP0002-Robot-Coursework
Robot maze-solver/ path-finder Coursework for Principles of Programming COMP0002.

## Description
Here is a little rat 🐀, he is hungry and wants cheese 🧀.

Oh goodie 🤤, it's a bunch of markers made of cheese for him to collect, buffet-style 😋.

---

Handrolling a priority queue (implemented with a binary heap), and hashtables (with separate chaining for collision handling), our little rat friend 🐀 uses the A* path-finding algorithm with the euclidean distance between him and the closest cheese 🧀 as his heuristic and target. yum yum yum 🤩🤗!!

What? This isn't optimal? Travelling salesman problem? What are you on about?! The rat does not concern himself with optimal route planning and instead follows nearest-neighbour (not really, if you consider travelling cost rather than physical distance).

---

Map generation works by randomly placing 'seeds' which will grow the walls outwards by a certain length specified in the source-code (maploader.c) as macro definitions.

This works most of the time, however there are no checks for whether every piece of cheese is reachable/ whether the graph is connected, and so the rat will only pick up the markers within reach.

---

This program can either generate maps by itself, or accept .txt map files that follows a specific format

## Installation

Before compiling please ensure the file hierarchy looks like so:

```
./COMP0002-Robot-Coursework
├─graphics      <-- important ❗❗
│  ├─graphics.c
│  └─graphics.h
├─drawapp.4.5   <-- important ❗❗
│  └─drawapp-4.5.jar
├─src
│  ├─astar.c
│  ├─display.c
|  ├─grid.c
│  ├─main.c
│  ├─maploader.c
│  ├─robot.c
│  └─vectors.c
└─inc
   ├─astar.h
   ├─display.h
   ├─grid.h
   ├─maploader.h
   ├─robot.h
   └─vectors.h
```
To compile this program, run the following:

`gcc -o robot_maze_solver "src\main.c" "src\robot.c" "src\vectors.c" "src\display.c" "src\astar.c" "src\grid.c" "src\maploader.c" "graphics\graphics.c" -I"inc" -I"graphics"`

or alternatively for Windows users:

`compile.bat`

> It is important that the graphics library source is in its own folder like the above file tree, or alternatively you can change the above command/ batch file to include the correct path to the `graphics.c` input file and `-I"DIRECTORY\WITH\GRAPHICS_H\"` in the command.

---

After compiling, you will have a robot_maze_solver executable file available for use, that can pipe its output into the drawapp jar file to display graphics.


## Usage

To run with map generation, use the command:

`robot_maze_solver.exe | java -jar "path\to\drawapp-4.5.jar"`

##### *where `"path\to\drawapp-4.5.jar"` is the correct path to your `drawapp-4.5.jar` file.*

or alternatively for Windows users:

`run_generated_map.bat`

> Note that the batch file assumes the file hierarchy to be the same as the one shown under ***## Installation***.

---

To run by loading your own map file, use the command

`robot_maze_solver.exe "path\to\map\file.txt" | java -jar "path\to\drawapp-4.5.jar"`

---

Assuming that the file hierarchy is the same as the original, the following commands should compile and run the program on map generation mode for Windows:

```
gcc -o robot_maze_solver "src\main.c" "src\robot.c" "src\vectors.c" "src\display.c" "src\astar.c" "src\grid.c" "src\maploader.c" "graphics\graphics.c" -I"inc" -I"graphics"

robot_maze_solver.exe | java -jar drawapp.4.5\drawapp-4.5.jar
```

## Map file formatting

The map file consists of four lines of metadata, and with the rest being map data.

- The first and second line correspond to the x and y dimensions of the map.

- The third line correspond to the size of the grid when displayed.

- The fourth line correspond to the amount of cheese/ markers there are in the map.

The rest of the lines is map data.

- Map data is saved with each character corresponding to one cell in the grid.

- `#` character corresponds to a wall
- `.` character corresponds to air/ empty space
- `$` character corresponds to a marker/ cheese
- `<`, `>`, `^`, `v` characters correspond to the rat and its starting direction respectively (left, right, up, down)

Please refer to the `example_maps\` directory for map examples.


