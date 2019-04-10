#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"

char* HexToBin(char);

int main() {
    FILE *fmnemonic, *fsource, *fintermediate, *fsymbol, *fobjectCode;
    fmnemonic = fopen("mnemonic.txt", "r");
    fsource = fopen("sic_xe_source.txt", "r");
    fintermediate = fopen("intermediate.txt", "w+");
    fsymbol = fopen("symbol_table.txt", "r+");
    fobjectCode = fopen("object_code.txt", "w");
    // Intermediate and Symbol table generation
    char mnemonic[10], label1[10], label2[10];
    int location;

    fscanf(fsource, "%*s %*s %X", &location);
    // Intermediate File Generation
    while(fscanf(fsource, "%s %s %s", label1, mnemonic, label2) == 3) {
        if (!strcmp(mnemonic, "RESW")) {
            fprintf(fintermediate, "%.4X %s %s %s\n", location, label1, mnemonic, label2);
            location += atoi(label2) * 3;
        }
        else if (!strcmp(mnemonic, "BASE") || !strcmp(mnemonic, "END")) {
            fprintf(fintermediate, "- %s %s %s\n", label1, mnemonic, label2);
        }
        else if (mnemonic[0] == '+') {
            fprintf(fintermediate, "%.4X %s %s %s\n", location, label1, mnemonic, label2);
            location += 4; // for extended mode
        }
        else {
            fprintf(fintermediate, "%.4X %s %s %s\n", location, label1, mnemonic, label2);
            location += 3;
        }
    }
    rewind(fintermediate);
    // Symbol table generation
    char loc[10];
    while(fscanf(fintermediate, "%s %s %*s %*s", loc, label1) == 2) {
        if(strcmp(label1, "-")) {
            fprintf(fsymbol, "%s %s\n", loc, label1);
        }
    }
    rewind(fsymbol);
    rewind(fintermediate);
    // For object code generation
    char object[35], table_mnemonic[10] ,temp[10], opcode[10];
    char d1[5], d2[5], temp1[6], temp2[6], temp3[6], label2_temp[10], temp_mnemonic[10];
    char table_label[15], target[10], buffer[10], target_disp[15];
    int j, i=0, table_loc, base_loc, target_add, disp;
    while(fscanf(fintermediate, "%s %s %s %s", loc, label1, mnemonic, label2) == 4) {
        if (label2[0] == '#') {
            while(fscanf(fmnemonic, "%s %s", table_mnemonic, opcode) == 2) {
                if (!strcmp(table_mnemonic, mnemonic)) {
                    strcpy(d1, HexToBin(opcode[0]));
                    strcpy(d2, HexToBin(opcode[1]));
                    //printf("%s %s\n", d1, d2);
                    while(i<4) {
                        object[i] = d1[i];
                        i++;
                    }
                    j=0;
                    while(i<6) {
                        object[i] = d2[j];
                        i++;
                        j++;
                    }
                     while(i<12) {
                        if (i == 7){
                            object[i] = '1';
                        }
                        else {
                            object[i] = '0';
                        }
                        i++;
                     }
                     object[i] = '\0';
                     i = 0;
                     j = 0;

                     while(i < 4) {
                        temp1[j] = object[i];
                        i++;
                        j++;
                     }
                     j = 0;
                     while (i<8) {
                        temp2[j++] = object[i++];
                     }
                     j = 0;
                     while (i < 12) {
                        temp3[j++] = object[i++];
                     }
                     j = 0;
                     for (i = 1; i < strlen(label2); ++i) // from 1 because to exclude # symbol
                     {
                        label2_temp[j++] = label2[i];
                     }
                     i =0;
                     j =0;
                     fprintf(fobjectCode, "%s %s %s %s ", loc, label1, mnemonic, label2);
                     fprintf(fobjectCode, "%c%c%c%.3X\n",BinToHex(temp1),BinToHex(temp2),BinToHex(temp3),atoi(label2_temp));
                }
            }
            rewind(fmnemonic);
        }
        if (mnemonic[0] == '+') {
            j=0;
            for (int i = 1; i < strlen(mnemonic); ++i) {
                temp_mnemonic[j++] = mnemonic[i];
            }
            temp_mnemonic[j] = '\0';
            i=0;j=0;
            while(fscanf(fmnemonic, "%s %s", table_mnemonic, opcode) == 2) {
                if(!strcmp(temp_mnemonic, table_mnemonic)) {
                    strcpy(d1, HexToBin(opcode[0]));
                    strcpy(d2, HexToBin(opcode[1]));
                    //printf("%s %s\n", d1, d2);
                    while(i<4) {
                        object[i] = d1[i];
                        i++;
                    }
                    j=0;
                    while(i<6) {
                        object[i] = d2[j];
                        i++;
                        j++;
                    }
                    if (label2[0] == '#'){
                     while(i<12) {
                        if (i == 11 || i == 7){
                            object[i] = '1';
                        }
                        else {
                            object[i] = '0';
                        }
                        i++;
                     }                   
                     object[i] = '\0';
                     j = 0;
                     
                     for (i = 1; i < strlen(label2); ++i) // from 1 because to exclude # symbol
                     {
                        label2_temp[j++] = label2[i];
                     }
                     label2_temp[j] = '\0';
                     
                    }
                    else {
                        while(i<12) {
                        if (i == 11 ||  i == 6 || i == 7){
                            object[i] = '1';
                        }
                        else {
                            object[i] = '0';
                        }
                            i++;
                        }
                        strcpy(label2_temp, label2);
                        object[i] = '\0';
                     }
                     
                     i = 0;
                     j = 0;

                     while(i < 4) {
                        temp1[j] = object[i];
                        i++;
                        j++;
                     }
                     temp1[j] = '\0';

                     j = 0;
                     while (i<8) {
                        temp2[j++] = object[i++];
                     }
                     temp2[j] = '\0';
                     j = 0;
                     while (i < 12) {
                        temp3[j++] = object[i++];
                     }
                     temp3[j] = '\0';
                     j = 0;
                     i=0;
                     //printf("N: %s\n", object);
                     while(fscanf(fsymbol, "%X %s", &table_loc, table_label) == 2) {
                        if(!strcmp(table_label, label2_temp)) {
                            fprintf(fobjectCode, "%s %s %s %s ", loc, label1, mnemonic, label2);
                            fprintf(fobjectCode, "%c%c%c%.5X\n",BinToHex(temp1),BinToHex(temp2),BinToHex(temp3), table_loc);
                            printf("%c%c%c%.5X\n",BinToHex(temp1),BinToHex(temp2),BinToHex(temp3), table_loc );
                        }

                     }
                     rewind(fsymbol);
                    }
                }
            }
            rewind(fmnemonic);
            if (!strcmp(mnemonic, "BASE") || !strcmp(mnemonic, "RESW") || !strcmp(mnemonic, "END")) {
                fprintf(fobjectCode, "%s %s %s %s\n", loc, label1, mnemonic, label2);
                if(!strcmp(mnemonic, "BASE")) {
                    while(fscanf(fsymbol, "%X %s", &table_loc, table_label) == 2) {
                            if(!strcmp(table_label, label2)) {
                            base_loc = table_loc;
                        }
                    }
                    rewind(fsymbol);
                    
                }
            }
            if(!strcmp(label2, "-")) {
                while(fscanf(fmnemonic, "%s %s", table_mnemonic, opcode) == 2) {
                    if(!strcmp(mnemonic, table_mnemonic)) {
                        strcpy(d1, HexToBin(opcode[0]));
                        strcpy(d2, HexToBin(opcode[1]));
                        //printf("%s %s\n", d1, d2);
                        while(i<4) {
                            object[i] = d1[i];
                            i++;
                        }
                        j=0;
                        while(i<6) {
                            object[i] = d2[j];
                            i++;
                            j++;
                        }
                        while(i<12) {
                        if (i == 6 || i == 7){
                            object[i] = '1';
                        }
                        else {
                            object[i] = '0';
                        }
                        i++;
                     } 
                        object[i] = '\0';
                        i=0;
                        j=0;
                    while(i < 4) {
                        temp1[j] = object[i];
                        i++;
                        j++;
                     }
                     temp1[j] = '\0';
                     j=0;
                     while (i<8) {
                        temp2[j++] = object[i++];
                     }
                     temp2[j] = '\0';
                     j=0;
                     i=0;
                        fprintf(fobjectCode, "%s %s %s %s %c%c000000\n", loc, label1, mnemonic, label2, BinToHex(temp1), BinToHex(temp2));
                    }
                }
                
            }
            rewind(fmnemonic);
            if (label2[strlen(label2) - 1] == 'X') {
                while(fscanf(fmnemonic, "%s %s", table_mnemonic, opcode) == 2) {
                if (!strcmp(table_mnemonic, mnemonic)) {
                    strcpy(d1, HexToBin(opcode[0]));
                    strcpy(d2, HexToBin(opcode[1]));
                    //printf("%s %s\n", d1, d2);
                    while(i<4) {
                        object[i] = d1[i];
                        i++;
                    }
                    j=0;
                    while(i<6) {
                        object[i] = d2[j];
                        i++;
                        j++;
                    }
                     while(i<12) {
                        if (i == 6 || i == 7 || i == 8 || i == 9){
                            object[i] = '1';
                        }
                        else {
                            object[i] = '0';
                        }
                        i++;
                     }
                     object[i] = '\0';
                     i=0;
                     while(label2[i] != ',') {
                        target[i] = label2[i];
                        i++;
                     }
                     target[i] = '\0';
                     while(fscanf(fsymbol, "%X %s", &table_loc, table_label) == 2) {
                        if(!strcmp(table_label, target)) {
                            target_add = table_loc;
                        }
                     }
                     disp = target_add - base_loc;
                     sprintf(buffer, "%X", disp); // to convert the disp to string
                     if(strlen(buffer) > 3){
                         i = strlen(buffer)-3;
                         j = 0;
                         while(i < 8) {
                            target_disp[j] = buffer[i];
                            i++;
                            j++;
                         }
                         target_disp[j] = '\0';
                         i=0;
                         j = 0;
                         while(i < 4) {
                            temp1[j] = object[i];
                            i++;
                            j++;
                         }
                         temp1[j] = '\0';

                         j = 0;
                         while (i<8) {
                            temp2[j++] = object[i++];
                         }
                         temp2[j] = '\0';
                         j = 0;
                         while (i < 12) {
                            temp3[j++] = object[i++];
                         }
                         temp3[j] = '\0';
                         j = 0;
                         i=0;
                         printf("DD:%s\n", buffer);
                         printf("SS: %s\n", target_disp);
                         fprintf(fobjectCode, "%s %s %s %s ", loc, label1, mnemonic, label2);
                         fprintf(fobjectCode, "%c%c%c%s\n",BinToHex(temp1),BinToHex(temp2),BinToHex(temp3),target_disp);
                    }
                    else {
                        fprintf(fobjectCode, "%s %s %s %s ", loc, label1, mnemonic, label2);
                         fprintf(fobjectCode, "%c%c%c%.3X\n",BinToHex(temp1),BinToHex(temp2),BinToHex(temp3),disp);
                    }
                     rewind(fsymbol);
                     // printf("TT:%s\n", target);
                     // printf("NN: %s\n", object);
                }
            }
            rewind(fmnemonic);
        }
    }

    
    return 0;

}