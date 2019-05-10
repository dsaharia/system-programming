#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE *fobjProg = fopen("object_program.txt", "r");
	FILE *fmem = fopen("memory.txt", "w");
    char line1[20], start_add[5], line2[40], text_size[5], temp[10];
    int j=0, i;
    fgets(line1, 1000, fobjProg);
    for (i = 9; i < 13; ++i)
    {
        start_add[j++] = line1[i];
    }
    start_add[j] = '\0';
    printf("ST:%s\n", start_add);
    sprintf(temp, "%X", atoi(start_add));
    if (strcmp(start_add, "0000") != 0) {
        fprintf(fmem, "No Object program from 0000 to %.4X\n", atoi(temp) - 16);
        fputs(start_add, fmem);
    }
    fgets(line2, 1000, fobjProg);
    i = 7; j =0;
    while(i<9) {
        text_size[j++] = line2[i++];
    }
    text_size[j] = '\0';
    if (!strcmp(text_size, "1E")) {
        
    }
}