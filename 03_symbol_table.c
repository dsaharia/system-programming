#include <stdio.h>

int main()
{
	FILE *fsource, *fintermediate, *fsymbol_table;
	fsource = fopen("source2.txt", "r");
	fintermediate = fopen("intermediate.txt","a+");
	int loc;
	char label1[25],label2[25],mnemonic[25];

	fscanf(fsource, "%*s %*s %d", &loc);
	while (fscanf(fsource, "%s %s %s", label1,mnemonic,label2) == 3) {
		fprintf(fintermediate, "%d ", loc);
		fprintf(fintermediate, "%s %s %s", label1, mnemonic, label2);
		fputc('\n', fintermediate);
		loc += 3;
		

	}


}
