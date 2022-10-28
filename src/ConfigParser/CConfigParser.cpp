#include <iostream>

#include "CConfigParser.hpp"

#define CP_NB_BTNS      (6)
#define CP_NB_AXIS      (2)
#define CP_NB_PARAMS    (6)

CConfigParser::CConfigParser(const char* strFilePath){
    INIReader reader(strFilePath);

    const char *strTableButtons[CP_NB_BTNS] = {"btnX", "btnY", "btnRB", "btnLB", "btnA", "btnB"};
    
    const char *strTableAxis[CP_NB_AXIS] = {"axisRT", "axisLT"};

    for(int k=0; k<CP_NB_BTNS; k++){
        s_parameters params;

        params.vecPos = {
            (float)reader.GetInteger(strTableButtons[k], "posX", 0),
            (float)reader.GetInteger(strTableButtons[k], "posY", 0),
        };

        params.colR = static_cast<uint8_t>(reader.GetInteger(strTableButtons[k], "colR", 0));
        params.colG = static_cast<uint8_t>(reader.GetInteger(strTableButtons[k], "colG", 0));
        params.colB = static_cast<uint8_t>(reader.GetInteger(strTableButtons[k], "colB", 0));


        params.iInputID = reader.GetInteger(strTableButtons[k], "btnID", 0);
        m_vecButtonsParameters.push_back(params);
    }

    for(int k=0; k<CP_NB_AXIS; k++){
        s_parameters params;

        params.vecPos = {
            (float)reader.GetInteger(strTableAxis[k], "posX", 0),
            (float)reader.GetInteger(strTableAxis[k], "posY", 0),
        };

        params.colR = static_cast<uint8_t>(reader.GetInteger(strTableAxis[k], "colR", 0));
        params.colG = static_cast<uint8_t>(reader.GetInteger(strTableAxis[k], "colG", 0));
        params.colB = static_cast<uint8_t>(reader.GetInteger(strTableAxis[k], "colB", 0));

        params.iInputID = reader.GetInteger(strTableAxis[k], "axisID", 0);
        m_vecAxesParameters.push_back(params);
    }

    m_iStickInputMode = reader.GetInteger("Stick", "InputMode", 0);
    m_iStickDisplayMode = reader.GetInteger("Stick", "Wasd", 0);
}

CConfigParser::~CConfigParser(){}

std::vector<CConfigParser::s_parameters> CConfigParser::GetButtonParameters() const{return m_vecButtonsParameters;}

std::vector<CConfigParser::s_parameters> CConfigParser::GetAxisParameters() const{return m_vecAxesParameters;}

int  CConfigParser::GetStickInputMode() const {return m_iStickInputMode;}

int  CConfigParser::GetStickDisplayMode() const {return m_iStickDisplayMode;}

void CConfigParser::PrintParams() const{
    std::vector<CConfigParser::s_parameters>::const_iterator itParams;

    for(itParams=m_vecButtonsParameters.begin(); itParams!=m_vecButtonsParameters.end(); ++itParams){
        std::cout    << "Position: " << std::endl 
                     << "X:" << (*itParams).vecPos.x << "\tY: " << (*itParams).vecPos.y << std::endl
                     << "Color (outer):" << std::endl
                     << "R: " << (*itParams).colR << "\tG: " << (*itParams).colG << "\tB: " << (*itParams).colB << std::endl;

    }
}