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

// Constants
#define EXIT_SUCCESS 0


// Function Prototypes



// Typedef Structs
typedef struct _Chapter_
{
  char* title_;
  char* text_;
  struct _ChapterStruct_* next_A_;
  struct _ChapterStruct_* next_B_;
} Chapter;

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


//-----------------------------------------------------------------------------
///
/// The main program that reads in all the game files and handles the gamers
/// input
///
/// @param argc number of inputs (is 1 if 0 inputs)
/// @param argv char* with the input string
/// @return always zero
//
int main(int argc, char* argv)
{

  return EXIT_SUCCESS;
}