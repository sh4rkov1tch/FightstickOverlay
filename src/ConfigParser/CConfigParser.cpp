#include <iostream>

#include "CConfigParser.hpp"

CConfigParser::CConfigParser(const char* strFilePath){
    INIReader reader(strFilePath);

    std::vector<std::string>vecButtonNames;
    vecButtonNames = {"btnX", "btnY", "btnRB", "btnLB", "btnA", "btnB"};
    
    std::vector<std::string>vecButtonParamNames;
    vecButtonParamNames = {"posX", "posY", "colR", "colG", "colB", "btnID"};

    std::vector<std::string>vecAxisParamNames;
    vecAxisParamNames = {"posX", "posY", "colR", "colG", "colB", "axisID"};
    
    std::vector<std::string>vecAxisNames;
    vecAxisNames = {"axisRT", "axisLT"};
    
    for(std::vector<std::string>::iterator itBtnName = vecButtonNames.begin(); itBtnName != vecButtonNames.end(); ++itBtnName){
        std::vector<int> vecBtnCache;
        for(std::vector<std::string>::iterator itBtnParams = vecButtonParamNames.begin(); itBtnParams != vecButtonParamNames.end(); ++itBtnParams){
            vecBtnCache.push_back(reader.GetInteger((*itBtnName), (*itBtnParams), -1));
        }
        m_vecButtonsParameters.push_back(vecBtnCache);
    }

        
    for(std::vector<std::string>::iterator itAxisName = vecAxisNames.begin(); itAxisName != vecAxisNames.end(); ++itAxisName){
        std::vector<int> vecAxesCache;
        for(std::vector<std::string>::iterator itAxisParams = vecAxisParamNames.begin(); itAxisParams != vecAxisParamNames.end(); ++itAxisParams){
            vecAxesCache.push_back(reader.GetInteger((*itAxisName), (*itAxisParams), -1));
        }
        m_vecAxesParameters.push_back(vecAxesCache);
    }

    m_iStickInputMode = reader.GetInteger("Stick", "InputMode", 0);
}

CConfigParser::~CConfigParser(){}

std::vector<std::vector<int>> CConfigParser::GetButtonParameters() const{return m_vecButtonsParameters;}

std::vector<std::vector<int>> CConfigParser::GetAxisParameters() const{return m_vecAxesParameters;}

int  CConfigParser::GetStickInputMode() const {return m_iStickInputMode;}

void CConfigParser::PrintParameters(){
    std::cout << "----- BUTTONS -----" << std::endl;
    for(std::vector<std::vector<int>>::iterator itBtns = m_vecButtonsParameters.begin(); itBtns != m_vecButtonsParameters.end(); ++itBtns){
        for(std::vector<int>::iterator itBtnParams = (*itBtns).begin(); itBtnParams != (*itBtns).end(); ++itBtnParams){
            std::cout << (*itBtnParams) << '\t';
        }
        std::cout << std::endl;
    }

    std::cout << "----- AXES -----" << std::endl;
    for(std::vector<std::vector<int>>::iterator itAxes = m_vecAxesParameters.begin(); itAxes != m_vecAxesParameters.end(); ++itAxes){
        for(std::vector<int>::iterator itAxesParams = (*itAxes).begin(); itAxesParams != (*itAxes).end(); ++itAxesParams){
            std::cout << (*itAxesParams) << '\t';
        }
        std::cout << std::endl;
    }

    std::cout << "----- STICK -----" << std::endl;
    std::cout << m_iStickInputMode << '\t' << std::endl;
}