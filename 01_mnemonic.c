#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void label(FILE*, FILE*, char*);
void mnemonic(FILE*,FILE*,FILE*,char*);

int main()
{
	FILE *finstruction, *fsource, *flabel,*fmnemonic;
	char src[25],opcode[25];
	int i=0,j=0;

	finstruction = fopen("opcode.txt","r"); //List of all mneumonics and opcodes.
	fsource = fopen("source.txt", "r"); // Main assembler source file.
	flabel = fopen("label.txt", "a+"); // to save the labels.
	fmnemonic = fopen("mnemonic.txt", "a+");
	//label(fsource,flabel,src);
	mnemonic(fsource,finstruction,fmnemonic,src);

}
void label(FILE* fsource, FILE* flabel, char *src)
{
	//Function to separate labels and save in another file.
	//For labels in column 1.
	while (fscanf(fsource,"%s %*s %*s",src) == 1) 
	{
	    fputs(src, flabel);
	    fputc('\n', flabel);
	}

	rewind(fsource); // To rewind the file pointer to start location.
	// For labels in column 3.
	while (fscanf(fsource,"%*s %*s %s",src) == 1) 
	{
	    fputs(src, flabel);
	    fputc('\n', flabel);
	}

}

void mnemonic(FILE *fsource,FILE *finstruction,FILE *fmnemonic,char *src) 
{
	char mnemonics[25], opcode[25];
	while(fscanf(fsource, "%*s %s %*s", src) == 1)
	{
	    while(fscanf(finstruction, "%s %s", mnemonics,opcode) == 2)
	    {
		if(strcmp(src,mnemonics) == 0)
		{
		    fputs(mnemonics,fmnemonic);
		    fputc('\t', fmnemonic);
		    fputs(opcode,fmnemonic);
		    fputc('\n', fmnemonic);
		}
	    
	    }
	    //printf("%s\t%s\t%s\n",src,mnemonics,opcode);
	    rewind(finstruction);
	
	}

}


