//uint8_t recieveEthernet(){
//  /*  Đọc bản tin */
//  byte i = 0;
//  while(client.available()){
//    _charCommandEthernet[i] = client.read();
//    i++;
//  }
//  /* Kiểm tra cấu trúc */
//  if(( _charCommandEthernet[FRAME_HEADER_Ether] == SYMBOL_HEADER_Ethernet) && (_charCommandEthernet[FRAME_SEPERATE_Ether] == SYMBOL_SEPERATE)&&( _charCommandEthernet[FRAME_END_Ether] == SYMBOL_END)
//   &&(_charCommandEthernet[FRAME_SLASH_1] == SYMBOL_SLASH) && (_charCommandEthernet[FRAME_SLASH_1] == SYMBOL_SLASH) && (_charCommandEthernet[FRAME_SLASH_1] == SYMBOL_SLASH))
//  {
//    _turn   = _charCommandEthernet[FRAME_TURN];
//    hour    = _charCommandEthernet[FRAME_HOUR_1]*10 + _charCommandEthernet[FRAME_HOUR_2];
//    minute  = _charCommandEthernet[FRAME_MINUTE_1]*10 + _charCommandEthernet[FRAME_MINUTE_2];
//    day     = _charCommandEthernet[FRAME_DAY_1]*10 + _charCommandEthernet[FRAME_DAY_2];
//    month   = _charCommandEthernet[FRAME_MONTH_1]*10 + _charCommandEthernet[FRAME_MONTH_2];
//    return 1;
//  }
//  else 
//    return 0;
//}
