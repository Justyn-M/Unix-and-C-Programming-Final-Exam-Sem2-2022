#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "color.h"
#include "random.h"
#include "macros.h"
#include "newSleep.h"

int main(int argc, char *argv[])
{
    int mapDimensions[2];
    int ant1Position[2];
    int ant2Position[2];
    char **map;
    int **map2;
    /* declaring file io variables */
    FILE *fp;
    char _ant1;
    char _ant2;
    int i;
    int j;
    /* randomNumber for moving ant2 randomly */
    int randomNum;
    /* declaring variables that use command line arguments*/
    int steps = atoi(argv[2]);
    float sec = atof(argv[3]);

    initRandom();
    /* Must have only 4 command line arguments */
    if (argc != 4)
    {
        printf("Input : %s <file_name> <steps_amount> <sleep_length>\n", argv[0]);
        return 1;
    }
    /* Steps cannot be a negative number */
    else if (steps < 0)
    {
        printf("Steps amount cannot be a negative number \n");
        return 1;
    }
    /* Sleep Seconds cannot be a negative number */
    else if (sec < 0)
    {
        printf("Seconds cannot be a negative number\n");
        return 1;
    }
    /* 2 ants cannot start on same position */
    if (ant1Position[MAP_ROW] == ant2Position[MAP_ROW] && ant1Position[MAP_COL] == ant2Position[MAP_COL])
    {
        printf("Ants cannot be in the same position\n");
        return 1;
    }
    /* Open file, check if command line argument 1 is a valid filename */
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    /* Read the file and store the values in the mapDimensions array */
    fscanf(fp, "%d %d", &mapDimensions[MAP_ROW], &mapDimensions[MAP_COL]);
    fscanf(fp, "%d %d %c", &ant1Position[MAP_ROW], &ant1Position[MAP_COL], &_ant1);
    fscanf(fp, "%d %d %c", &ant2Position[MAP_ROW], &ant2Position[MAP_COL], &_ant2);
    /* generate map2 */
    map2 = malloc(mapDimensions[MAP_ROW] * sizeof(int *));
    for (i = 0; i < mapDimensions[MAP_ROW]; i++)
    {
        map2[i] = malloc(mapDimensions[MAP_COL] * sizeof(int));
    }
    for (i = 0; i < mapDimensions[MAP_ROW]; i++)
    {
        for (j = 0; j < mapDimensions[MAP_COL]; j++)
        {
            fscanf(fp, "%d", &map2[i][j]);
        }
    }
    fclose(fp);

    /* initial screen when simulation first starts */
    map = generateMap(mapDimensions);
    system("clear");
    layMap(map, mapDimensions);
    insertAntStartingPos(map, ant1Position, ant2Position, _ant1, _ant2);
    printMap(map, map2, mapDimensions, ant1Position, ant2Position);
    newSleep(sec);

    /* ===== langton's ant simulation ===== */
    /* Below code is very repetitive because the simulation rules have been placed
    inside main file.
    I have tried to make a dedicated function for the rules, but it results
    in the simulation running with the ants only moving left and right

    If a rules function gives no issues, it should be used because it will
    drastically reduce the lines of code in the main file. */
    for (i = 0; i < steps; i++)
    {
        /* ======= Rules for if ant is on neutral ======= */
        if ((_ant1 == MARKER_ANT_UP) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 0)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 2;
            ant1Position[MAP_COL]++;
            _ant1 = MARKER_ANT_RIGHT;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            /* delete the previous position of _ant1 */
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL] - 1] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_RIGHT) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 0)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 2;
            ant1Position[MAP_ROW]++;
            _ant1 = MARKER_ANT_DOWN;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW] - 1][ant1Position[MAP_COL]] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_DOWN) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 0)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 2;
            ant1Position[MAP_COL]--;
            _ant1 = MARKER_ANT_LEFT;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL] + 1] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_LEFT) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 0)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 2;
            ant1Position[MAP_ROW]--;
            _ant1 = MARKER_ANT_UP;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW] + 1][ant1Position[MAP_COL]] = ' ';
        }
        /* =============== Rules for if ant is on green ================== */
        else if ((_ant1 == MARKER_ANT_UP) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 1)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 0;
            ant1Position[MAP_COL]--;
            _ant1 = MARKER_ANT_LEFT;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL] + 1] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_LEFT) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 1)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 0;
            ant1Position[MAP_ROW]++;
            _ant1 = MARKER_ANT_DOWN;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW] - 1][ant1Position[MAP_COL]] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_DOWN) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 1)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 0;
            ant1Position[MAP_COL]++;
            _ant1 = MARKER_ANT_RIGHT;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL] - 1] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_RIGHT) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 1)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 0;
            ant1Position[MAP_ROW]--;
            _ant1 = MARKER_ANT_UP;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW] + 1][ant1Position[MAP_COL]] = ' ';
        }
        /* =============== Rules for if ant is on red ================== */
        else if ((_ant1 == MARKER_ANT_UP) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 2)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 0;
            ant1Position[MAP_COL]--;
            _ant1 = MARKER_ANT_LEFT;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL] + 1] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_LEFT) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 2)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 0;
            ant1Position[MAP_ROW]++;
            _ant1 = MARKER_ANT_DOWN;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW] - 1][ant1Position[MAP_COL]] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_DOWN) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 2)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 0;
            ant1Position[MAP_COL]++;
            _ant1 = MARKER_ANT_RIGHT;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL] - 1] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_RIGHT) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 2)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 0;
            ant1Position[MAP_ROW]--;
            _ant1 = MARKER_ANT_UP;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW] + 1][ant1Position[MAP_COL]] = ' ';
        }
        /* =============== Rules for if ant is on blue ================== */
        else if ((_ant1 == MARKER_ANT_UP) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 3)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 2;
            ant1Position[MAP_COL]++;
            _ant1 = MARKER_ANT_RIGHT;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL] - 1] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_RIGHT) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 3)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 2;
            ant1Position[MAP_ROW]++;
            _ant1 = MARKER_ANT_DOWN;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW] - 1][ant1Position[MAP_COL]] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_DOWN) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 3)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 2;
            ant1Position[MAP_COL]--;
            _ant1 = MARKER_ANT_LEFT;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL] + 1] = ' ';
        }
        else if ((_ant1 == MARKER_ANT_LEFT) && map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] == 3)
        {
            map2[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = 2;
            ant1Position[MAP_ROW]--;
            _ant1 = MARKER_ANT_UP;
            map[ant1Position[MAP_ROW]][ant1Position[MAP_COL]] = _ant1;
            map[ant1Position[MAP_ROW] + 1][ant1Position[MAP_COL]] = ' ';
        }
        /* ============= Langton's Ant (Ant 1) Animation Completed ============ */

        /* ============= Random Ant (Ant 2) Animation Started ============ */

        /* Ant moves unpredictably/randomly based on the number rolled by the
        random function */
        randomNum = random(1, 4);
        /* ============== Rules for ant 2 if on neutral cell ============ */
        if ((randomNum == 1) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 0)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 3;
            ant2Position[MAP_COL]++;
            _ant2 = MARKER_ANT_RIGHT;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL] - 1] = ' ';
        }
        else if ((randomNum == 2) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 0)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 3;
            ant2Position[MAP_ROW]++;
            _ant2 = MARKER_ANT_DOWN;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW] - 1][ant2Position[MAP_COL]] = ' ';
        }
        else if ((randomNum == 3) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 0)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 3;
            ant2Position[MAP_COL]--;
            _ant2 = MARKER_ANT_LEFT;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL] + 1] = ' ';
        }
        else if ((randomNum == 4) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 0)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 3;
            ant2Position[MAP_ROW]--;
            _ant2 = MARKER_ANT_UP;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW] + 1][ant2Position[MAP_COL]] = ' ';
        }
        /* =============== Rules for if ant2 is on green ================== */
        else if ((randomNum == 1) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 1)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 0;
            ant2Position[MAP_COL]++;
            _ant2 = MARKER_ANT_RIGHT;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL] - 1] = ' ';
        }
        else if ((randomNum == 2) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 1)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 0;
            ant2Position[MAP_ROW]++;
            _ant2 = MARKER_ANT_DOWN;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW] - 1][ant2Position[MAP_COL]] = ' ';
        }
        else if ((randomNum == 3) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 1)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 0;
            ant2Position[MAP_COL]--;
            _ant2 = MARKER_ANT_LEFT;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL] + 1] = ' ';
        }
        else if ((randomNum == 4) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 1)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 0;
            ant2Position[MAP_ROW]--;
            _ant2 = MARKER_ANT_UP;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW] + 1][ant2Position[MAP_COL]] = ' ';
        }
        /* =============== Rules for if ant2 is on red ================== */
        else if ((randomNum == 1) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 2)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 3;
            ant2Position[MAP_COL]++;
            _ant2 = MARKER_ANT_RIGHT;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL] - 1] = ' ';
        }
        else if ((randomNum == 2) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 2)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 3;
            ant2Position[MAP_ROW]++;
            _ant2 = MARKER_ANT_DOWN;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW] - 1][ant2Position[MAP_COL]] = ' ';
        }
        else if ((randomNum == 3) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 2)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 3;
            ant2Position[MAP_COL]--;
            _ant2 = MARKER_ANT_LEFT;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL] + 1] = ' ';
        }
        else if ((randomNum == 4) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 2)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 3;
            ant2Position[MAP_ROW]--;
            _ant2 = MARKER_ANT_UP;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW] + 1][ant2Position[MAP_COL]] = ' ';
        }
        /* =============== Rules for if ant2 is on blue ================== */
        else if ((randomNum == 1) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 3)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 0;
            ant2Position[MAP_COL]++;
            _ant2 = MARKER_ANT_RIGHT;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL] - 1] = ' ';
        }
        else if ((randomNum == 2) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 3)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 0;
            ant2Position[MAP_ROW]++;
            _ant2 = MARKER_ANT_DOWN;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW] - 1][ant2Position[MAP_COL]] = ' ';
        }
        else if ((randomNum == 3) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 3)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 0;
            ant2Position[MAP_COL]--;
            _ant2 = MARKER_ANT_LEFT;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL] + 1] = ' ';
        }
        else if ((randomNum == 4) && map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] == 3)
        {
            map2[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = 0;
            ant2Position[MAP_ROW]--;
            _ant2 = MARKER_ANT_UP;
            map[ant2Position[MAP_ROW]][ant2Position[MAP_COL]] = _ant2;
            map[ant2Position[MAP_ROW] + 1][ant2Position[MAP_COL]] = ' ';
        }
        /* Clear screen, print map, and sleep simulation upon each movement */
        system("clear");
        printMap(map, map2, mapDimensions, ant1Position, ant2Position);
        newSleep(sec);
    }
    /* free memory */
    free(map);
    free(map2);

    return 0;
}