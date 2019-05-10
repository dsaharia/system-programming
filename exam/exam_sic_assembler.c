#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *fsource, *fopcode, *fobject, *fsymbol;
	fsource = fopen("source.txt", "r");
	fopcode = fopen("opcode.txt", "r");
	fsymbol = fopen("symbol.txt", "r");
	fobject = fopen("sic_obj.txt", "w");
	int loc,opcode,loc1,i,add;
	char label1[10],label2[10],mnemonic[5],target_label[5],target_content[5],tab_mne[5],tab_label[5];
	char temp[8];
	while(fscanf(fsource, "%X %s %s %s", &loc,label1,mnemonic,label2) == 4){
		if(!strcmp(mnemonic,"LDX")){
			strcpy(target_label,label2);
			printf("T:%s\n", target_label);
		}
	}
	rewind(fsource);
	while(fscanf(fsource, "%X %s %s %s", &loc,label1,mnemonic,label2) == 4){
		if(!strcmp(label1,"ZERO")){
			strcpy(target_content,label2);
			printf("TA:%s\n", target_content);
		}
	}
	rewind(fsource);
	while(fscanf(fsource, "%X %s %s %s", &loc,label1,mnemonic,label2) == 4){
		if(label2[strlen(label2) - 1] == 'X'){
			while(fscanf(fopcode,"%s %X", tab_mne, &opcode) == 2){
				if(!strcmp(tab_mne,mnemonic)){
					while(fscanf(fsymbol,"%X %s", &loc1,tab_label) == 2){
						for (i = 0; label2[i] != ','; ++i)
						{
							temp[i] = label2[i];
						}
						temp[i] = '\0';
						if(!strcmp(temp,tab_label)){
							printf("L:%X\n", loc1);
							add = 32768 + loc1 + atoi(target_content);
						}
					}
					rewind(fsymbol);
				}
			}
			fprintf(fobject, "%X %s %s %s %X%X\n", loc,label1,mnemonic,label2, opcode, add);
		}
	
	else{
			while(fscanf(fopcode,"%s %X", tab_mne, &opcode) == 2){
				if(!strcmp(tab_mne,mnemonic)){
					while(fscanf(fsymbol,"%X %s", &loc1,tab_label) == 2){
						if(!strcmp(label2,tab_label)){
							printf("SS:\n");
							printf("L:%X\n", loc1);
							fprintf(fobject, "%X %s %s %s %.2X%X\n", loc,label1,mnemonic,label2, opcode, loc1);
						}
					}
					rewind(fsymbol);
				}
			}
			rewind(fopcode);
			
		
	}
}
}
