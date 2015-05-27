#include <stdio.h>
#include "mazeGenerator.h"

int main() {
  int maze[CELLSZ][CELLSZ];
  int sci, scj;

  generateMaze(maze, &sci, &scj);

  printf("Starting cell = {%d,%d}\n", sci, scj);
  printMaze(maze);
  return 0;
}
