#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "mazeGenerator.h"


typedef struct Cell {
  int i;
  int j;
} Cell;

const int maxCell = CELLSZ*CELLSZ;
List * l;

double dist(Cell * c, Cell * o) {
  int pi = c->i - o->i;
  int pj = c->j - o->j;
  pi *= pi; pj *= pj;
  return sqrt(pi+pj);
}

// seleccionamos el lado de entrada
Cell pickEntry(int * sp) {
  Cell entry;
  switch(*sp=(random() % 4)) {
    case NORTH: //north
      entry.i = 1;
      entry.j = random() % (CELLSZ-2);
      if (entry.j <= 1) entry.j = 2;
      break;
    case SOUTH: // south
      entry.i = CELLSZ - 2;
      entry.j = random() % (CELLSZ-2);
      if (entry.j <= 1) entry.j = 2;
      break;
    case EAST: // east
      entry.i = random() % (CELLSZ-2);
      entry.j = CELLSZ - 2;
      if (entry.i <= 1) entry.i = 2;
      break;
    case WEST: // west
      entry.i = random() % (CELLSZ-2);
      entry.j = 1;
      if (entry.i <= 0) entry.i = 2;
      break;
  }
  return entry;
}

// seleccionamos la salida del laberinto en el lado opuesto a la entrada
Cell pickExit(int maze[CELLSZ][CELLSZ], Cell * entry, int startPoint) {
  int i, j;
  double d;
  double dM = 0;
  Cell exit;
  Cell cell;
  
  switch (startPoint) {
    case NORTH:
      i = CELLSZ - 1;
      cell.i = i;
      exit.i = i;
      for (j=0; j<CELLSZ; j++) {
        cell.j = j;
        d = dist(entry, &cell);
        if (d > dM && maze[i-1][j] == CELL) {
          exit.j = j;
          dM = d;
        }
      }
      break;
    case SOUTH:
      i = 0;
      cell.i = i;
      exit.i = i;
      for (j=0; j<CELLSZ; j++) {
        cell.j = j;
        d = dist(entry, &cell);
        if (d > dM && maze[i+1][j] == CELL) {
          exit.j = j;
          dM = d;
        }
      }
      break;
    case EAST:
      j = 0;
      cell.j = j;
      exit.j = j;
      for (i=0; i<CELLSZ; i++) {
        cell.i = i;
        d = dist(entry, &cell);
        if (d > dM && maze[i][j+1] == CELL) {
          exit.i = i;
          dM = d;
        }
      }
      break;
    case WEST:
      j = CELLSZ - 1;
      cell.j = j;
      exit.j = j;
      for (i=0; i<CELLSZ; i++) {
        cell.i = i;
        d = dist(entry, &cell);
        if (d > dM && maze[i][j-1] == CELL) {
          exit.i = i;
          dM = d;
        }
      }
      break;
  }
  return exit;
}

void addNeighbourgs(List * l, Cell * c, int maze[CELLSZ][CELLSZ]) {
  const int i = c->i;
  const int j = c->j;
  if (j > 2 && maze[i][j-2] == WALL) {
    L_append(&l, i, j-2);
    maze[i][j-1] = CELL;
    maze[i][j-2] = APPENDED;
  } else if (j > 1 && maze[i][j-2] == WALL) {
    maze[i][j-1] = CELL;
  }
  
  if (j < (CELLSZ-3) && maze[i][j+2] == WALL) {
    L_append(&l, i, j+2);
    maze[i][j+1] = CELL;
    maze[i][j+2] = APPENDED;
  } else if(j < (CELLSZ-2) && maze[i][j+2] == WALL){
    maze[i][j+1] = CELL;
  }

  if (i > 2 && maze[i-2][j] == WALL) {
    L_append(&l, i-2, j);
    maze[i-1][j] = CELL;
    maze[i-2][j] = APPENDED;
  } else if (i > 1 && maze[i-2][j] == WALL) {
    maze[i-1][j] = CELL;
  }
  
  if (i < (CELLSZ-3) && maze[i+2][j] == WALL) {
    L_append(&l, i+2, j);
    maze[i+1][j] = CELL;
    maze[i+2][j] = APPENDED;
  } else if(i < (CELLSZ-2) && maze[i+2][j] == WALL){
    maze[i+1][j] = CELL;
  }
}

void printMaze(int maze[CELLSZ][CELLSZ]) {
  int i;
  int j;
  int c;
  printf("\n----------\n");
  for (i = 0; i<CELLSZ; i++) {
    for (j = 0; j<CELLSZ; j++) {
      c = maze[i][j];
      if(c > CELL) {
        if (c < 0) {
          printf("%c ",(48+c));
        } else {
          printf("%d ", c);
        }
      }
      else printf("  ");
    }
    printf("\n");
  }
  printf("\n----------\n");
}


void generateMaze(int maze[CELLSZ][CELLSZ], int * sci, int * scj) {
  int i,j;
  int sp;

  Cell cell;
  
  L_create(&l, maxCell);

  // cols
  for (i = 0; i<CELLSZ; i++) {
    // rows
    for (j = 0; j<CELLSZ; j++) {
      maze[i][j] = WALL;
    }
  }

  srandom(time(NULL));
 
  Cell scell;
  scell = pickEntry(&sp);
  *sci = scell.i; *scj = scell.j;
  maze[scell.i][scell.j] = SCELL;
  cell = scell;

  addNeighbourgs(l, &cell, maze);

  while (!L_isEmpty(l)) {
    L_chooseRandom(&l, &cell.i, &cell.j);
    if (maze[cell.i][cell.j] == APPENDED) { 
      maze[cell.i][cell.j] = CELL;
      addNeighbourgs(l, &cell, maze);
    }
    L_remove(&l, cell.i, cell.j);
  }

  Cell ecell;
  ecell = pickExit(maze, &scell, sp);
  maze[ecell.i][ecell.j] = ECELL;

  L_destroy(l);
}
