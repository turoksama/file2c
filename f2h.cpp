/*
	Compile: g++ f2h.cpp -o f2h
	Usage:   f2h foo.txt
*/

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <algorithm>

using namespace std;


void help(char* me) 
{
	cout << "Convert a file into a C source/header char array file." << endl;
	cout << "Usage: " << me << " inputfile" << endl;
	cout << "	It will generate the output file inputfile.h automatically." << endl;
	cout << "	eg: " << me << " foo.obj"<< endl;
	cout << "	    You will get file \"foo.h\"."<< endl;
	cout << "	!!: Input file name should be shorter than 255."<< endl;
}

int main(int argc, char* argv[]) 
{
	if(argc != 2 || strlen(*(argv+1))>=255 || **(argv+1) == '?' ) 
	{
		help(argv[0]); exit(1);
	}
	else 
	{
    	char* fn = argv[1];
		char char_t[384], char_t1[386], char_t2[384];
    	FILE* f = fopen(fn, "rb");
		memset(char_t, 0x00, 384);
		memcpy(char_t, fn, strlen(fn));
    	char *p = strrchr(char_t, '.');
		if(p != NULL)*p = '\0';
		memset(char_t1, 0x00, 386);
		sprintf(char_t1, "%s.h",char_t);
		memcpy(char_t2, char_t1, 384);
		FILE* f2 = fopen(char_t1, "w+");
    	if(!f || !f2) { cerr << "Error while opening/creating file." << endl; exit(1); }
		fputs("/**\n*	",f2);
		fputs(fn,f2);
		fputs("\n*/\n\n",f2);
		transform(char_t2, &char_t2[383], char_t2, ::toupper);
		fputs("#ifndef __",f2);
    	p = strrchr(char_t2, '.');
		if(p != NULL)*p = '\0';
		fputs(char_t2,f2);
		fputs("_H__\n",f2);
		fputs("#define __",f2);
		fputs(char_t2,f2);
		fputs("_H__\n\n",f2);
		
    	p = strrchr(fn, '.');
		if(p != NULL)*p = '\0';
		memset(char_t, 0x00, 384);
		sprintf(char_t, "const char %s[] = \n{\n	\"",fn);
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
		fputs("xFF\"\n};\n\n",f2);
		fputs("#endif\n",f2);
    	fclose(f);
		fclose(f2);
    }
    return 0;
}
