#ifndef MAP_H
#define MAP_H

char **generateMap(int mapDimensions[]);
void wipeMap(char **map, int mapDimensions[]);
void layMap(char **map, int mapDimensions[]);
void insertAntStartingPos(char **map, int ant1Position[], int ant2Position[], 
char _ant1, char _ant2);
void printMap(char **map, int **map2, int mapDimensions[], int ant1Position[], 
int ant2Position[]);
#endif