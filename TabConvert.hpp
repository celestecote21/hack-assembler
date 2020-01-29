#include <map>
#include <string>
#include <sstream>
#include <iostream>


class TabConvert
{
private:
    std::map<std::string, std::string> tabConvertComp;
    std::map<std::string, std::string> tabConvertJump;
public:
    TabConvert();
    ~TabConvert();

    std::string compToBin(std::string str);
    std::string jumpToBin(std::string str);
};


