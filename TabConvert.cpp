#include "TabConvert.hpp"

TabConvert::TabConvert(/* args */)
{
    /*
    * remplissage de la table convertissant les partie comp de l'assembleur en binaire
    *
    */
    tabConvertComp["0"] = "0101010";
    tabConvertComp["1"] = "0111111";
    tabConvertComp["-1"] = "0111010";
    tabConvertComp["D"] = "0001100";
    tabConvertComp["A"] = "0110000";
    tabConvertComp["!D"] = "0001101";
    tabConvertComp["!A"] = "0110001";
    tabConvertComp["-D"] = "0001111";
    tabConvertComp["-A"] = "0110011";
    tabConvertComp["D+1"] = "0011111";
    tabConvertComp["A+1"] = "0110111";
    tabConvertComp["D-1"] = "0001110";
    tabConvertComp["A-1"] = "0110010";
    tabConvertComp["D+A"] = "0000010";
    tabConvertComp["D-A"] = "0010011";
    tabConvertComp["A-D"] = "0000111";
    tabConvertComp["D&A"] = "0000000";
    tabConvertComp["D|A"] = "0010101";
    tabConvertComp["M"] = "1110000";
    tabConvertComp["!M"] = "1110001";
    tabConvertComp["-M"] = "1110011";
    tabConvertComp["M+1"] = "1110111";
    tabConvertComp["M-1"] = "1110010";
    tabConvertComp["D+M"] = "1000010";
    tabConvertComp["D-M"] = "1010011";
    tabConvertComp["M-D"] = "1000111";
    tabConvertComp["D&M"] = "1000000";
    tabConvertComp["D|M"] = "1010101";



    tabConvertJump["JGT"] = "001";
    tabConvertJump["JEQ"] = "010";
    tabConvertJump["JGE"] = "011";
    tabConvertJump["JLT"] = "100";
    tabConvertJump["JNE"] = "101";
    tabConvertJump["JLE"] = "110";
    tabConvertJump["JMP"] = "111";
}

TabConvert::~TabConvert()
{
}


std::string TabConvert::compToBin(std::string str){
    
    std::stringstream ss;
    
    for(std::map<std::string, std::string>::iterator itMap = tabConvertComp.begin();
                                    itMap != tabConvertComp.end(); 
                                    itMap++){
        
        if(str.compare(itMap->first) == 0){
            ss << "111" << itMap->second;
        }
    }
    return ss.str();
}



std::string TabConvert::jumpToBin(std::string str){
    
    std::stringstream ss;
    
    for(std::map<std::string, std::string>::iterator itMap = tabConvertJump.begin();
                                    itMap != tabConvertJump.end(); 
                                    itMap++){
        
        if(str.compare(itMap->first) == 0){
            ss << itMap->second;
        }
    }
    return ss.str();
}