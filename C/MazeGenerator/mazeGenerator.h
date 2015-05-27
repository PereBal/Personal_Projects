#define CELL -5
// celda de inicio
#define SCELL -4
// celda de salida
#define ECELL -3
#define APPENDED -2
#define WALL -1

// Esta variable define el tamaño del laberinto
#define CELLSZ 32

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

// genera un laberinto i lo guarda en la variable maze, sci-scj indican la posicion i,j de inicio
void generateMaze(int maze[CELLSZ][CELLSZ], int * sci, int * scj);
void printMaze(int maze[CELLSZ][CELLSZ]);
