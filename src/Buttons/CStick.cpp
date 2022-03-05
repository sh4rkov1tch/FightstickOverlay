#include "CStick.hpp"
#include <iostream>
#include <vector>

#define STICK_OUTER_RADIUS      (95)
#define STICK_OUTER_THICKNESS    (5)
#define STICK_INNER_RADIUS      (65)
#define STICK_INNER_OFFSET      (30)

#define WASD_SIZE      (256)
#define BUTTON_OUTER_SIZE (85)
#define BUTTON_SPACING (5)
#define BUTTON_BORDER_SIZE (5)
#define BUTTON_INNER_SPACING (BUTTON_SPACING*2)
#define BUTTON_INNER_SIZE (BUTTON_OUTER_SIZE-(BUTTON_INNER_SPACING*2)-(BUTTON_BORDER_SIZE*2))

CStick::CStick(int iControllerSlot, int iInputMode, Vector2 vecCenter, Color colStick, Color colBorder):
    m_iControllerSlot(iControllerSlot),
    m_iInputMode(iInputMode),
    m_vecCenter(vecCenter),
    m_colStick(colStick),
    m_colBorder(colBorder)
{

}

CStick::~CStick(){

}

void CStick::Draw(){
    int iLR = 0, iUD = 0;

    switch(m_iInputMode){
    case INPUT_DPAD:
        
        iLR = ((float)IsGamepadButtonDown(m_iControllerSlot, GAMEPAD_BUTTON_LEFT_FACE_LEFT))*-STICK_INNER_OFFSET;
        iLR+=((float)IsGamepadButtonDown(m_iControllerSlot, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))*STICK_INNER_OFFSET;

        iUD = ((int)IsGamepadButtonDown(m_iControllerSlot, GAMEPAD_BUTTON_LEFT_FACE_UP))*-STICK_INNER_OFFSET;
        iUD+=((int)IsGamepadButtonDown(m_iControllerSlot, GAMEPAD_BUTTON_LEFT_FACE_DOWN))*STICK_INNER_OFFSET;

        if(iUD && iLR){
            if(iUD<0)
                iUD=-0.85*STICK_INNER_OFFSET;
            else
                iUD=0.85*STICK_INNER_OFFSET;

            if(iLR<0)
                iLR=-0.85*STICK_INNER_OFFSET;
            else
                iLR=0.85*STICK_INNER_OFFSET;
        }
        break;
    case INPUT_LS:
        iLR = STICK_INNER_OFFSET*GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_LEFT_X);
        iUD = STICK_INNER_OFFSET*GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_LEFT_Y);
        
        break;
    case INPUT_RS:
        iLR = STICK_INNER_OFFSET*GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_RIGHT_X);
        iUD = STICK_INNER_OFFSET*GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_RIGHT_Y);
        
        break;
    default:
        break;
    }


    DrawCircle(
            m_vecCenter.x+iLR, 
            m_vecCenter.y+iUD, 
            STICK_INNER_RADIUS, 
            m_colStick
    );
    for(int thickness=0; thickness<STICK_OUTER_THICKNESS; thickness++)
        DrawCircleLines(m_vecCenter.x, m_vecCenter.y, STICK_OUTER_RADIUS+thickness, m_colBorder);
}   

void CStick::DrawWASD(){
    uint8_t byteInputFlags = 0;

    Vector2 vecCorrectedPos = {m_vecCenter.x-WASD_SIZE/2, m_vecCenter.y-WASD_SIZE/2};     
    std::vector<Vector3> vecButtonPos;

    //Manually setting the buttons because why the hell not ? The only thing that you can configure is the position of the virtual WASD
    vecButtonPos.push_back(Vector3{vecCorrectedPos.x+WASD_SIZE/2-BUTTON_OUTER_SIZE/2, vecCorrectedPos.y+WASD_SIZE/2-BUTTON_OUTER_SIZE-BUTTON_SPACING/2, 0});
    vecButtonPos.push_back(Vector3{vecCorrectedPos.x+WASD_SIZE/2-BUTTON_OUTER_SIZE/2, vecCorrectedPos.y+WASD_SIZE/2+BUTTON_SPACING/2, 1});
    vecButtonPos.push_back(Vector3{vecCorrectedPos.x+WASD_SIZE/2-BUTTON_SPACING-3*(BUTTON_OUTER_SIZE/2), vecCorrectedPos.y+WASD_SIZE/2+BUTTON_SPACING/2, 2});
    vecButtonPos.push_back(Vector3{vecCorrectedPos.x+WASD_SIZE/2+BUTTON_SPACING+BUTTON_OUTER_SIZE/2, vecCorrectedPos.y+WASD_SIZE/2+BUTTON_SPACING/2, 3});

    /*
        0 - Up,
        1 - Down,
        2 - Left,
        3 - Right
        
    */
    switch(m_iInputMode){
    case INPUT_DPAD:
        byteInputFlags = (IsGamepadButtonDown(m_iControllerSlot, GAMEPAD_BUTTON_LEFT_FACE_UP)       << 0) +
                         (IsGamepadButtonDown(m_iControllerSlot, GAMEPAD_BUTTON_LEFT_FACE_DOWN)     << 1) +
                         (IsGamepadButtonDown(m_iControllerSlot, GAMEPAD_BUTTON_LEFT_FACE_LEFT)     << 2) +
                         (IsGamepadButtonDown(m_iControllerSlot, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)    << 3);
        break;
    case INPUT_LS:
        byteInputFlags =    ((GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_LEFT_Y)<0) << 0) +
                            ((GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_LEFT_Y)>0) << 1) +
                            ((GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_LEFT_X)<0) << 2) +
                            ((GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_LEFT_X)>0) << 3);
        break;
    case INPUT_RS:
            byteInputFlags =    ((GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_RIGHT_Y)<0) << 0) +
                            ((GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_RIGHT_Y)>0) << 1) +
                            ((GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_RIGHT_X)<0) << 2) +
                            ((GetGamepadAxisMovement(m_iControllerSlot, GAMEPAD_AXIS_RIGHT_X)>0) << 3);
        break;
    default:
        break;
    }

    for(Vector3 buttonPos : vecButtonPos){
        DrawRectangleLinesEx(
            Rectangle{buttonPos.x, buttonPos.y, BUTTON_OUTER_SIZE, BUTTON_OUTER_SIZE}, BUTTON_BORDER_SIZE, RAYWHITE
        );

        uint8_t byteMask = 0;
        byteMask = 1 << (int)buttonPos.z;

        if(byteMask&byteInputFlags)
            DrawRectangle(
                buttonPos.x+BUTTON_BORDER_SIZE+BUTTON_INNER_SPACING, buttonPos.y+BUTTON_BORDER_SIZE+BUTTON_INNER_SPACING, BUTTON_INNER_SIZE, BUTTON_INNER_SIZE, 
                Color{245, 245, 245, 128}
            );
    }  
}