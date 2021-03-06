#include "map.h"
#include "errorMessage.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>

/*-----------------------Initiate--------------------------*/

Map *newMap(int size)
{
  Map *map = (Map *)calloc(1, sizeof(Map));

  if (map == NULL)
    errorMessageMem("newMap");

  map->mapSize = size;

  map->board = newBiCell(size);

  map->ship = initiateShip(size);

  return map;
}

Cell *newCell(int size)
{
  Cell *arr = (Cell *)calloc(size, sizeof(Cell));

  if (arr == NULL)
    errorMessageMem("newCell");

  for (int i = 0; i < size; i++)
  {
    arr[i].bit = '0';
    arr[i].shot = '0';
  }

  return arr;
}

Cell **newBiCell(int size)
{
  Cell **biArr = (Cell **)calloc(size, sizeof(Cell *));

  if (biArr == NULL)
    errorMessageMem("newBiCell");

  for (int i = 0; i < size; i++)
    biArr[i] = newCell(size);

  return biArr;
}

/*----------------------Check if lost--------------------------*/
int lost(Map *map)
{
  return someActiveShip(map->ship) ? 0 : 1;
}

/*----------------------Free-----------------------------------*/
void freeMap(Map *map)
{
  if (map == NULL)
    return;

  for (int i = 0; i < map->mapSize; i++)
  {
    free(map->board[i]);
    map->board[i] = NULL;
  }

  free(map->board);
  map->board = NULL;

  freeShip(map->ship);
  map->ship = NULL;

  free(map);
}
