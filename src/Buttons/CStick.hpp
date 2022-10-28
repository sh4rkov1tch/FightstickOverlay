#include <raylib.h>

class CStick{
private:
    int m_iControllerSlot;
    int      m_iInputMode;

    Vector2   m_vecCenter;
    
    Color      m_colStick;
    Color     m_colBorder;
    
    CStick();

public:
    enum e_InputMode{
        INPUT_DPAD = 0,
        INPUT_LS   = 1,
        INPUT_RS   = 2
    };

    CStick(int iControllerSlot, int iInputMode, Vector2 vecCenter, Color colStick, Color colBorder);
    ~CStick();
    void Draw();
    void DrawWASD();
};