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

    String s_strRFIDUidForStart = String("B3C194DF");     //24번 젤리비 카트 22번  B3C194DF
    
    String s_strRFIDUidFor1 = String("8E184770");   //1번     서울  8E184770
    String s_strRFIDUidFor2 = String("3E183F70");   //2번     인천  3E183F70
    String s_strRFIDUidFor3 = String("1E635970");   //3번     세종  1E635970
    String s_strRFIDUidFor4 = String("8E3C4270");   //4번     대전  8E3C4270
                                                    //5번     대구  BE043770
                                                    //6번     광주  CED84270
                                                    //7번     춘천  5E474A70
                                                    //8번     제주  0EFE4970
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
