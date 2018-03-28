#include "RTC.h"

/********************************************************
 *                         Hàm đọc thời gian 
 *******************************************************/
void readDS1307(){
  Wire.beginTransmission(DS1307);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, NumberOfFields);
  
  second = bcd2dec(Wire.read() & 0x7f);
  minute = bcd2dec(Wire.read() );
  hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
  wday   = bcd2dec(Wire.read() );
  day    = bcd2dec(Wire.read() );
  month  = bcd2dec(Wire.read() );
  year   = bcd2dec(Wire.read() );
  year += 2000;    
}

/********************************************************
 *                 Hàm chuyển mã nhị phân sang thập phân
 *******************************************************/
int bcd2dec(byte num){
  return ((num/16 * 10) + (num % 16));
}

/********************************************************
 *               Hàm chuyển mã thập phân sang mã nhị phân
 ********************************************************/
int dec2bcd(byte num)
{
        return ((num/10 * 16) + (num % 10));
}

 /********************************************************
 *               Hàm cài đặt thời gian Mudule
 ********************************************************/
void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
{
        Wire.beginTransmission(DS1307);
        Wire.write(byte(0x00)); // đặt lại pointer
        Wire.write(dec2bcd(sec));
        Wire.write(dec2bcd(min));
        Wire.write(dec2bcd(hr));
        Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
        Wire.write(dec2bcd(d)); 
        Wire.write(dec2bcd(mth));
        Wire.write(dec2bcd(yr));
        Wire.endTransmission();
}
/********************************************************
 * 
 *******************************************************/
 void In_man_hinh(){
  Serial.print("Thoi gian: ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
  Serial.print("  /  ");
  Serial.print(day);
  Serial.print("-");
  Serial.print(month);
  Serial.print("-");
  Serial.println(year);
}
