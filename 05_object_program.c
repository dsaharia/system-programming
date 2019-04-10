#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_header_record(FILE*, FILE*);
void create_text_record(FILE*, FILE*);
void create_end_record(FILE*, FILE*);

int main() {
    FILE *fobjCode, *fobjProg;
    fobjCode = fopen("object_code.txt", "r");
    fobjProg = fopen("object_program.txt", "w");
    create_header_record(fobjProg, fobjCode);
    create_text_record(fobjProg, fobjCode);
    // create_end_record(fobjProg, fobjCode);
}

void create_header_record(FILE *fobjProg, FILE *fobjCode) {
	FILE *fsource = fopen("source2.txt", "r");
	char prog_name[10];
	char start_add[10];
	char end_add[10];
	int name_space, start_space, length;
	fscanf(fsource, "%s %*s %s", prog_name, start_add);
	fputc('H', fobjProg);
	fprintf(fobjProg, "%s", prog_name);
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
	while (fscanf(fobjCode, "%s %*s %*s %*s %*s", end_add) == 1) {;}
	length = atoi(end_add) - atoi(start_add);
	fprintf(fobjProg, "%.6d", length);
	fputc('\n', fobjProg);
	fclose(fsource);
}

void create_text_record(FILE *fobjProg, FILE *fobjCode) {
	FILE *fsource = fopen("source2.txt", "r");
	char start_add[10];
	
	fputc('T', fobjProg);
