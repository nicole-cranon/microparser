/* 
   nicole cranon <nicole.cranon@ucdenver.edu
   csci 4640, fall 2015
   assignment 2 - micro parser
 */

#include "parser.h"
#include <iostream>

int main (int argc, char* argv[]) {

  char *scanFilename = argv[1];

  // instantiate the file stream for reading the provided file
  scanner::file.open (scanFilename);

  // handle empty file
  if (scanner::file == NULL || scanner::file.fail()) {

    std::cerr << "\nError opening file.\n";

  }

  // parse provided file
  parser::systemGoal();

  // close the file stream
  scanner::file.close();

  return 0;

}

