/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

#ifndef __RFIDREADER_H__
#define __RFIDREADER_H__
#include <Arduino.h>

#include <SPI.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

class RFIDReader 
{
private:
    String _strUid;
    MFRC522 _mfrc522;
public:
    RFIDReader(uint8_t pinSlaveSelect, uint8_t pinReset);
    void Init();
    bool Read();
    String getUid() { return _strUid; }
};


#endif//_RFIDREADER_H__
