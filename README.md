<<<<<<< HEAD
# microparser
=======
# A Micro Scanner
The scanner will be a function of no arguments that returns Token values.

**type** 
Token **is** (BeginSym, EndSym, ReadSym, WriteSym, Id, IntLiteral, LParen,
RParen, SemiColon, Comma, AssignOp, PlusOp, MinusOp, EofSym); 

TokenBuffer: String

**function** Scanner **return** Token; 
	The following routines will be used: 


	*Read  
		Inspect — 
			The next input character is read; error if Eof is true.
			The next input character is returned, but input is not advanced; error if Eof is true.
		Advance - 
			The next input character is removed, but not returned; no effect at end of file.
 
	*Eof -
		True at the end of file.

	*BufferChar —  
		Adds its argument to a character buffer called TokenBuffer. This buffer is visible to any part of the compiler, and always contains the text of the most recently scanned token. The content of TokenBuffer will be used particularly by semantic routines. Of course, the characters of this buffer also are used by CheckReserved to determine whether a token that looks like an identifier is actually a reserved word.

	*ClearBuffer —  
		Reset the buffer TokenBuffer to the empty string

	*CheckReserved —  
		Takes the identifiers as they are recognized and returns the proper token class (either Id or some reserved word).
>>>>>>> e842a1fa4815c6646327ef68d51bdbfcfe715815
