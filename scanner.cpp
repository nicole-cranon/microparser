/* 
   nicole cranon <nicole.cranon@ucdenver.edu
   csci 4640, fall 2015
   assignment 1 - micro scanner
 */

#include "scanner.h"
#include <cctype>
#include <iostream>

namespace scanner {

  std::ifstream file;

  // for use in printing the token type
  std::string token_type[]= {

    [BeginSym] = "BeginSym", 
    [EndSym] = "EndSym", 
    [ReadSym] = "ReadSym", 
    [WriteSym] = "WriteSym", 
    [Id] = "Id",
    [IntLiteral] = "IntLiteral",
    [LParen] = "LParen",
    [RParen] = "RParen",
    [SemiColon] = "SemiColon",
    [Comma] = "Comma",
    [AssignOp] = "AssignOp",
    [ExpOp] = "ExpOp",
    [MultOp] = "MultOp",
    [PlusOp] = "PlusOp",
    [MinusOp] = "MinusOp",
    [EqualOp] = "EqualOp",
    [EofSym] = "EofSym"

  };

  char inspect () {

    char c;
    c = file.get();
    file.unget();

    return c;

  }

  void advance () {

    file.get();

  }

  char read () {

    char next_char = inspect();
    advance();

    return next_char;

  }

  token checkReserved (const std::string checkString) {

    if (checkString.compare ("BEGIN") == 0) {

      return BeginSym;

    }

    else if (checkString.compare ("END") == 0) {

      return EndSym;

    }

    else if (checkString.compare ("READ") == 0) {

      return ReadSym;

    }

    else if (checkString.compare ("WRITE") == 0) {

      return WriteSym;

    }

    else {

      return Id;

    }

  }

  std::vector<std::string> tokenBuffer;
  token scan () {

    std::string buffer;

    char currentChar;
    bool done;
    do {

      buffer = "";

      // read current character
      currentChar = read();

      // determine token being read
      switch (currentChar) {

        // do nothing with whitespace 
        case ' ':
        case '\t':
        case '\n':
        case '\r':

          break;

          // identifier or reserved symbol
        case 'a' ... 'z':
        case 'A' ... 'Z':

          buffer += currentChar;

          done = false; 

          // while not done keep reading identifier or reserved symbol
          while (!done) {

            switch (inspect ()) {

              case 'a' ... 'z':
              case 'A' ... 'Z':
              case '0' ... '9':
              case '_':

                currentChar = inspect ();
                buffer += currentChar;
                advance ();
                break;

              default:

                done = true;
                //std::cout << buffer << ' ' ;
                tokenBuffer.push_back (buffer);
                return checkReserved (buffer);

            }

          }

          break;

          // Integer string
        case '0' ... '9':

          buffer += currentChar;

          done = false; 

          while (!done) {

            switch (inspect()) {

              case '0' ... '9':

                currentChar = inspect ();
                buffer += currentChar;
                advance ();

                break;

              default:

                done = true;
                //std::cout << buffer << ' ';
                tokenBuffer.push_back (buffer);
                return IntLiteral;

            }
          }

          break;

          // Left Paren
        case '(':

          buffer += currentChar;

          //std::cout << buffer << ' ' ;
          tokenBuffer.push_back (buffer);

          return LParen;

          break;

          // Right Paren
        case ')':

          buffer += currentChar;

          //std::cout << buffer << ' ' ;
          tokenBuffer.push_back (buffer);

          return RParen;

          break;

          // Semi Colon
        case ';':

          buffer += currentChar;

          //std::cout << buffer << ' ' ;
          tokenBuffer.push_back (buffer);

          return SemiColon;

          break;


          // Comma
        case ',':

          buffer += currentChar;

          //std::cout << buffer << ' ' ;
          tokenBuffer.push_back (buffer);

          return Comma;

          break;

          // Check for Assign Operator
        case ':':

          // Is AssignOp
          if (inspect () == '=') { 

            buffer += currentChar;

            currentChar = inspect ();
            buffer += currentChar;
            advance ();

            //std::cout << buffer << ' ' ;
            tokenBuffer.push_back (buffer);

            return AssignOp;

          }

          // Is lexical error
          else {

            std::cerr << "\nLexical Error\n";

          }

          break;

          // Check for muliplication or exponentiation operator 
        case '*':

          buffer += currentChar;

          // Exponentiation operator
          if (inspect () == '*') { 

            currentChar = inspect ();
            buffer += currentChar;
            advance ();

            //std::cout << buffer << ' ' ;
            tokenBuffer.push_back (buffer);

            return ExpOp;

          }

          // Multiplication operator
          else {

            //std::cout << buffer << ' ' ;
            tokenBuffer.push_back (buffer);

            return MultOp;

          }

          break;

          // Plus operator
        case '+':

          buffer += currentChar;

          //std::cout << buffer << ' ' ;
          tokenBuffer.push_back (buffer);

          return PlusOp;

          break;

          // Minus operator or comment
        case '-':

          buffer += currentChar;
          // Is Comment ignore it
          if (inspect () == '-') {

            while (inspect() != '\n' && inspect() != '\r') {

              currentChar = read();

              buffer += currentChar;
            }

            //std::cout << buffer << '\n';

          }

          // Is minus operator
          else {

            //std::cout << buffer << ' ' ;
            tokenBuffer.push_back (buffer);

            return MinusOp;

          }  

          break;

          // Equality Operator
        case '=':

          buffer += currentChar;

          //std::cout << buffer << ' ' ;
          tokenBuffer.push_back (buffer);

          return EqualOp;

          break;

          // End of file encountered
        case EOF:

          buffer += currentChar;
          tokenBuffer.push_back (buffer);

          return EofSym;
          break;

        default:

          std::cerr << "\nLexical Error\n";

      }

    }while (currentChar != EOF && file.good());

    return EofSym;

  }

}
