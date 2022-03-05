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

            if(!m_iStickDisplayMode)
                m_pStick->Draw();
            else
                m_pStick->DrawWASD();

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
    
    m_iStickDisplayMode = cfgParser.GetStickDisplayMode();

    std::vector<CConfigParser::s_parameters> btnParams = cfgParser.GetButtonParameters();
    for(std::vector<CConfigParser::s_parameters>::iterator itBtnParams = btnParams.begin(); itBtnParams!=btnParams.end(); itBtnParams++){
        CConfigParser::s_parameters paramsInput = (*itBtnParams);
        
        m_vecButtons.emplace_back(
            0, 
            (GamepadButton)paramsInput.iInputID, 
            paramsInput.vecPos,
            Color{paramsInput.colR, paramsInput.colG, paramsInput.colB, 180},
            Color{paramsInput.colR, paramsInput.colG, paramsInput.colB, 255}
        );
    }

    std::vector<CConfigParser::s_parameters> axesParams = cfgParser.GetAxisParameters(); 
    for(std::vector<CConfigParser::s_parameters>::iterator itAxesParams = axesParams.begin(); itAxesParams!=axesParams.end(); itAxesParams++){
        CConfigParser::s_parameters paramsInput = (*itAxesParams);
        
        m_vecButtons.emplace_back(
            0, 
            (GamepadAxis)paramsInput.iInputID,
            paramsInput.vecPos,
            Color{paramsInput.colR, paramsInput.colG, paramsInput.colB, 180},
            Color{paramsInput.colR, paramsInput.colG, paramsInput.colB, 255}
        );
    }

}