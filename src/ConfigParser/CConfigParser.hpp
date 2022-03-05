#include <vector>
#include <string>
#include <INIReader.h>
#include <raylib.h>

class CConfigParser{
public:
    struct s_parameters{
        uint8_t     colR, colG, colB;
        Vector2     vecPos;
        int         iInputID;
    };
private:
    std::vector<CConfigParser::s_parameters> m_vecButtonsParameters;
    // Button order {X, Y, RB, LB, A, B}
    
    std::vector<CConfigParser::s_parameters> m_vecAxesParameters;
    // Axis order {RT, LT}

    int m_iStickInputMode;
    int m_iStickDisplayMode;

    CConfigParser();
public:
    CConfigParser(const char* strFilePath);
    ~CConfigParser();
    std::vector<CConfigParser::s_parameters> GetButtonParameters() const;
    std::vector<CConfigParser::s_parameters> GetAxisParameters() const;
    int  GetStickInputMode() const;
    int  GetStickDisplayMode() const;
    void PrintParams() const;
};