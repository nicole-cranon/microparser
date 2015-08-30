/* 
	nicole cranon <nicole.cranon@ucdenver.edu
	csci 4640, fall 2015
	assignment 1 - micro scanner
*/

#include "scanner.h"
#include <iostream>

std::vector<scanner::token> scanner::tokenVector;

int main (int argc, char* argv[]) {
	
  char *scanFilename = argv[1];

  scanner::file.open (scanFilename);

  // handle empty file
  if (scanner::file == NULL || scanner::file.fail()) {

    std::cerr << "\nError opening file.\n";

  }

  scanner::token readToken;

  do {

    // get next token
    readToken = scanner::scan ();
    // append next token to token vector
    scanner::tokenVector.push_back (readToken);

//    // print read token symbol
//    std::cout << token_type[readToken] << '\n';

  } while (readToken != scanner::EofSym);

  scanner::file.close();

  for (int i = 0; i < scanner::tokenVector.size(); ++i) {

    std::cout << "Token " << i << ':' <<  ' ' << scanner::token_type [scanner::tokenVector[i]] << " \"" << scanner::tokenBuffer[i] << '\"' << '\n';

  }

	return 0;

}

