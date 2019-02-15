#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashTable {
        char mnemonic[10];
        char opcode[10];

}h_table;

void createTable(h_table* table, FILE* fopcode)
{
	int i=0;
        char mnemonic[20],opcode[20];

        while(fscanf(fopcode, "%s %s", mnemonic, opcode) == 2) {
		strcpy(table[i].mnemonic, mnemonic);
		strcpy(table[i].opcode, opcode);
		i++;

        }

}
void print(h_table* table, int no_mnemonic)
{
        int i;

        for(i=0;i<no_mnemonic;i++) {
                printf("%s\t", table[i].mnemonic);
                printf("%s\n", table[i].opcode);

        }


}

int main()
{
        FILE* fopcode = fopen("opcode.txt", "r");
        int no_mnemonic=0;
        char opcode[100];
        while(fgets(opcode,300,fopcode) != NULL) {
                no_mnemonic++;
        }
	rewind(fopcode);
        printf("%d\n", no_mnemonic);
        h_table* table;
        table = malloc(sizeof(h_table) * no_mnemonic);
        createTable(table, fopcode);
	print(table, no_mnemonic);

}
