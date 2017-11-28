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
#define BUFFERSIZE 80
#define EXIT_SUCCESS 0
#define USAGE_ERROR_TEXT "Usage: ./ass2 [file-name]\n"
#define OUT_OF_MEMORY_ERROR_TEXT "[ERR] Out of memory.\n"
#define FILE_READ_ERROR_TEXT "[ERR] Could not read file [filename].\n"
#define INPUT_ERROR_TEXT "[ERR] Please enter A or B.\n"


// Function Prototypes
void parseErrorCode(int error_code);
int parseCommandLineInput(char* input_string, int argc, char* argv[]);


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
  char input[BUFFERSIZE];
  printf("%s\n", argv[1]);
  // Parses the command line input and handles all the possible errors.
  parseErrorCode(parseCommandLineInput(input, argc, argv));

  return EXIT_SUCCESS;
}

/*
//-----------------------------------------------------------------------------
///
/// <Function Description>
///
/// @param input input
/// @return int output
//
int exampleFunction(int input)
{
  return 0;
}
*/

//-----------------------------------------------------------------------------
///
/// <Function Description>
///
/// @param argc number of inputs
/// @param argv input string array
/// @return int output
//
int parseCommandLineInput(char* input_string, int argc, char* argv[])
{
  // TODO Implement proper command line parsing
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
    input_string = argv[1];
    if(!strcmp(pointer_to_dot_in_string, file_format))
    {
      return FILE_READ_ERROR;
    }
  }
  else
  {
    input_string = strcat(argv[1], file_format);
    printf("%s\n", input_string);
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