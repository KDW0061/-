/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

#include "RFIDReader.h"


RFIDReader::RFIDReader(uint8_t pinSlaveSelect, uint8_t pinReset)
: _mfrc522(pinSlaveSelect, pinReset)
{
}

void RFIDReader::Init()
{
    SPI.begin();
    _mfrc522.PCD_Init();
}

bool RFIDReader::Read()
{
    if(!_mfrc522.PICC_IsNewCardPresent()){
        return false;
    }
    if (!_mfrc522.PICC_ReadCardSerial()) {
        return false;
    }
    _strUid = "";
    for (uint16_t i = 0; i < _mfrc522.uid.size; i++ ) {
        _strUid.concat(String(_mfrc522.uid.uidByte[i] < 0x10 ? "0": ""));
        _strUid.concat(String(_mfrc522.uid.uidByte[i], HEX));
    }
    _strUid.toUpperCase();

    return true;
}
