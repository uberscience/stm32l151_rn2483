#include "conversions_app.h"
#include <string.h>

char Buf_Hex[]= {'0','1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void convert_dectoascii(uint16_t DEC, char *ASCII){
  uint8_t i;
  uint32_t div = 1;
    for(i = 0; i < 5; i++){
        
        ASCII[i] = (DEC%(100000/div))/(10000/div)+48;
        div = div*10;

    }
}

void convert_ds18b20_to_char(uint16_t temp,char* temp_char){
  char temp_whole;
  unsigned int temp_fraction;

  // Check if temperature is negative
  if (temp & 0x8000) {
     temp_char[0] = '-';
     temp = ~temp + 1;
     }

  // Extract temp_whole
  temp_whole = temp >> 4 ;

  // Convert temp_whole to characters
  if (temp_whole/100)
     temp_char[0] = temp_whole/100  + 48;
  else
     temp_char[0] = '0';

  temp_char[1] = (temp_whole/10)%10 + 48;             // Extract tens digit
  temp_char[2] =  temp_whole%10     + 48;             // Extract ones digit

  // Extract temp_fraction and convert it to unsigned int
  temp_fraction  = temp;
  temp_fraction &= 0x000F;
  temp_fraction *= 625;
  temp_char[3]='.';
  // Convert temp_fraction to characters
  temp_char[4] =  temp_fraction/1000    + 48;         // Extract thousands digit
  temp_char[5] = (temp_fraction/100)%10 + 48;         // Extract hundreds digit
  temp_char[6] = '\0';
  //temp_char[6] = (temp_fraction/10)%10  + 48;       // Extract tens digit
  //temp_char[7] =  temp_fraction%10      + 48;       // Extract ones digit
}

int CharToHex(char *s,char* buf,char Count){
      int i=0;
      char hi,lo,c ;
      //Count = strlen(s);
      // Returns hex String representation of char c
      while( Count--  )
           {  c = *s++;
           hi =  c >> 4;
           lo =  c & 0x0f;
           buf[i++]= Buf_Hex[hi];
           buf[i++]= Buf_Hex[lo];
           }
      ;    
      return i;
}

uint8_t check_hex_format(char *text,char *uncheckdataH,char* uncheckdataL){
    
    uint8_t i,end,start;   
    start = strlen(uncheckdataH);
    end = strlen(text)-strlen(uncheckdataL);
    for(i=start;i<end;i++){
        if(((text[i]>'F')&(text[i]<'a'))|(text[i]<'0')){
            return INVALID_DATA;
        }
        else if((text[i]>'9')&(text[i]<'A')){
            return INVALID_DATA;
        }
        else if(((text[i]<'a')&(text[i]>'F'))|(text[i]>'f')){
            return INVALID_DATA;
        }
    }
    return VALID_DATA;
}

