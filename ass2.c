//------------------------------------------------------------------------------
// ass2.c
//
// This is a text based adventure game where the end of the game depends on the
// user's decisions.
//
// Group: Group 10, study assistant David Bidner
//
// Authors: Fabian Obermayer 01131905
// Daniel Krems 00930736
//------------------------------------------------------------------------------
//


// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Constants
#define LINE_BUFFER 80
#define INITIAL_CHAPTERS 20
#define EXIT_SUCCESS 0
#define TRUE 1
#define FALSE 0
#define USAGE_ERROR_TEXT "Usage: ./ass2 [file-name]\n"
#define OUT_OF_MEMORY_ERROR_TEXT "[ERR] Out of memory.\n"
#define FILE_READ_ERROR_TEXT "[ERR] Could not read file [filename].\n"
#define INPUT_ERROR_TEXT "[ERR] Please enter A or B.\n"


// Function Prototypes
void parseErrorCode(int error_code);
int parseCommandLineInput(char* command_line_input, int argc, char* argv[]);
int readFiles(char* name_of_start_file, void* list_of_chapters);
int gameLoop(void* list_of_chapters);

// Typedef Structs
typedef struct _Chapter_
{
  char* title_;
  char* text_;
  struct _ChapterStruct_* next_A_;
  struct _ChapterStruct_* next_B_;
} Chapter;


// Typedef Enum
typedef enum _ErrorCodes_
{
  SUCCESS,
  USAGE_ERROR,
  OUT_OF_MEMORY_ERROR,
  FILE_READ_ERROR,
  USER_INPUT_ERROR,
  UNKNOWN_ERROR

}ErrorCodes;


//-----------------------------------------------------------------------------
///
/// The main program that reads in all the game files and handles the gamers
/// input
///
/// @param argc number of inputs (is 1 if 0 inputs)
/// @param argv char* with the input string
/// @return always zero
//
int main(int argc, char* argv[])
{
  char command_line_input[LINE_BUFFER];
  Chapter* list_of_chapters = (Chapter*)
      malloc(sizeof(INITIAL_CHAPTERS * sizeof(Chapter)));
  // Parses the command line command_line_input and handles all the possible errors.
  parseErrorCode(parseCommandLineInput(command_line_input, argc, argv));
  parseErrorCode(readFiles(command_line_input));


  return EXIT_SUCCESS;
}


//-----------------------------------------------------------------------------
///
/// Reads in files for the game and saves them in the provided chapter struct
///
/// @param name_of_start_file name of the first chapter/file to read in
/// @return int error_code
//
int readFiles(char* name_of_start_file, void* list_of_chapters)
{
  list_of_chapters = (Chapter*) list_of_chapters;
  // TODO Write function to read in the data
}



//-----------------------------------------------------------------------------
///
/// <Function Description>
///
/// @param argc number of inputs
/// @param argv input string array from command line
/// @return int output
//
int parseCommandLineInput(char* command_line_input, int argc, char* argv[])
{
  char* file_format = ".txt";

  // check if no user input or too many user inputs
  if(argc == 1 || argc > 2)
  {
    return USAGE_ERROR;
  }

  char* pointer_to_dot_in_string = strchr(argv[1], '.');
  // check if .txt is appended or not, if not append it to the file string
  if(strchr(argv[1], '.'))
  {
    command_line_input = argv[1];
    if(strcmp(pointer_to_dot_in_string, file_format))
    {
      return FILE_READ_ERROR;
    }
  }
  else
  {
    command_line_input = strcat(argv[1], file_format);
    return EXIT_SUCCESS;
  }
}


//-----------------------------------------------------------------------------
///
/// This function parses the returned error code from other functions into a
/// readable error string that is written to stdout.
///
/// @param error_code error code
/// @return void
//
void parseErrorCode(int error_code)
{
  switch(error_code)
  {
    case 0:
      printf("Success\n");
      break;
    case 1:
      printf("%s", USAGE_ERROR_TEXT);
      exit(USAGE_ERROR);
    case 2:
      printf("%s", OUT_OF_MEMORY_ERROR_TEXT);
      exit(OUT_OF_MEMORY_ERROR);
    case 3:
      printf("%s", FILE_READ_ERROR_TEXT);
      exit(FILE_READ_ERROR);
    case 4:
      printf("%s", INPUT_ERROR_TEXT);
      break;
    default:
      printf("Unknown Error Code");
      exit(UNKNOWN_ERROR);
  }
}

//-----------------------------------------------------------------------------
///
/// This is the main game loop that prints the current chapter on the screen
/// and handles user input.
///
/// @param  error code
/// @return int error_code
//
int gameLoop(void* list_of_chapters)
{
  // convert void pointer to a pointer to the array of chapters
  list_of_chapters = (Chapter*) list_of_chapters;
  while(TRUE)
  {
    // TODO write main game loop, some functions that print the chapter text
    // and await user input have to be written.
  }

}