/*
    map.c - file for map related functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "color.h"
#include "random.h"
#include "macros.h"

/* function that generates the simulation map*/
char **generateMap(int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int col = mapDimensions[MAP_COL];
    char **map = malloc(row * sizeof(char *));
    int i = 0;

    for (i = 0; i < row; i++)
        map[i] = malloc(col * sizeof(char));

    return map;
}

/* function that wipes the map and free the memory */
void wipeMap(char **map, int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int i;
    for (i = 0; i < row; i++)
    {
        free(map[i]);
        map[i] = NULL;
    }

    free(map);
    map = NULL;
}

/* function that lays the map borders */
void layMap(char **map, int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int col = mapDimensions[MAP_COL];

    int i;
    for (i = 0; i < row; i++)
    {
        if (i == 0 || i == row - 1)
        {
            memset(map[i], MARKER_BORDER, col);
        }
        else
        {
            memset(map[i], MARKER_BORDER, 1);
            memset(map[i] + 1, ' ', col - 2);
            memset(map[i] + col - 1, MARKER_BORDER, 1);
        }
    }
}

void insertAntStartingPos(char **map, int ant1Position[], int ant2Position[], char _ant1, char _ant2)
{
    map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
    map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
    /* check for starting position of ant 1*/
    if (_ant1 == MARKER_ANT_UP)
        map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = MARKER_ANT_UP;
    else if (_ant1 == MARKER_ANT_DOWN)
        map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = MARKER_ANT_DOWN;
    else if (_ant1 == MARKER_ANT_LEFT)
        map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = MARKER_ANT_LEFT;
    else if (_ant1 == MARKER_ANT_RIGHT)
        map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = MARKER_ANT_RIGHT;
    /* check for starting position for ant 2*/
    if (_ant2 == MARKER_ANT_UP)
        map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = MARKER_ANT_UP;
    else if (_ant2 == MARKER_ANT_DOWN)
        map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = MARKER_ANT_DOWN;
    else if (_ant2 == MARKER_ANT_LEFT)
        map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = MARKER_ANT_LEFT;
    else if (_ant2 == MARKER_ANT_RIGHT)
        map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = MARKER_ANT_RIGHT;
}


void printMap(char **map, int **map2, int mapDimensions[], int ant1Position[], int ant2Position[])
{
    int i, j;
    for (i = 0; i < mapDimensions[MAP_ROW]; i++)
    {
        for (j = 0; j < mapDimensions[MAP_COL]; j++)
        {
            if (map2[i][j] == 0)
            {
                printf("%c", map[i][j]);
            }
            else if (map2[i][j] == 2)
            {
                setBackground("red");
                printf(" ");
                setBackground("reset");
            }
            else if (map2[i][j] == 3)
            {
                setBackground("blue");
                printf(" ");
                setBackground("reset");
            }
            else
            {
                setBackground("green");
                printf(" ");
                setBackground("reset");
            }
        }
        printf("\n");
    }
}
