
#include "RS485.h"
#include "RTC.h"
#include <Wire.h>

#define Address_Mega                    48

uint8_t state = 0;
uint8_t i = 0;
uint8_t checkFrameMaster_status = 0;
uint8_t Uno_Active[9];
uint8_t out = 0;

unsigned int Nhiet_do[9];
unsigned int Ngoai_quan[9];

byte second, minute, hour, day, wday, month;
int year;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  // put your setup code here, to run once:
//    pinMode_begin();
//    RTC_begin();
    RS485_begin();
//    SD_begin();
//    Ethernet_begin();
    
    for(i=0; i<9; i++){
      RS485_send_check_Master2Slave(i+49);
//      state = waitting(2,1000);
      if(state == 1){
        checkFrameMaster_status = RS485_recieve_check_Slave2Master();
        if(checkFrameMaster_status == 0){
          Uno_Active[i] = 1;
        }
        else 
          Uno_Active[i] = 0;
      }
      else
        Uno_Active[i] = 0;
    }
//    for(uint8_t i = 0; i<9; i++){
//      Serial.print("Uno_Active: ");
//      Serial.print(i+1);
//      Serial.print("- ");
//      Serial.println(Uno_Active[i]);
//    }
/*setTime(16, 40, 0, 7,28, 3, 18);*/
}

void loop() {
  // put your main code here, to run repeatedly:
  readDS1307();
  In_man_hinh();
  delay(1000);
}
