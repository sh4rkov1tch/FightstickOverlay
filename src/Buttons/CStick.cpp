#include "CStick.hpp"
#include <iostream>

#define STICK_OUTER_RADIUS      (95)
#define STICK_OUTER_THICKNESS    (5)
#define STICK_INNER_RADIUS      (65)
#define STICK_INNER_OFFSET      (30)

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