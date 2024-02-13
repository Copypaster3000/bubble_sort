//lineinfo.c
//Assignment one
//Drake Wheeler
//CS299

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

//Present choices to user, returns choice as an int
int menu(void)
{
    int choice = 0;

    printf("Select an option from the menu below\n");
    printf("1) Enter the name of the file you want to use");
    printf("\n2) Enter input through the terminal\n");
    printf("Menu choice as an integer: ");

    scanf("%d", &choice);
    clear_input_buffer(); //Clears input stream

    return choice;
}

//Clears input stream (use after 'scanf' because it leaves a '\n' in the input stream)
void clear_input_buffer(void)
{
    int c;
    while((c = getchar()) != '\n' && c != EOF); //Clears character from input stream one at a time until it hits newline or EOF

    return;
}

//Opens file and runs all the line processing functions if successful
int get_file(char** file_array, int* file_index)
{
    char file_name[MAX]; //To store file name gotten from user
    char line[MAX]; //Holds current line text from file

    printf("\nType in the name of the file you would like to use: ");
    fgets(file_name, MAX, stdin); //Puts user input into file_name
    printf("%s\n", file_name);

    file_name[strcspn(file_name, "\n")] = '\0'; //Removes newline character from the end of file_name

    FILE* file = fopen(file_name, "r"); //Sets file to open file
    if(file == NULL) //If error opening file, tells user
    {
        printf("\nError opening file\n");
        return 0;
    }
    printf("\nFile successfully opened\n\n");
    
    while(fgets(line, MAX, file) != NULL) //Loops through the file
    {
        line[strcspn(line, "\n")] = '\0'; //takes out the '\n' char before putting the string in file_array
        strncpy(file_array[*file_index], line, MAX); //Copies each line from file as a string into file_array
        ++(*file_index); //Increments file_index for each string added to array
    }

    return 1; //For successful opening of file and storage of file lines into file_array
}

//Checks for line to be truncated in file_array, stores warnings in output_array
void truncated_lines(char** file_array, char** output_array, int* output_index, int file_index)
{
    int i = 0;
    int k = 0;
    char warning_text[MAX];

    while(i <= file_index) //Loops for each string in file_array
    {
        while(file_array[i][k] != '\0' && k < 21) //Loops until end of string or once over 20 length
        {
            if(k >= 20) //If string is greater than 20 length
            {
                sprintf(warning_text, "*Warning* Line %d is truncated.", (i + 1)); //Creates warning for that line being truncated
                strncpy(output_array[*output_index], warning_text, MAX); //Stored created string in output array
                ++(*output_index); //Increments output_array because new string has been added
            }
            ++k; //Increments to go to next char in current string
        }
        k = 0; //Resets k for going through a new string
        ++i; //Increments i to go through next string in file_array
    }

    return;
}

//Adds total number of lines to output_array
void total_lines(char** output_array, int* output_index, int file_index)
{
    char string[MAX];

    sprintf(string, "Total number of lines: %d", (file_index)); //Creates string to be stored in output array, using file_index for total number of lines in file
    strncpy(output_array[*output_index], string, MAX); //Copies string to output_array

    ++(*output_index); //Increments output_array since new string has been added
}


void longest_line(char** file_array, char** output_array, int file_index, int* output_index)
{
    int ll_index = 0;
    int ll_length = 0;
    int k = 0;
    int j = 0;
    char output_string[MAX];
    char truncated_string[MAX];
    int truncated_length = 20;

    for(int i = 0; i < file_index; ++i) //loops once for each string in file_array
    {
        while(file_array[i][k] != '\0') ++k; //Sets K to length of current string

        if(k > ll_length) //If this string is larger than previous largest, updates variables
        {
            ll_index = i; //Sets longest line index
            ll_length = k; //Sets length of longest line
        }

        k = 0;
    }

    while(j <= 19 && j < ll_length) 
    {
        truncated_string[j] = file_array[ll_index][j]; //Sets truncated_string with longest line string, truncates at 20
        ++j;
    }
    
    if(ll_length <= 20) truncated_length = ll_length; //Sets truncated_length to 

    truncated_string[truncated_length] = '\0'; //Sets null char at the end of string


    sprintf(output_string, "The longest is Line %d: \"%s\" (len=%d)", (1 + ll_index), truncated_string, (truncated_length)); //Creates full string to be put into output array
    strncpy(output_array[*output_index], output_string, MAX); //Adds string to output array
    ++(*output_index); //Increments output_index because a new string was added to the array

    return;
}



void shortest_line(char** file_array, char** output_array, int file_index, int* output_index)
{
    int current_length = 0;
    int shortest_length = MAX;
    int shortest_index = 0;
    int k = 0;
    int j = 0;
    char truncated_string[MAX];
    char output_string[MAX];
    int truncated_length = 19;

    for(int i = 0; i < file_index; ++i) //Loops once for each string in file_array
    {
        while(file_array[i][current_length] != '\0') ++current_length; //Increments current_length once for each char in string

        if(current_length < shortest_length) 
        {
            shortest_length = current_length;
            shortest_index = i;
        }

        current_length = 0; //Resets current_length to 0 for next loop
    }

    while(j <= 19 && j < shortest_length) //Loops until string is fully copied or 20 chars are copied to string
    {
        truncated_string[j] = file_array[shortest_index][j]; //Sets truncated_string with shortest string truncates after 20 chars
        ++j;
    }

    if(shortest_length < 19) truncated_length = shortest_length; //Sets truncated_length

    truncated_string[truncated_length] = '\0'; //Sets end of string with '\0'

    sprintf(output_string, "The shortest is Line %d: \"%s\" (len=%d)", (1 + shortest_index), truncated_string, (truncated_length)); //Creates string to be set to output_array
    strncpy(output_array[*output_index], output_string, MAX); //Sets output_array with shorts line info
    ++(*output_index); //Increments one for new string in output_array

    return;
}


//Allocate memory for string to be stored in array
void allocate_array(char** array)
{
    for(int i = 0; i < MAX; ++i)
    {
        array[i] = malloc(MAX * sizeof(char));
    }

    return;
}


//Prints each string in array
void print_results(char** array, int index)
{
    int i = 0;
    while(i < index)
    {
        printf("%s\n", array[i]);
        ++i;
    }

    return;
}


//Gets lines to be processed from user, stores them in file_array, sets file_index for number of strings in file_array
void get_user_lines(char** file_array, int* file_index)
{
    char string[MAX];
    printf("\nTpye in the lines you would like processed blow.\n");
    printf("Press enter without any text to finish entering lines.\n");

    do
    {
        printf("\nType line here: ");
        fgets(string, MAX, stdin); //Puts user input into file_name
        strncpy(file_array[*file_index], string, MAX);
        ++(*file_index);
    } while (string[0] != '\n');

    --(*file_index); //Subtracts one for the last line that is just '\n'

    for(int i = 0; i < *file_index; ++i)
    {
        file_array[i][strcspn(file_array[i], "\n")] = '\0'; //Replaces newline character with '\0' at the end of each string
    }
    
    return;
}

int main()
{
    int choice = 0;
    char* file_array[MAX]; //Holds the each line of the file or user input as a string in the array
    char* output_array[MAX];
    int output_index = 0; //Keeps track of which index of the array is next to be filled in output_array
    int file_index = 0; //Keeps track of how many lines are stored in file array

    allocate_array(file_array); //Allocates space for array
    allocate_array(output_array);

    choice = menu(); //Gets menu choice from user


    if(choice == 1) //Get lines from file if option chosen
    {
        if(!get_file(file_array, &file_index)) //Fills file_array with lines from file
            get_user_lines(file_array, &file_index); //If opening file fails, get lines from user
    }
    else get_user_lines(file_array, &file_index); //Get lines from user if option chosen from menu
    

    truncated_lines(file_array, output_array, &output_index, file_index); //Finds which lines are truncated and updates output_array
    total_lines(output_array, &output_index, file_index); //Finds the total number of lines and updates output_array
    longest_line(file_array, output_array, file_index, &output_index); //Finds the longest line and updates output_array
    shortest_line(file_array, output_array, file_index, &output_index); //Finds the shortest line and updates output_array

    printf("\nLines to be processed: \n"); 
    print_results(file_array, file_index); //Output to user pre-processed lines
    printf("\n");

    printf("Processing results: \n");
    print_results(output_array, output_index); //Output to user processing results

    printf("\nThis program has ended.\n");

    return 0;
}