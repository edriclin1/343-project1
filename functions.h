#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

/**
* Header file for Game of Life.
* 
* @author Edric Lin
* @author Austin Maley
* @version 2/10/2018
*/

/** struct representing the universe as an array. stores array size. */
struct universe {
    char* cells;
    int rows;
    int cols;
};
typedef struct universe UNIV;

/**
* Print the current universe.
*
* @param universe the universe to print
*/
void printUniverse(UNIV* universe);

/**
* Load universe from file.
*
* @param universe the universe to load
*/
void loadFile(char* filename, UNIV* universe);

/**
* Save universe to file.
*
* @param universe the universe to save
*/
void saveFile(char* filename, UNIV* universe);

/**
* Count number of live neighbors of a universe position
*
* @param universe the universe being simulated
* @param pos the position in the universe array to look at
* @return number of live neighbors of position
*/
int countNeigh(UNIV* universe, int pos);

/**
* Take one step forward in universe simulation.
*
* @param universe the universe to step
*/
void step(UNIV* universe);