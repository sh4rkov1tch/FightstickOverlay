#include "CButton.hpp"

#define BTN_OUTER_RADIUS            (47)
#define BTN_OUTER_THICKNESS          (3)

#define BTN_INNER_RADIUS            (40)

CButton::CButton(int iControllerSlot, GamepadButton buttonID, Vector2 vecCenter, Color colInner, Color colOuter):
    m_iControllerSlot(iControllerSlot),
    m_buttonID(buttonID),
    m_vecCenter(vecCenter),
    m_isAxis(0),
    m_colInner(colInner),
    m_colOuter(colOuter)
{

}

CButton::CButton(int iControllerSlot, GamepadAxis axisID, Vector2 vecCenter, Color colInner, Color colOuter):
    m_iControllerSlot(iControllerSlot),
    m_axisID(axisID),
    m_vecCenter(vecCenter),
    m_isAxis(1),
    m_colInner(colInner),
    m_colOuter(colOuter)
{

}

CButton::~CButton(){}

void CButton::Draw(){
    for(int thickness=0; thickness<BTN_OUTER_THICKNESS; thickness++){
        DrawCircleLines(m_vecCenter.x, m_vecCenter.y, BTN_OUTER_RADIUS+thickness, m_colOuter);
    }
    
    if(m_isAxis){
        if(GetGamepadAxisMovement(m_iControllerSlot, m_axisID)>0)
            DrawCircle(m_vecCenter.x, m_vecCenter.y, BTN_INNER_RADIUS, m_colInner);
    }
    else{
        if(IsGamepadButtonDown(m_iControllerSlot, m_buttonID))
            DrawCircle(m_vecCenter.x, m_vecCenter.y, BTN_INNER_RADIUS, m_colInner);
    }
}
