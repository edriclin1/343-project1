#include "functions.h"

int main(int argc, char** argv) {

    // if not 2 arguments, error
    if (argc != 2) {
        printf("> Usage: ./prog_name universe_file\n");
        exit(1);
    }

    printf("--------------------------\n");
    printf("    1: Step forward\n");
    printf("    2: Load from file\n");
    printf("    3: Save to file\n");
    printf("    0: Exit\n");
    printf("--------------------------\n");
    
    // initialize universe pointer
    UNIV* universe = (UNIV*) malloc(sizeof(UNIV));

    // open file and print universe
    loadFile(argv[1], universe);
    printUniverse(universe);

    // continue prompting unless user enters 0
    int command = -1;
    char* filename = (char*) malloc(255 * sizeof(char));
    while (command != 0) {
        printf("> Enter a number command 1-3 or 0 to exit: ");
        scanf("%d", &command);

        switch (command) {

            // step forward in simulation if command 1
            case 1:
                step(universe);
                printUniverse(universe);
                break;

            // load universe from file if command 2
            case 2:
                printf("> Enter filename: ");
                scanf("%s", filename);
                printf("%s\n", argv[1]);
                loadFile(filename, universe);
                
                printUniverse(universe);
                break;

            // save universe to file if command 3
            case 3:
                printf("> Enter filename: ");
                scanf("%s", filename);
                saveFile(filename, universe);
                break;

            // exit simulation if command 0
            case 0:
                printf("> Exiting simulation.\n");
                free(universe -> cells);
                return 0;
                
            // invalid command
            default:
                printf("> Invalid command entered.\n");
                break;
        }
    printf("--------------------------\n");
    printf("    1: Step forward\n");
    printf("    2: Load from file\n");
    printf("    3: Save to file\n");
    printf("    0: Exit\n");
    printf("--------------------------\n");
    }
}