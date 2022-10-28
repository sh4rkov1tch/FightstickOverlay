#include <vector>
#include <map>

#include <algorithm>

#include <raylib.h>

#include <CConfigParser.hpp>
#include <CButton.hpp>
#include <CStick.hpp>

class CApp{
private:
    std::vector<CButton> m_vecButtons;
    
    int      m_iStickDisplayMode;
    CStick*  m_pStick;

    void _PushButtonsToVector(const char* strCfgPath);
public:
    CApp(const char* strCfgPath = "Configs/default.ini");
    ~CApp();
    void Run();
    
};