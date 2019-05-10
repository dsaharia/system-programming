#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_header_record(FILE*, FILE*);
void create_text_record(FILE*, FILE*);
void create_end_record(FILE*, FILE*);
char end_add[15];
int main() {
    FILE *fobjCode, *fobjProg;
    fobjCode = fopen("object_code_new.txt", "r");
    fobjProg = fopen("object_program.txt", "w");
    create_header_record(fobjProg, fobjCode);
    //create_text_record(fobjProg, fobjCode);
    // create_end_record(fobjProg, fobjCode);
}

void create_header_record(FILE *fobjProg, FILE *fobjCode) {
	FILE *fsource = fopen("source2.txt", "r");
	char prog_name[10];
	char start_add[10];
	
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
	while (fscanf(fobjCode, "%s %*s %*s %*s %*s", end_add) == 1) ;
	printf("SS:%s\n", start_add);
	printf("EE:%s\n", end_add);
	length = atoi(end_add) - atoi(start_add);
	printf("LL:%X\n", length);
	fprintf(fobjProg, "%.6X", length);
	fputc('\n', fobjProg);
	fclose(fsource);
}

// void create_text_record(FILE *fobjProg, FILE *fobjCode) {
// 	FILE *fsource = fopen("source2.txt", "r");
// 	char code[25],buffer[10][15],buffer1[10];
// 	int flag = 0, j = 0, temp = 0, loc, start_add,size;	
// 	while(fscanf(fobjCode, "%X %*s %*s %*s %s", &loc, code) == 2){
// 		// printf("%s\n", code);
// 		if(flag == 0 && strcmp(code, "-") != 0) {
// 			start_add = loc;
// 			fputc('T', fobjProg);
// 			fprintf(fobjProg,"%.6X", start_add);
// 			flag = 1;
// 		}
// 		if (flag > 0 && strcmp(code, "-")!=0 && flag <= 10){
// 			strcpy(buffer[j], code);
// 			flag++;
// 			j++;
// 		}
		
// 		temp = flag-1;
// 		if(flag > 10) {
// 			size = temp * 3;
// 			fprintf(fobjProg, "%.2X", size);
// 			for (int i = 0; i < 10; ++i)
// 			{
// 				fprintf(fobjProg, "%s", buffer[i]);
// 			}
// 			fputc('\n', fobjProg);
// 			flag = 0;j = 0;
// 		}
// 		sprintf(buffer1,"%X",loc);
// 		if (strcmp(buffer1,end_add) == 0) {
// 			size = temp * 3;
// 			fprintf(fobjProg, "%.2X", size);
// 			for (int i = 0; i < temp; ++i)
// 			{
// 				fprintf(fobjProg, "%s", buffer[i]);
// 			}
// 			fputc('\n', fobjProg);
// 			flag = 0;j = 0;
// 		}
// 		// if(flag > 0 && strcmp(code, "-") == 0 && flag < 10) {
// 		// 	size = temp * 3;
// 		// 	fprintf(fobjProg, "%.2X", size);
// 		// 	for (int i = 0; i < temp; ++i)
// 		// 	{
// 		// 		fprintf(fobjProg, "%s", buffer[i]);
// 		// 	}
// 		// 	fputc('\n', fobjProg);
// 		// 	flag = 0;j = 0;
// 		// }
		

// 	}
// }