#include "RS485.h"

unsigned char buffer_Frame[15];
uint8_t Size = 11; 
//extern unsigned char buffer_Frame[15];
//extern uint8_t Size = 11; 
void RS485_begin(){
  Serial.begin(9600);
  RS485_recieve;
  //check = "OK";
}
//--------------------------------
uint8_t RS485_readUART(uint8_t c[]){
  uint8_t i = 0;
  LED_status_ON;
  delay(1000);
  while(Serial.available()){
    c[i] = char (Serial.read());
    i++;
  }
  LED_status_OFF;
  return i;
}
//----------------------------------
uint8_t RS485_send_check_Master2Slave(uint8_t address_Slave){
  RS485_transmiter;
  delay(100);
  Serial.print(char(SYMBOL_HEADER_Serial));
  Serial.print(char(Address_Mega));
  Serial.print(",");
  Serial.print(char(address_Slave));
  Serial.print(",");
  Serial.print("OK");
  Serial.print(char(SYMBOL_END));
  delay(100);
  RS485_recieve;
}
//-------------------------------
uint8_t RS485_recieve_check_Slave2Master(){
  /* Kiểm tra cấu trúc (@0,OK!) */
  uint8_t poisition_header = 0;
  uint8_t poisition_end = 0;
  uint8_t poisition_seperate1 = 0;
  uint8_t poisition_seperate2 = 0;
  uint8_t check = 0;
  Size = RS485_readUART(buffer_Frame);

          /* Kiểm tra có ký tự đầu ko */
  for(uint8_t i =0; i < Size; i++){
    if(buffer_Frame[i] == SYMBOL_HEADER_Serial){
      poisition_header = i;
      check ++;
    }
  }
  
  if(check != 1){
    return 1;
  }  
  
           /* Kiểm tra có ký tự cuối ko */
  for(uint8_t i = poisition_header; i < Size; i++){
    if(buffer_Frame[i] == SYMBOL_END){
       poisition_end = i;
       check ++;
    }
  }
  
  if(check != 2){
    return 2;
  }
  
             /* Kiểm tra dấu phẩy 1 */
  for(byte i = (poisition_header+1); i < poisition_end; i++){
    if(buffer_Frame[i] == SYMBOL_SEPERATE){
      poisition_seperate1 = i;
      check ++;
      break;
    }
  }
  if(check != 3){
    return 3;
  }
  
            /* Kiểm tra dấu phẩy 2 */
  for(byte i = (poisition_seperate1 +1); i < poisition_end; i++){
    if(buffer_Frame[i] == SYMBOL_SEPERATE){
      poisition_seperate2 = i;
      check ++;
      break;
    }
  }
  if(check != 4){
    return 4;
  }
  
           /* Kiểm tra địa chỉ Master */
  if (buffer_Frame[poisition_seperate1 -1] == Address_Mega) 
    check ++;

  if(check != 5){
    return 5;
  }
          /* Kiểm tra địa chỉ Slave */
  if ((buffer_Frame[poisition_seperate2 -1] > 48) && (buffer_Frame[poisition_seperate2 -1] < 58))
    check ++;
    
  if(check != 6){
    return 6;
  }
  
          /* Kiểm tra địa chỉ Slave */
  if ((buffer_Frame[poisition_seperate2 +1] == 'O') && (buffer_Frame[poisition_seperate2 +2] == 'K'))
    check ++;
    
  if(check != 7){
    return 7;
  }

  return 0;
}
//----------------------------------------------
uint8_t RS485_send_data_Master2Slave(uint8_t address_Slave, unsigned int data1, unsigned int data2){
  RS485_transmiter;
  delay(100);
  Serial.print(char(SYMBOL_HEADER_Serial));
  Serial.print(char(Address_Mega));
  Serial.print(",");
  Serial.print(char(address_Slave));
  Serial.print(",");
  Serial.print(String(data1));
  Serial.print(",");
  Serial.print(String(data2));
  Serial.print(char(SYMBOL_END));
  delay(100);
  RS485_recieve;
}
//---------------------------------------------
uint8_t RS485_recieve_Again_Slave2Master(){
  uint8_t poisition_header = 0;
  uint8_t poisition_end = 0;
  uint8_t poisition_seperate1 = 0;
  uint8_t poisition_seperate2 = 0;
  uint8_t check = 0;
  Size = RS485_readUART(buffer_Frame);

          /* Kiểm tra ký tự đầu */
  for(uint8_t i =0; i < Size; i++){
    if(buffer_Frame[i] == SYMBOL_HEADER_Serial){
      poisition_header = i;
      check ++;
    }
  }
  
  if(check != 1){
    return 1;
  }  
  
           /* Kiểm tra ký tự cuối */
  for(uint8_t i = poisition_header; i < Size; i++){
    if(buffer_Frame[i] == SYMBOL_END){
       poisition_end = i;
       check ++;
    }
  }
  
  if(check != 2){
    return 2;
  }
  
             /* Kiểm tra dấu phẩy 1 */
  for(byte i = (poisition_header+1); i < poisition_end; i++){
    if(buffer_Frame[i] == SYMBOL_SEPERATE){
      poisition_seperate1 = i;
      check ++;
      break;
    }
  }
  if(check != 3){
    return 3;
  }
  
            /* Kiểm tra dấu phẩy 2 */
  for(byte i = (poisition_seperate1 +1); i < poisition_end; i++){
    if(buffer_Frame[i] == SYMBOL_SEPERATE){
      poisition_seperate2 = i;
      check ++;
      break;
    }
  }
  if(check != 4){
    return 4;
  }
  
           /* Kiểm tra địa chỉ Master */
  if (buffer_Frame[poisition_seperate1 -1] == Address_Mega) 
    check ++;

  if(check != 5){
    return 5;
  }
          /* Kiểm tra địa chỉ Slave */
  if ((buffer_Frame[poisition_seperate2 -1] > 48) && (buffer_Frame[poisition_seperate2 -1] < 58))
    check ++;
    
  if(check != 6){
    return 6;
  }
  
          /* Kiểm tra nội dung */
  if (buffer_Frame[poisition_seperate2 +1] == 'A') 
    if (buffer_Frame[poisition_seperate2 +2] == 'G') 
      if (buffer_Frame[poisition_seperate2 +3] == 'A')
        if (buffer_Frame[poisition_seperate2 +4] == 'I')
          if (buffer_Frame[poisition_seperate2 +5] == 'N')
              check ++;
    
  if(check != 7){
    return 7;
  }

  return 0;
}
