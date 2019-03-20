#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fsource, *fintermediate, *fsymbol_table;
	fsource = fopen("source2.txt", "r");
	fintermediate = fopen("intermediate.txt","w");
	fsymbol_table = fopen("symbol_table.txt", "w");
	int loc;
	char label1[25],label2[25], mnemonic[25];

	fscanf(fsource, "%*s %*s %X", &loc);
	while (fscanf(fsource, "%s %s %s", label1,mnemonic,label2) == 3) {
		//printf("%s\n", mnemonic);
		if (!strcmp(label1, "-")) {
			strcpy(label1, "\t");
		}
		fprintf(fintermediate, "%X %s %s %s", loc, label1, mnemonic, label2);
		fputc('\n', fintermediate);
		if (strcmp(label1, "\t") != 0) {
			fprintf(fsymbol_table, "%X %s", loc, label1);
			fputc('\n', fsymbol_table);
		}
		if (!strcmp(mnemonic, "RESW")) {
			loc += atoi(label2) * 3;
		}
		else if (!strcmp(mnemonic, "RESB")) {
			loc += atoi(label2);
		 }
		else if (!strcmp(mnemonic, "BYTE")) {
			if (label2[0] == 'C') {
				loc += (strlen(label2) - 3);
			}
			else {
				loc += ((strlen(label2) - 3) / 2 );
			}

		}
		else {
			loc += 3;
		}
	}
}
