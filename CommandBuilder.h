#ifndef __COMMANDBUILDER_H__
#define __COMMANDBUILDER_H__
/** 
 *  Copyright (c) 2019 Robot&More, jhlee@robotnmore.com(signaled@gmail.com)
 *  
 *  See the file license.txt for copying permission  
 */

#include "Define.h"

class CommandBuilder
{
private:
    enum {
        eInitialPosition = 0, 
        eWareHousePosition, 
        eTargetPosition
    } _currentPosition;

    CMD _cmdList[MAX_CMD];
    uint8_t _cmdIndex;
    uint8_t _buildIndex;
    
    void DebugCMDList();
    bool BuildCmdInitToWareHouse(String strUID);
    bool BuildWareHouseToTargetPosition(String strUID);
    bool BuildTargetPositionToWarePosition(String strUID);

    String s_strRFIDUidForStart = String("B3C194DF");
    
    String s_strRFIDUidFor1 = String("8E3C4270");   //4번         지역 RF번호 리더기로 읽어들인 값 저장
    String s_strRFIDUidFor2 = String("3E183F70");   //2번
    String s_strRFIDUidFor3 = String("1E635970");   //3번
    String s_strRFIDUidFor4 = String("EE942270");   //10번
    String s_strRFIDUidForSeoul2=String("6E292F70");
    
public:
    CommandBuilder();
    ~CommandBuilder();
    void Init();
    bool BuildCmdList(String strUID);
    CMD GetCommand();
    void Next();
};



#endif//__COMMANDBUILDER_H__
