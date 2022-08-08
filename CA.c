#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CA.h"

/**
 * Main function to call the menu 
 */
int main() 
{
    runMenu();
}

/**
 * This function runs the menu which contains all the main functions for the program 
 */
void runMenu() 
{
    int userChoice; //Case for the switch case
    long long binary; //Number to be processed for converting binary to decimal
    int ruleChoice; //The ruleset the user inputs
    int decimal; //Number to be processed for converting decimal to binary

    //Runs the loop until exited
    while(1)
    {
        //Displays menu options to user
        printf("1. Run a 1-d CA\n");
        printf("2. Load all previous patterns CA\n");
        printf("3. Convert from binary to decimal\n");
        printf("4. Convert decimal to binary\n");
        printf("0. Exit\n");
        printf("Enter an option from the menu:  ");
        scanf("%d",&userChoice); //Gets the users menu choice 
        
        //Switch case for menu functions
        switch(userChoice)
        {
            //Gets the user to select which ruleset they want displayed
            case 1:
                //Asks the user to enter the number for the ruleset
                printf("Rule 30\n");
                printf("Rule 54\n");
                printf("Rule 126\n");
                printf("Rule 150\n");
                printf("Rule 222\n");               
                printf("Please enter the number for the ruleset you would like to use:(e.g 30) \n");
                scanf("%d", &ruleChoice); //Gets the users rule choice

                //Displays rule 30
                if(ruleChoice == 30) 
                {
                    changeRuleset(rule30);
                }
                //Displays rule 54
                else if(ruleChoice == 54)
                {
                    changeRuleset(rule54);
                }
                //Displays rule 126
                else if(ruleChoice == 126)
                {
                    changeRuleset(rule126);
                }
                //Displays rule 150
                else if(ruleChoice == 150)
                {
                    changeRuleset(rule150);
                }
                //Displays rule 222
                else if(ruleChoice == 222)
                {
                    changeRuleset(rule222);
                }
                //Displays the grid for the chosen ruleset
                runCA();
                break;

            //Load the pattern that was saved to a text file
            case 2:
                loadPattern();
                break;
                
            //Converts a binary number to a decimal
            case 3:
                printf("Enter a binary number to convert to decimal:  ");
                scanf("%lld",&binary); //Gets the number the user enters
                long long convertBinary = binaryToDecimal(binary); //Converts number
                printf("Here is the converted number %lld\n", convertBinary);
                break;
            //Converts a decimal into a binary number
            case 4:
                printf("Enter a decimal number to convert to binary:  ");
                scanf("%d",&decimal); //Gets the number the user enters
                int convertDecimal = decimalToBinary(decimal); //Converts number
                printf("Here is the converted number %d\n", convertDecimal);
                break;
            //Exits program
            case 0:
                exit(0);
        }
    }
}



/**
 * This function calls all the necessary functions that enables the grid to display
 */
void runCA() 
{
    //Allocate memory to grid
    Grid *grid = (Grid*)malloc(sizeof(Grid));

    initialiseGrid(grid);
    displayNewGeneration(grid);

    for(int i = 0; i < 50; i++) 
    {
        calcNextCell(grid);
        displayNewGeneration(grid);
    }
    printf("Your CA has been saved to previousPattern.txt\n"); //Messsage to say it's been saved to file
    free(grid); //Free grid memory
}
/**
 * Initialises the grid to have a 1 in the middle of the first line
 * That is the default grid for Wolfram
 */
void initialiseGrid(Grid *grid) 
{
    //Simplest possible implementation
    for(int i = 0; i<SIZE; i++) 
    {
        grid->parent[i] = 0;
    }
    //Setting the mid value to be 1
    int mid = SIZE/2;
    grid->parent[mid]=1;
}

//Changes the 0's and 1's to be + and -
void displayNewGeneration(Grid *grid) 
{
    for(int i = 0; i < SIZE; i++)
    {
        if(grid->parent[i] == 0) printf("+");
        if(grid->parent[i] == 1) printf("-");
    }
    //Automatically saves the grid to text file
    savePattern(grid);
    printf("\n");
}

/**
 *  Calculates what the next generation will be
 */
void calcNextCell(Grid *grid) 
{
    //Allocating memory for a cell
    Cell *cell = (Cell*)malloc(sizeof(Cell));

    //Checking all cells in the array and its neigbours to be calculated
    for(int i = 0; i<SIZE; i++) 
    {
        cell->right = grid->parent[i+1]; //Sets right neighbour
        cell->left = grid->parent[i-1]; //Sets left neighbour
        cell->current = grid->parent[i]; //Sets current

        grid->child[i] = returnNextCell(cell); //Calls the function to get next generation 
    }

    //Sets the current generation to the next generation
    for(int i = 0; i < SIZE; i++) 
    {
        grid->parent[i] = grid->child[i];
    }
    //Free cell memory
    free(cell);
}

/**
 * Returns what the next cell is
 */
int returnNextCell(Cell *cell) 
{
    if (cell->right == 1 && cell->left == 1 && cell->current == 1)
        return rules[0]; //Returning value depending on neighbours
    if (cell->right == 1 && cell->left == 1 && cell->current == 0)
        return rules[1]; //Returning value depending on neighbours
    if (cell->right == 1 && cell->left == 0 && cell->current == 1)
        return rules[2]; //Returning value depending on neighbours
    if (cell->right == 1 && cell->left == 0 && cell->current == 0)
        return rules[3]; //Returning value depending on neighbours
    if (cell->right == 0 && cell->left == 1 && cell->current == 1)
        return rules[4]; //Returning value depending on neighbours
    if (cell->right == 0 && cell->left == 1 && cell->current == 0)
        return rules[5]; //Returning value depending on neighbours
    if (cell->right == 0 && cell->left == 0 && cell->current == 1)
        return rules[6]; //Returning value depending on neighbours
    if (cell->right == 0 && cell->left == 0 && cell->current == 0)
        return rules[7]; //Returning value depending on neighbours
}

/**
 * Converts character array to integers
 * https://stackoverflow.com/questions/5796874/convert-array-of-characters-to-array-of-integers-in-c
 * Used stackoverflow to find out how to do it
 */
void changeRuleset(char ruleset[]) 
{
    for(int i = 0; i < 8; i++) 
    {
        rules[i] = ruleset[i]-'0';
    }
}

/**
* Function is called when the pattern is displayed and saves it to file automatically
*/
void savePattern (Grid *grid) 
{
     FILE *fp;
     fp = fopen("previousPattern.txt", "a");

    for(int i = 0; i < SIZE; i++)
    {
        if(grid->parent[i] == 0) fprintf(fp,"+");
        else if(grid->parent[i] == 1) fprintf(fp, "-");
    }
    fprintf(fp, "\n");
    fclose(fp);
}


/**
 * Loads a previously saved 'pattern' saved as previousPattern.txt
*/
void loadPattern ()
{
    FILE *fp;
    fp = fopen("previousPattern.txt", "r");

    char array[256];  
    while(fgets(array, 256,fp) != NULL)
    {
        printf("%s", array);
    }
    fclose(fp);
}

/**
 * Converting binary numbers into decimal and returns it
 */
int binaryToDecimal (long long n)
{    
    long r = 0;
    long d = 0;
    long i = 1;
    
    while (n != 0)
    {
        r = n % 10;
        d = d + r * i;
        i = i * 2;
        n = n/10;
    }
    return d;
}

/**
 * Converting decimal numbers into binary and returning the result
 */
long long decimalToBinary (int d)
{    
    long n = 0;
    long r = 0;
    long i = 1;
    
    while (d != 0)
    {
        r = d % 2;
        n = n + r * i;
        i = i * 10;
        d = d/2;
    }

    return n;
}


