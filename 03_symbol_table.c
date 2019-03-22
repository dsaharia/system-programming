#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fsource, *fintermediate, *fsymbol_table;
	fsource = fopen("source2.txt", "r");
	fintermediate = fopen("intermediate.txt","a+");
	fsymbol_table = fopen("symbol_table.txt", "a+");
	int loc;
	char label1[25],label2[25], mnemonic[25];

	fscanf(fsource, "%*s %*s %X", &loc);
	while (fscanf(fsource, "%s %s %s", label1,mnemonic,label2) == 3) {
		//printf("%s\n", mnemonic);
		if (!strcmp(mnemonic, "RESW")) {
		    fprintf(fintermediate, "%X ", loc);
		    fprintf(fsymbol_table, "%X ", loc);
		    if (!strcmp(label1, "-")) {
				strcpy(label1, "\t");

			}
			fprintf(fintermediate, "%s %s %s", label1, mnemonic, label2);
			fprintf(fsymbol_table, "%s ", label1);
			fputc('\n', fintermediate);
			fputc('\n', fsymbol_table);
			loc += atoi(label2) * 3;
		}
		else if (!strcmp(mnemonic, "RESB")) {
		 	fprintf(fintermediate, "%X ", loc);
		    fprintf(fsymbol_table, "%X ", loc);
		    if (!strcmp(label1, "-")) {
				strcpy(label1, "\t");
			}
			fprintf(fintermediate, "%s %s %s", label1, mnemonic, label2);
			fprintf(fsymbol_table, "%s ", label1);
			fputc('\n', fintermediate);
			fputc('\n', fsymbol_table);
			loc += atoi(label2);
		 }
		else {
			fprintf(fintermediate, "%X ", loc);
		    fprintf(fsymbol_table, "%X ", loc);
			if (!strcmp(label1, "-")) {
				strcpy(label1, "\t");
			}
			fprintf(fintermediate, "%s %s %s", label1, mnemonic, label2);
			fprintf(fsymbol_table, "%s ", label1);
			fputc('\n', fintermediate);
			fputc('\n', fsymbol_table);
			loc += 3;
		}



	}


}
