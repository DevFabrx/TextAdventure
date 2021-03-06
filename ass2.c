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
#define EXIT_SUCCESS 0
#define TRUE 1
#define FALSE 0
#define USAGE_ERROR_TEXT "Usage: ./ass2 [file-name]\n"
#define OUT_OF_MEMORY_ERROR_TEXT "[ERR] Out of memory.\n"
#define FILE_READ_ERROR_TEXT "[ERR] Could not read file [filename].\n"
#define INPUT_ERROR_TEXT "[ERR] Please enter A or B.\n"


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

// Function Prototypes
void parseErrorCode(int error_code);
int parseCommandLineInput(char** command_line_input, int argc, char* argv[]);
int readFiles(char* name_of_start_file);
char* readFile(FILE* file);
int gameLoop(Chapter* root_chapter);
int getChapterTitle(FILE* file, char* title);
int isCorrupt(char* data);
Chapter* createChapters(char* chapter_data);
void freeAll(Chapter* root_chapter);
Chapter* createChapters(char* chapter_data);
int printChapterToConsole(Chapter* chapter);



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
  //char command_line_input[LINE_BUFFER];
  char* command_line_input;
  // Parses the command line command_line_input and handles all the possible errors.
  parseErrorCode(parseCommandLineInput(&command_line_input, argc, argv));
  //FILE* file = fopen("start_of_adventure.txt", "r");

  FILE* file = fopen(command_line_input, "r");
  if(file == NULL)
  {
    printf("Cannot open file.\n");
  }

  char* root_data = readFile(file);

  fclose(file);

  //TODO: Error Handling
  if(isCorrupt(root_data))
  {
    return FILE_READ_ERROR;
  }
  Chapter* root_chapter = createChapters(root_data);
  Chapter* current_chapter = root_chapter;
  gameLoop(root_chapter);
  freeAll(root_chapter);
  return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
///
/// Reads in all data from the files into the corresponding data structure
///
/// @param chapter_data char* that contains all Chapter data
/// @return new_chapter New Chapter* to the filled data struct
//
Chapter* createChapters(char* chapter_data)
{
  char* string_copy = (char*) malloc(sizeof(char)*strlen(chapter_data));
  string_copy = strncpy(string_copy, chapter_data, strlen(chapter_data));
  Chapter* new_chapter = (Chapter*) malloc(sizeof(Chapter));
  char* title = strtok(string_copy, "\n");
  char* chapter_A = strtok(NULL, "\n");
  //char* chapter_A_type = &chapter_A[strlen(chapter_A)-4];
  char* chapter_B = strtok(NULL, "\n");
  //char* chapter_B_type = &chapter_B[strlen(chapter_B)-4];
  char* description = strtok(NULL, "\0");
  new_chapter->title_ = title;
  new_chapter->text_ = description;
  if(strcmp(chapter_A,"-")!=0)
  {
    FILE* file = fopen(chapter_A,"r");
    if(file == NULL)
    {
      printf("Cannot open file.\n");
    }

    new_chapter->next_A_ = createChapters(readFile(file));
    fclose(file);
  }
  else
  {
    new_chapter->next_A_ = NULL;
  }
  if(strcmp(chapter_B, "-") != 0)
  {
    FILE* file = fopen(chapter_B,"r");
    if(file == NULL)
    {
      printf("Cannot open file.\n");
    }

    new_chapter->next_B_ = createChapters(readFile(file));
    fclose(file);
  }
  else
  {
    new_chapter->next_B_ = NULL;
  }
  return new_chapter;
}



//-----------------------------------------------------------------------------
///
/// Reads in all data from a file and returns a pointer to the c-string that
/// contains that data
///
/// @param file pointer to the file stream
/// @return char* read c-string
//
char* readFile(FILE* file)
{
  char* buffer = (char*) calloc(LINE_BUFFER, sizeof(char));
  int buffer_length = LINE_BUFFER;
  int length_counter = 0;
  char c;

  while((c=fgetc(file)) != EOF)
  {
    if(length_counter == buffer_length-1)
    {
      buffer_length += LINE_BUFFER;
      buffer = (char*) realloc(buffer, buffer_length);
      if(buffer == NULL)
      {
        return NULL;
      }
    }
    buffer[length_counter] = c;
    length_counter += 1;
  }
  fclose(file);

  //buffer[length_counter] = '\n';
  buffer[length_counter+1] = '\0';
  //buffer = realloc(buffer, length_counter+1);
  return buffer;
}


//-----------------------------------------------------------------------------
///
/// Checks if the read file data is corrupt (does not have the right data
/// structure) and returns 0 if not corrupt and 1 if corrupt.
///
/// @param file pointer to the file stream
/// @return int 1 (TRUE) or 0 (FALSE)
//
int isCorrupt(char* file_data)
{
  char* string_data = (char*) malloc(sizeof(char)*strlen(file_data));
  string_data = strncpy(string_data, file_data, strlen(file_data));
  char* title = strtok(string_data, "\n");
  char* chapter_A = strtok(NULL, "\n");
  char* chapter_A_type = &chapter_A[strlen(chapter_A)-4];
  char* chapter_B = strtok(NULL, "\n");
  char* chapter_B_type = &chapter_B[strlen(chapter_B)-4];
  char* description = strtok(NULL, "\0");
  if(strcmp(chapter_A, "-") != 0 && strstr(chapter_A_type, ".txt") == NULL)
  {
    free(string_data);
    return TRUE;
  }
  if(strcmp(chapter_B, "-") != 0 && strstr(chapter_B_type, ".txt") == NULL)
  {
    free(string_data);
    return TRUE;
  }
  if(description == NULL || strstr(description, "") == NULL)
  {
    free(string_data);
    return TRUE;
  }
  else
  {
    free(string_data);
    return FALSE;
  }
  return FALSE;
}

//-----------------------------------------------------------------------------
///
/// Checks if there is only one command line input argument and parses that
/// into a .txt string so that the file can be opened.
///
/// @param command_line_input pointer where the parsed string is stored
/// @param argc number of inputs from main
/// @param argv pointer to the input array from main
/// @return int error code
//
int parseCommandLineInput(char** command_line_input, int argc, char* argv[])
{
  char* file_format = ".txt";
  // check if no user input or too many user inputs
  if(argc != 2)
  {
    return USAGE_ERROR;
  }
  char* pointer_to_dot_in_string = strchr(argv[1], '.');
  // check if .txt is appended or not, if not append it to the file string
  *command_line_input = argv[1];
  if(strcmp(pointer_to_dot_in_string, file_format) != 0)
  {
    *command_line_input = strcat(argv[1], file_format);
    return EXIT_SUCCESS;
  }
  return EXIT_SUCCESS;
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
  // TODO NO EXIT()
  switch(error_code)
  {
    case 0:
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
int gameLoop(Chapter* chapter)
{
  // TODO "B" input not working properly --> NEED TO FIX
  char input;
  while(TRUE)
  {
    printChapterToConsole(chapter);
    scanf("%c", &input);
    if(input == 'A')
    {
      if(chapter->next_A_== NULL)
      {
        return 0;
      }
      chapter = chapter->next_A_;
    }
    if(input == 'B')
    {
      if(chapter->next_B_== NULL)
      {
        return 0;
      }
      chapter = chapter->next_B_;
    }
  }
}


//-----------------------------------------------------------------------------
///
/// Prints the Chapter data in the right format to the console output
///
/// @param  chapter Chapter* to the data of the chapter
/// @return int error_code
//
int printChapterToConsole(Chapter* chapter)
{
  printf("------------------------------\n");
  printf("%s\n\n", chapter->title_);
  printf("%s\n\n", chapter->text_);
  if(chapter->next_A_ == NULL && chapter->next_B_ == NULL)
  {
    printf("ENDE\n");
    return 0;
  }
  else
  {
    printf("Deine Wahl [A/B]? ");
  }
}


//-----------------------------------------------------------------------------
///
/// Frees all dynamically allocated memory of the Chapter structs
///
/// @param  root_chapter Root chapter of the binary tree data structure
/// @return void
//
void freeAll(Chapter* root_chapter)
{
  if(root_chapter->next_A_ != NULL)
  {
    freeAll(root_chapter->next_A_);
  }
  if(root_chapter->next_B_ != NULL)
  {
    freeAll(root_chapter->next_B_);
  }
  free(root_chapter);
}
