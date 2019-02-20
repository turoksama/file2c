# f2c - Convert a file into a C source/header char array(Simulate a text file).
(Based on IngwiePhoenix/file2c)

This is a very, very simple tool. 

To compile it:

	g++ f2c.cpp -o f2c
	
Then use it like:

	f2c foo.txt foo.h
  	
Now you can compile foo.h and access it like any regular text string array. You could serialize a zip archive in there, or things like that. Just keep in mind, that this is without a header! So to use it properly,you may want to create a header and declare these as "external". Therefore, the variable name appears at the top of the file after a // comment.

An example header may look like this:

	#ifndef HAVE_FILES_H
	#define HAVE_FILES_H
	
	// You can generate this. Each file starts with: // varName
	// where varName is the original variable name.
	
	extern char[] myFile;
	
	#endif
	
Then you can include that header into your code, so it is aware of the variables.

Have fun. ^.^
