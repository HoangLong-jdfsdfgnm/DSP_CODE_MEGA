#ifndef RS485_H_
#define RS485_H_
#include <SPI.h>
#include <Arduino.h>
#define Address_Mega                    48

#define pinLED_connect                  7
#define pinLED_status                   4
#define pinRS485                        6
#define pinSPI                          10

#define   SYMBOL_HEADER_Serial          0x40
#define   SYMBOL_HEADER_Ethernet        0x24
#define   SYMBOL_START_DATA             0x3B
#define   SYMBOL_SEPERATE               0x2C
#define   SYMBOL_SLASH                  0x2F
#define   SYMBOL_END                    0x21
#define   SYMBOL_CHECK                  0x3F

#define pinLED_status                   4
#define pinRS485                        6

#define LED_status_ON       digitalWrite(pinLED_status, HIGH) 
#define LED_status_OFF      digitalWrite(pinLED_status, LOW)  
#define RS485_transmiter    digitalWrite(pinRS485, HIGH)
#define RS485_recieve       digitalWrite(pinRS485, LOW) 


void RS485_begin();
    /* read UART*/
uint8_t RS485_readUART(uint8_t c[]);
  /* Master transmit */
uint8_t RS485_send_check_Master2Slave(uint8_t address_Slave);
uint8_t RS485_send_data_Master2Slave(uint8_t address_Slave);
  /* Master recieve */
uint8_t RS485_recieve_check_Slave2Master();
uint8_t RS485_recieve_Again_Slave2Master();


//volatile uint8_t checkFrameMaster_Status = 0;

//String check;

 
//uint8_t Nhiet_do = 45;  
//uint8_t Ngoai_quan = 9;
#endif
