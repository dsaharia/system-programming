#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *fsource;
	fsource = fopen("ex_source.txt","r");
	int buff_add,disp,prog_coun,loc,i;
	buff_add = 0036;
	prog_coun = 1051;
	char label1[10],label2[10],mnemonic[10],temp_lab[10],obj[25],obj1[25];
	char opcode[8];
	strcpy(obj,"010101");
	strcpy(obj1,"011101");
	int new_disp = 4096;
	while(fscanf(fsource,"%X %s %s %s", &loc,label1,mnemonic,label2) == 4){
		if (label2[strlen(label2) - 1] == 'X'){
			for(i=0;label2[i] != ',';i++){
				temp_lab[i] = label2[i];
			}
			temp_lab[i] = '\0';
			disp = buff_add - 0033;
			obj[6] = '1';
			for (i=6;i<12;i++){
				if(i == 6 || i == 7 || i == 8 || i ==9){
					obj[i] = '1';
				}
				else{
					obj[i] = '0';
				}
			}
			printf("Object code 1:%s", obj);
			printf("%.3X\n", disp);
		}
		if(mnemonic[0] == '+'){
			obj[6] = '0';
			for (i=6;i<12;i++){
				if(i == 11 || i == 7){
					obj1[i] = '1';
				}
				else{
					obj1[i] = '0';
				}
			}
			printf("Object code 2:%s", obj1);
			printf("%d\n", new_disp);
		}
	}
}