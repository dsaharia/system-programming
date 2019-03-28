#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	FILE *fobject, *fsymbol, *fintermediate, *fmnemonic;
	fobject = fopen("object_code.txt", "w");
	fsymbol = fopen("symbol_table.txt", "r");
	fintermediate = fopen("intermediate.txt", "r");
	fmnemonic = fopen("mnemonic.txt", "r");

	char line[1000], operand[20], opcode[5], object_code[30], mnemonic[25], tabbed_mnemonic[25], table_mnemonic[25], location[25], table_label[25];
	char target_label[10], target_operand[10];
	int index_location;

	while(fgets(line,1000, fintermediate)) {
		sscanf(line, "%*s %s %s %s", tabbed_mnemonic, mnemonic, operand);
		printf("%s %s %s\n", tabbed_mnemonic, mnemonic, operand);
		line[strlen(line) - 1] = ' ';
		// if (mnemonic[strlen(mnemonic)-1] == 'X') {
		// 	strcpy(target_address, )
		// }

		while (fscanf(fmnemonic, "%s\t%s", table_mnemonic, object_code) == 2) {
			if(!strcmp(table_mnemonic, mnemonic) || !strcmp(table_mnemonic, tabbed_mnemonic)) {
				if (!strcmp(mnemonic, "LDX")) {
					strcpy(target_label, operand);
					printf("TARGET: %s\n", target_label);
				}
				strcat(line, object_code);
				break;
			}
		 // for mnemonic to opcode
		}

		while(fscanf(fsymbol, "%s %s", location, table_label) == 2) {
			if (line[5] == '\t') {
				if (!strcmp(table_label, mnemonic)) {
					strcat(line, location);
				}
			}
			else if (!strcmp(table_label, operand)) {
				strcat(line, location);
				break;

			}
		}
		rewind(fsymbol);
		rewind(fmnemonic);
		fputs(line, fobject);
		if (operand[0] == 'C' && operand[1] == '\'') {
			char m_representation[strlen(operand)-2]; // temp array for the constant
			int i = 2, k = 0;
			while (operand[i] != '\'') {
				m_representation[k] = operand[i];
				k++; i++;
			}
			m_representation[k] = '\0';
			i = 0;
			while (i < strlen(m_representation)) {
				fprintf(fobject, "%X", m_representation[i++]);
			}

		}
		fputc('\n', fobject);
		
	 }
	 
	while (fgets(line,1000, fintermediate)) {
		sscanf(line, "%*s %s %s %s", tabbed_mnemonic, mnemonic, operand);
		if (!strcmp(target_label, tabbed_mnemonic)) {
			index_location = atoi(operand);
			break;
		}
		// while (fscanf(fsymbol, "%s %s", location, table_label) == 2) {
		// 	if (!strcmp())
		// }
	}
	printf("value at register X: %d\n", index_location);

}
