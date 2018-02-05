#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

struct universe {
    char* cells;
    int rows;
    int cols;
};
typedef struct universe UNIV;

void printUniverse(UNIV* universe);
void loadFile(char* filename, UNIV* universe);
void saveFile(char* filename, UNIV* universe);
int countNeigh(UNIV* universe, int pos);
void step(UNIV* universe);