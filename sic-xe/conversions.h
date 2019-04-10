char* HexToBin(char hexdec) 
{ 
      switch (hexdec) { 
        case '0': 
            return("0000\0");  
        case '1': 
           return("0001\0");  
        case '2': 
           return("0010\0");  
        case '3': 
           return("0011\0");  
        case '4': 
           return("0100\0");  
        case '5': 
           return("0101\0");  
        case '6': 
           return("0110\0");  
        case '7': 
           return("0111\0");  
        case '8': 
           return("1000\0");  
        case '9': 
           return("1001\0");  
        case 'A': 
 			     return("1010\0");  
        case 'B':  
           return("1011\0");  
        case 'C': 
			     return("1100\0");  
        case 'D': 
 			      return("1101\0");  
        case 'E': 
 			      return("1110\0");  
        case 'F': 
           return("1111\0"); 
        }
        return 0;  
}
char BinToHex(char *hexdec) 
{ 
       
        if(strcmp(hexdec,"0000") == 0) 
            return('0');  
        else if(strcmp(hexdec,"0001") == 0) 
            return('1');  
        else if(strcmp(hexdec, "0010") == 0)
            return('2');  
        else  if(strcmp(hexdec, "0011") == 0)
            return('3');  
        else if(strcmp(hexdec, "0100") ==0 )
            return('4');  
        else if(strcmp(hexdec, "0101") == 0)
            return('5');  
        else if(strcmp(hexdec,"0110") == 0)
            return('6');  
        else if(strcmp(hexdec, "0111") == 0)
            return('7');  
        else if(strcmp(hexdec, "1000") == 0)
            return('8');  
        else if(strcmp(hexdec, "1001") == 0)
            return('9');  
        else if(strcmp(hexdec,"1010") == 0)
 			      return('A');  
        else if(strcmp(hexdec, "1011") == 0)
            return('B');  
        else if(strcmp(hexdec, "1100") == 0)
			      return('C');  
        else if(strcmp(hexdec, "1101") == 0)
 			      return('D');  
        else  if(strcmp(hexdec, "1110") == 0)
 			      return('E');  
        else if(strcmp(hexdec, "1111") == 0)
           return('F');
        return 0; 
          
}