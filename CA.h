#ifndef __CA_HEADER__ // this is a 'guard' on the header file, to prevent it's contents from
#define __CA_HEADER__ //being redefined more than once during the build process

#include <string.h>

#define SIZE 100 //Defines the size

int rules[] = {0, 0, 0, 1, 1, 1, 1, 0}; //Default ruleset
char rule30[] = {"00011110"}; //Rule 30
char rule54[] = {"00110110"}; //Rule 54
char rule126[] = {"01111110"}; //Rule 126
char rule150[] = {"10010110"}; //Rule 150
char rule222[] = {"11011110"}; //Rule 222

/**
 * Typedef for a grid. 
 * Contains a parent and a child as its two fields
 */
typedef struct grid 
{
    int parent[SIZE];
    int child[SIZE]; 
}Grid;

/**
 * Typedef for a cell. 
 * Contains a reference to the neighbours left, right and current
 */
typedef struct cell 
{
    int right;
    int left;
    int current;
}Cell;

void initialiseGrid();
void displayNewGeneration();
void calcNextCell();
void runMenu();
void displayMenu();
void runCA();
void savePattern();
void loadPattern();
void changeRuleset();
int returnNextCell();
int binaryToDecimal();
long long decimalToBinary();

#endif
