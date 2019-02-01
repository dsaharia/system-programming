#include <stdio.h>
#include <stdlib.h>

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
	fgets(opcode,200,finstruction);
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

void mnemonic(FILE *fsource,FILE *finstruction,FILE *mnemonic,char *src) 
{
	while(fscanf(fsource, "%*s %s %*s", src) == 1)
	{
	    printf("%s\n",src);
	
	}

}










