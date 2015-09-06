/*
  nicole cranon <nicole.cranon@ucdenver.edu>
  csci 4640, fall 2015
  assignment 2 - micro parser
 */

#include "parser.h"
#include <iostream>
#include <cstdlib>

namespace parser {

  scanner::token currentToken,
    nextToken;

  void match (const scanner::token& t) {


    currentToken = scanner::scan();

   
      std::cerr << "\nCurrentToken " << scanner::token_type[currentToken] << " Expected Token " << scanner::token_type[t] << '\n';
    if (currentToken != t) {
   
      syntaxError (currentToken); 

    }

  }

  void syntaxError (const scanner::token& t) {

    // TODO : Address syntax error handling
    std::cerr << "\nSyntax Error " << scanner::token_type[t] << '\n';

    exit(EXIT_FAILURE);

  }

  void systemGoal () {

    std::cout << "\nIn systemGoal\n" ;

    program();

    match (scanner::EofSym);

    std::cout << "\nEnd systemGoal\n";

  }

  void program () {

    std::cout << "\nIn program\n" ;
    match (scanner::BeginSym);

    stmtList ();

    match (scanner::EndSym);

    std::cout << "\nEnd program\n";

  }

  void stmtList () {
    std::cout << "\nIn stmtList\n" ;
    statement ();

    nextToken = getNextToken();

    switch (nextToken) {

      case (scanner::Id) :
      case (scanner::ReadSym) :
      case (scanner::WriteSym) :

        stmtList();
        break;

			default :
				return;

    }

    std::cout << "\nEnd stmtList\n";

  }

  void statement () {

    std::cout << "\nIn statement\n";
    nextToken = getNextToken();

    switch (nextToken) {

      case (scanner::Id) :

        ident ();
        match (scanner::AssignOp);
        expression();
        match (scanner::SemiColon);

        break;

      case (scanner::ReadSym) :

        match (scanner::ReadSym);
        match (scanner::LParen);
        idList();
        match (scanner::RParen);
        match (scanner::SemiColon);

        break;

      case (scanner::WriteSym) :

        match (scanner::WriteSym);
        match (scanner::LParen);
        exprList ();
        match (scanner::RParen);
        match (scanner::SemiColon);
        break;

      default:

        syntaxError (nextToken);

    }

    std::cout << "\nEnd statement\n";

  }

  void idList () {

    std::cout << "\nIn idList\n";

    ident();

    nextToken = getNextToken();

    if (nextToken == scanner::Comma) {

      match(scanner::Comma);
      
      idList();

    }

    std::cout << "\nEnd idList\n";

  }

  void ident () {

    std::cout << "\nIn ident\n";
    match (scanner::Id);

    std::cout << "\nEnd ident\n";

  }

  void exprList () {

    std::cout << "\nIn exprList\n";

    expression ();

    nextToken = getNextToken();

    if (nextToken == scanner::Comma) {

      match(scanner::Comma);

      exprList();

    }

    std::cout << "\nEnd exprList\n";

  }

  void expression () {
   
    std::cout << "\nIn expression\n";

    primary ();

    nextToken = getNextToken();

    if (nextToken == scanner::PlusOp || nextToken == scanner::MinusOp) {

        addOp ();
        expression ();

    }

    std::cout << "\nEnd expression\n";

  }

  void primary ()  {

    std::cout << "\nIn primary\n";

    nextToken = getNextToken();

    switch (nextToken) {

      case (scanner::Id):

        ident();
        break;

      case (scanner::IntLiteral):

        match (scanner::IntLiteral);
        break;

      case (scanner::LParen):

        match (scanner::LParen);
        expression ();
        match (scanner::RParen);

        break;

      default :

        syntaxError(nextToken);

    }

    std::cout << "\nEnd primary\n";

  }

  void addOp () {

    std::cout << "\nIn addOp\n";

    nextToken = getNextToken ();

    switch (nextToken) {

      case (scanner::PlusOp) :
        match (scanner::PlusOp);
        break;

      case (scanner::MinusOp) :
        match (scanner::MinusOp);
        break;

      default:
        syntaxError(nextToken);

    }

    std::cout << "\nEnd addOp\n";

  }

  scanner::token getNextToken () {

    int initialPosition = scanner::file.tellg();
    //std::cout << "\nInitial Position " << initialPosition << '\n';

    std::string buffer = "";

    char currentChar;
    bool done;
    do {

      buffer = "";

      // read current character
      currentChar = scanner::read();

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

          buffer += currentChar ;

          done = false; 

          // while not done keep reading identifier or reserved symbol
          while (!done) {

            switch (scanner::inspect ()) {

              case 'a' ... 'z':
              case 'A' ... 'Z':
              case '0' ... '9':
              case '_':

                currentChar = scanner::inspect ();
                buffer += currentChar ;
                scanner::advance ();
                break;

              default:
                
                done = true;
                //std::cout << buffer << ' ' ;

                // check if an id or a reserved word
                scanner::file.seekg (initialPosition);
                return scanner::checkReserved (buffer);

            }

          }

          break;

        // Integer string
        case '0' ... '9':

          buffer += currentChar ;

          done = false; 

          while (!done) {

            switch (scanner::inspect()) {

              case '0' ... '9':

                currentChar = scanner::inspect ();
                buffer += currentChar ;
                scanner::advance ();

                break;

              default:

                done = true;
                //std::cout << buffer << ' ';


                scanner::file.seekg (initialPosition);
                return scanner::IntLiteral;

            }
          }

          break;

        // Left Paren
        case '(':

          buffer += currentChar ;

          //std::cout << buffer << ' ' ;


          scanner::file.seekg (initialPosition);
          return scanner::LParen;

          break;

        // Right Paren
        case ')':

          buffer += currentChar ;

          //std::cout << buffer << ' ' ;

          scanner::file.seekg (initialPosition);

          return scanner::RParen;

          break;

        // Semi Colon
        case ';':

          buffer += currentChar ;

          //std::cout << buffer << ' ' ;


          scanner::file.seekg (initialPosition);
          return scanner::SemiColon;

          break;


        // Comma
        case ',':

          buffer += currentChar ;

          //std::cout << buffer << ' ' ;


          scanner::file.seekg (initialPosition);
          return scanner::Comma;

          break;

        // Check for Assign Operator
        case ':':

          buffer += currentChar ;

          // Is AssignOp
          if (scanner::inspect () == '=') { 

            currentChar = scanner::inspect ();
            buffer += currentChar ;
            scanner::advance ();

            //std::cout << buffer << ' ' ;


            scanner::file.seekg (initialPosition);
            return scanner::AssignOp;

          }

          // Is lexical error
          else {

            std::cerr << "\nLexical Error\n";

          }

          break;

        // Check for muliplication or exponentiation operator 
        case '*':

          buffer += currentChar ;

          // Exponentiation operator
          if (scanner::inspect () == '*') { 

            currentChar = scanner::inspect ();
            buffer += currentChar ;
            scanner::advance ();

            //std::cout << buffer << ' ' ;


            scanner::file.seekg (initialPosition);
            return scanner::ExpOp;

          }

          // lexical error, there is no multiplication
          else {

            std::cerr << "\nLexical Error\n";

          }

          break;

        // Plus operator
        case '+':

          buffer += currentChar ;

          //std::cout << buffer << ' ' ;


          scanner::file.seekg (initialPosition);
          return scanner::PlusOp;

          break;

        // Minus operator or comment
        case '-':

          buffer += currentChar ;
          // Is Comment ignore it
          if (scanner::inspect () == '-') {

            while (scanner::inspect() != '\n' && scanner::inspect() != '\r') {

              currentChar = scanner::read();

              buffer += currentChar ;
            }

            //std::cout << buffer << '\n';

          }

          // Is minus operator
          else {

            //std::cout << buffer << ' ' ;


            scanner::file.seekg (initialPosition);
            return scanner::MinusOp;

          }  

          break;

        // Equality Operator
        case '=':

          buffer += currentChar ;

          //std::cout << buffer << ' ' ;


          scanner::file.seekg (initialPosition);
          return scanner::EqualOp;

          break;

        // End of file encountered
        case EOF:

          buffer += currentChar ;


          scanner::file.seekg (initialPosition);
          return scanner::EofSym;
          break;

        default:

          scanner::file.seekg (initialPosition);
          std::cerr << "\nLexical Error\n";
					exit(EXIT_FAILURE);

      }

    }while (currentChar != EOF && scanner::file.good());

		scanner::file.seekg (initialPosition);
		std::cerr << "\nLexical Error\n";
		exit(EXIT_FAILURE);

  }

}
