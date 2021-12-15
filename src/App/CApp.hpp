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
    
    CStick*  m_stick;

    void _PushButtonsToVector(const char* strCfgPath = "Configs/default.ini");
public:
    CApp();
    ~CApp();
    void Run();
    
};