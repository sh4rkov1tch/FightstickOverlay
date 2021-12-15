#include <string>
#include <iostream>

#include "CApp.hpp"

CApp::CApp():
    m_vecButtons(),
    m_pStick(nullptr)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(854, 480, "Raylib - FightstickOverlay");
    SetTargetFPS(60);
    
    _PushButtonsToVector();
        
    Run();
}

CApp::~CApp(){
    delete m_pStick;
}

void CApp::Run(){

    while(!WindowShouldClose()){

        if(IsFileDropped()){
            int iNbFiles = 0;
            char** strTableDroppedFiles = GetDroppedFiles(&iNbFiles);

            std::string strFilePath(strTableDroppedFiles[0]);

            if(strFilePath.find(".ini") != strFilePath.npos)
                _PushButtonsToVector(strTableDroppedFiles[0]);
            else
                std::cout << "Invalid file format" << std::endl;
            
            ClearDroppedFiles();
        }
        BeginDrawing();

            ClearBackground(BLACK);
            
            for(std::vector<CButton>::iterator itButtons = m_vecButtons.begin(); itButtons!=m_vecButtons.end(); itButtons++)
                (*itButtons).Draw();

            m_pStick->Draw();
            

        EndDrawing();
    }
    CloseWindow();
}

void CApp::_PushButtonsToVector(const char* strCfgPath){

    CConfigParser cfgParser(strCfgPath);

    if(!m_vecButtons.empty()){
        m_vecButtons.clear();
    }
    
    if(m_pStick)
        delete m_pStick;
    
    m_pStick = new CStick(0, cfgParser.GetStickInputMode(), Vector2{854/6, 480/2}, Color{245, 245, 245, 128}, RAYWHITE);

    std::vector<std::vector<int>> btnParams = cfgParser.GetButtonParameters();
    for(std::vector<std::vector<int>>::iterator itBtnParams = btnParams.begin(); itBtnParams!=btnParams.end(); itBtnParams++){
        std::vector<int> vecIntPrms = (*itBtnParams);

        int iButtonID = vecIntPrms[5];
        float fVecX = vecIntPrms[0], fVecY = vecIntPrms[1];
        unsigned char uR = vecIntPrms[2];
        unsigned char uG = vecIntPrms[3];
        unsigned char uB = vecIntPrms[4];
        
        m_vecButtons.emplace_back(
            0, 
            (GamepadButton)iButtonID, 
            Vector2{fVecX, fVecY},
            Color{uR, uG, uB, 180},
            Color{uR, uG, uB, 255}
        );
    }

    std::vector<std::vector<int>> axesParams = cfgParser.GetAxisParameters(); 
    for(std::vector<std::vector<int>>::iterator itAxesParams = axesParams.begin(); itAxesParams!=axesParams.end(); itAxesParams++){
        std::vector<int> vecIntPrms = (*itAxesParams);
        int iAxisID = vecIntPrms[5];
        float fVecX = vecIntPrms[0], fVecY = vecIntPrms[1];
        unsigned char uR = vecIntPrms[2];
        unsigned char uG = vecIntPrms[3];
        unsigned char uB = vecIntPrms[4];
        
        m_vecButtons.emplace_back(
            0, 
            (GamepadAxis)iAxisID, 
            Vector2{fVecX, fVecY},
            Color{uR, uG, uB, 180},
            Color{uR, uG, uB, 255}
        );
    }

}