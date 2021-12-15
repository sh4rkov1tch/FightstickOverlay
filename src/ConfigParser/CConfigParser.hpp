#include <vector>
#include <string>
#include <INIReader.h>

class CConfigParser{
private:
    std::vector<std::vector<int>> m_vecButtonsParameters;
    // Button order {X, Y, RB, LB, A, B}
    
    std::vector<std::vector<int>> m_vecAxesParameters;
    // Axis order {RT, LT}

    int m_iStickInputMode;

    CConfigParser();
public:
    CConfigParser(const char* strFilePath = "Config/default.ini");
    ~CConfigParser();
    std::vector<std::vector<int>> GetButtonParameters() const;
    std::vector<std::vector<int>> GetAxisParameters() const;
    int  GetStickInputMode() const;
    void PrintParameters();
};