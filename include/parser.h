/*
  nicole cranon <nicole.cranon@ucdenver.edu>
  csci 4640, fall 2015
  assignment 2 - micro parser
 */

#ifndef _PARSER
#define _PARSER

#include "scanner.h"

// TODO : Add equality and exponential operator productions

namespace parser {

  // hold current and next tokens
  extern scanner::token currentToken, 
    nextToken;

  /*
    match

    precondition -
    a legal token, t

    postcondition - 
    calls a syntax error on the given token
   */
  void match (const scanner::token& t);

  /*
    syntaxError

    precondition - 
    a token, t

    postcondition - 
    handles the case of an illegal token
   */
  void syntaxError (const scanner::token& t);

  /*
    systemGoal

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition - 
    calls the program production and looks for the end of file token
   */
  void systemGoal ();

  /*
    program

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition -
    looks for the begin token, calls the stmtList production, then looks for the end token
   */
  void program ();

  /*
    stmtList

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition - 
    calls the statement production, then checks if it needs to call itself again, ie
    there is another statement to process
   */
  void stmtList ();

  /*
    statement

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition -
    handles the id, read, and write statement cases
   */
  void statement ();

  /*
    idList

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition - 
    calls the ident production, then checks if it needs to call itself again, ie
    there is another ident to process
   */
  void idList ();

  /*
    ident

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition - 
    checks for the id token
   */
  void ident ();

  /*
    exprList

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition -
    calls the expression production, then checks if it needs to call itself again, ie
    there is another expresssion to process
   */
  void exprList ();

  /*
    expression

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition -
    calls the primary production, if there is an add operation, it calls the add op 
    production and calls itself again to process the rest of the expression
   */
  void expression ();

//  /*
//    exponential
//
//    precondition -
//    if stream object scanner::file opened for a specific file
//
//    postcondition - 
//    handles the case of primary and primary ** exponential
//   */
//  void exponential ();

  /*
    primary 

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition - 
    handles the case of id, int literal, or expression primary
   */
  void primary ();

  /*
    addOp

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition -
    checks for the plusOp, or minusOp token

   */
  void addOp ();

  /*
    getNextToken

    precondition -
    if stream object scanner::file opened for a specific file

    postcondition -
    returns the next token, but does not advance the read stream
   */
  scanner::token getNextToken ();


}

#endif
