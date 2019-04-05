#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_header_record(FILE*, FILE*);

int main() {
    FILE *fobjCode, *fobjProg;
    fobjCode = fopen("object_code.txt", "r");
    fobjProg = fopen("object_program.txt", "w");
    create_header_record(fobjProg, fobjCode);
}

void create_header_record(FILE *fobjProg, FILE *fobjCode) {
	FILE *fsource = fopen("source2.txt", "r");
	char prog_name[6],start_add[6], end_add[6];
	int name_space, start_space, length;
	fscanf(fsource, "%s %*s %s", prog_name, start_add);
	fputc('H', fobjProg);
	fprintf(fobjProg, "%s", prog_name);
	// fputs(prog_name, fobjProg);
	name_space = 6 - strlen(prog_name);
	while(name_space) {
		fputc(' ', fobjProg);
		name_space--;
	}
	start_space = 6 - strlen(start_add);
	while(start_space) {
		fputc('0', fobjProg);
		start_space--;
	}
	// Can be done also using %.6X
	fputs(start_add, fobjProg);
	// for length of the program
	while (fscanf(fobjCode, "%s %*s %*s %*s %*s", end_add) == 1);
	length = atoi(end_add) - atoi(start_add);
	printf("%s\n", start_add);
	//fprintf(fobjProg, "%X\n", length);
	// fputs(length, fobjProg);

}