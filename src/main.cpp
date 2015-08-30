/* 
   nicole cranon <nicole.cranon@ucdenver.edu
   csci 4640, fall 2015
   assignment 2 - micro parser
 */

#include "microscanner/src/scanner.h"
#include <iostream>

int main (int argc, char* argv[]) {

  char *scanFilename = argv[1];

  // instantiate the file stream for reading the provided file
  scanner::file.open (scanFilename);

  // handle empty file
  if (scanner::file == NULL || scanner::file.fail()) {

    std::cerr << "\nError opening file.\n";

  }

  // holds the current token as we read the file
  scanner::token readToken;

  do {

    // get next token
    readToken = scanner::scan ();

    // print read token symbol and the contents of the buffer
    std::cout << "Token : " <<  scanner::token_type[readToken] << " \"" << scanner::tokenBuffer << "\"" <<  '\n';

  } while (readToken != scanner::EofSym);

  // close the file stream
  scanner::file.close();

  return 0;

}

