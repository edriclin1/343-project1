#include "functions.h"

/**
* Functions for Game of Life. Used to print, step, load, and
* save the game universe.
* 
* @author Edric Lin
* @author Austin Maley
* @version 2/10/2018
*/

/**
* Print the current universe.
*
* @param universe the universe to print
*/
void printUniverse(UNIV* universe) {

    // row * (number of columns) + column = string position in array
    printf("\n");
    int row = 0;
    for (; row < universe -> rows; row++) {
        printf("   ");
        int col = 0;
        for (; col < universe -> cols; col++) {
            printf("[ %c ]", universe -> cells[row * universe -> cols + col]);
        }
    printf("\n");
    }
    printf("\n");
}

/**
* Load universe from file.
*
* @param universe the universe to load
*/
void loadFile(char* filename, UNIV* universe) {

    // create file pointer
    FILE* in;
    in = fopen(filename, "r");

    // error opening file
    if (in == NULL) {
        printf("> File \"%s\" could not be opened.\n", filename);
        exit(0);
    }

    // get rows and columns from file
    int rows;
    int cols;
    fscanf(in,"%d\n%d\n", &rows, &cols); //https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm

    // set universe size and create corresponding array of cells
    int size = rows * cols;
    universe -> rows = rows;
    universe -> cols = cols;
    universe -> cells = (char*) malloc (size * sizeof(char));

    //printf("    rows: %d    cols: %d\n", universe -> rows, universe -> cols);

    // read and set cell contents
    int i = 0;
    for (; i < size; i++) {
        fscanf(in, "%c\n", &(universe -> cells[i]));
        //printf("    cell %d: %c\n", i, universe -> cells[i]);
    }

    fclose(in);
}

/**
* Save universe to file.
*
* @param universe the universe to save
*/
void saveFile(char* filename, UNIV* universe) {

    // create file pointer
    FILE* out;
    out = fopen(filename, "w");

    // error opening file
    if (out == NULL) {
        printf("> File \"%s\" could not be opened.\n", filename);
        exit(0);
    }

    // write world size to file
    fprintf(out, "%d\n%d\n", universe -> rows, universe -> cols);

    // write cell contents to file
    int size = universe -> rows * universe -> cols;
    int i = 0;
    for (; i < size; i++) {
        fprintf(out, "%c\n", universe -> cells[i]);
    }

    printf("> Universe has been saved to \"%s\" file.\n", filename);
    fclose(out);
}

/**
* Count number of live neighbors of a universe position
*
* @param universe the universe being simulated
* @param pos the position in the universe array to look at
* @return number of live neighbors of position
*/
int countNeigh(UNIV* universe, int pos) {
    // neighbor count
    int neighCount = 0;

    // universe size
    int size = universe -> rows * universe -> cols;

    // array of possible neighbors
    int neigh[8];
    neigh[0] = pos - universe -> cols - 1; // up left
    neigh[1] = pos - 1; // left
    neigh[2] = pos + universe -> cols - 1; // down left
    neigh[3] = pos - universe -> cols; // up
    neigh[4] = pos + universe -> cols; // down
    neigh[5] = pos - universe -> cols + 1; // up right
    neigh[6] = pos + 1; // right
    neigh[7] = pos + universe -> cols + 1; // down right

    // check all neighbors positions if not an edge cell
    int start = 0;
    int end = 7;

    // left edge cell, dont check left neighbors
    if (pos % universe -> cols == 0) {
        start = 3;
    }

    // right edge cell, don't check right neighbors
    if (pos % universe -> cols == universe -> cols - 1) {
        end = 4;
    }

    // check neighbor content and store info
    for (; start <= end; start++) {

        // check if neighbor pos is within cells array
        if (neigh[start] >= 0 && neigh[start] < size) {

            // check if cell is alive
            if (universe -> cells[neigh[start]] == 'O') {
                neighCount++;
            }
        }
    }
    return neighCount;
}

/**
* Take one step forward in universe simulation.
*
* @param universe the universe to step
*/
void step(UNIV* universe) {

    // universe size
    int size = universe -> rows * universe -> cols;

    UNIV* temp = (UNIV*) malloc(sizeof(UNIV));
    
    // copy universe info for analysis
    temp -> rows = universe -> rows;
    temp -> cols = universe -> cols;
    temp -> cells = (char*) malloc (size * sizeof(char));
    memcpy(temp -> cells, universe -> cells, size * sizeof(char));

    //printf("%d %d %c %c\n", temp -> rows, temp -> cols, temp -> cells[0], temp -> cells[1]);

    // check each cells neighbors and change original universe accordingly
    int i = 0;
    for (; i < size; i++) {

        //printf("universe\n");
        //printUniverse(temp);

        // count live neighbors
        int neighCount = countNeigh(temp, i);
        //printf("_____num neigh %d: %d______\n", i, neighCount);

        // if cell is live
        if(temp -> cells[i] == 'O') {

            // live cells with less than 2 or more than 3 neighbors die
            if (neighCount < 2 || neighCount > 3) {
                universe -> cells[i] = 'X';
            }
        }

        // if cell is dead
        else {
        
            // dead cells with 3 live neighbors become live cells
            if (neighCount == 3) {
                universe -> cells[i] = 'O';
            }
        }
    }
    free(temp -> cells);
    free(temp);
}