/*
	Compile: g++ f2c.cpp -o f2c
	Usage:   f2c foo.txt foo.h
*/

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>

using namespace std;

void help(char* me) 
{
	cout << "Convert a file into a C source/header char array file." << endl;
	cout << "Usage: " << me << " inputfile outputfile" << endl;
	cout << "	eg: " << me << " foo.obj foo.c"<< endl;
	cout << "	!!: File name should be shorter than 255."<< endl;
}

int main(int argc, char* argv[]) 
{
	if(argc != 3 || strlen(*(argv+1))>=255 || strlen(*(argv+2))>=255 ) 
	{
		help(argv[0]); exit(1);
	}
	else 
	{
    	char* fn = argv[1];
    	char* varName = argv[2];
		char char_t[384];
    	FILE* f = fopen(fn, "rb");
		FILE* f2 = fopen(varName, "w+");
    	if(!f) { cerr << "Error while opening file." << endl; exit(1); }
    	char *p = strrchr(varName, '.');
		if(p != NULL)*p = '\0';
		memset(char_t, 0x00, 384);
		sprintf(char_t, "const char %s[] = \n{\n	\"",varName);
		fputs(char_t,f2);
    	while(!feof(f)) 
		{
        	unsigned char c;
        	if(fread(&c, 1, 1, f) == 0) break;
			if(c == '\n')
			{
				fputc('\\', f2);
				fputc('n', f2);
				fputc('\"', f2);
				fputc(c, f2);
				fputc('	', f2);
				fputc('\"', f2);
			}
			else if(c == '\r')
			{
				
			}
			else
			{
				fputc(c, f2);
			}			
    	}
		fputc('\\', f2);
		fputs("xFF\"\n};\n",f2);
    	fclose(f);
		fclose(f2);
    }
    return 0;
}