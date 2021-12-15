#include <raylib.h>

class CButton{

private:
    int        m_iControllerSlot;
    GamepadButton     m_buttonID;
    GamepadAxis         m_axisID;
    Vector2          m_vecCenter;
    int                 m_isAxis;
    Color             m_colInner;
    Color             m_colOuter;
    const char*       m_strLabel;
    CButton();

public:
    CButton(int iControllerSlot, GamepadButton buttonID, Vector2 vecCenter, Color colInner, Color colOuter);
    CButton(int iControllerSlot, GamepadAxis axisID, Vector2 vecCenter, Color colInner, Color colOuter);
    ~CButton();

    void Draw();

};