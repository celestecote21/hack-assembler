#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <stdio.h>
#include <string.h>
#include <map>
#include "InstructionList.hpp"
#include <vector>

using namespace std;


unsigned int_to_int(unsigned k) {
    if (k == 0) return 0;
    if (k == 1) return 1;                       /* optional */
    return (k % 2) + 10 * int_to_int(k / 2);
}

string strToBin(string str){
    int nbDec = stoi(str);
    stringstream ss;
    ss << int_to_int(nbDec);
    string str_final = ss.str();
    

    return str_final;
}




string CInstruct(char listPars[3][7]){
    stringstream ss;
    //ss << "111";
    string temp = listPars[1];
    map<string, string> tabConvert;
    tabConvert["0"] = "0101010";
    tabConvert["1"] = "0111111";
    tabConvert["-1"] = "0111010";
    tabConvert["D"] = "0001100";
    tabConvert["A"] = "0110000";
    tabConvert["!D"] = "0001101";
    tabConvert["!A"] = "0110001";
    tabConvert["-D"] = "0001111";
    tabConvert["-A"] = "0110011";
    tabConvert["D+1"] = "0011111";
    tabConvert["A+1"] = "0110111";
    tabConvert["D-1"] = "0001110";
    tabConvert["A-1"] = "0110010";
    tabConvert["D+A"] = "0000010";
    tabConvert["D-A"] = "0010011";
    tabConvert["A-D"] = "0000111";
    tabConvert["D&A"] = "0000000";
    tabConvert["D|A"] = "0010101";
    tabConvert["M"] = "1110000";
    tabConvert["!M"] = "1110001";
    tabConvert["-M"] = "1110011";
    tabConvert["M+1"] = "1110111";
    tabConvert["M-1"] = "1110010";
    tabConvert["D+M"] = "1000010";
    tabConvert["D-M"] = "1010011";
    tabConvert["M-D"] = "1000111";
    tabConvert["D&M"] = "1000000";
    tabConvert["D|M"] = "1010101";

    for(map<string, string>::iterator itMap = tabConvert.begin();
                                    itMap != tabConvert.end(); 
                                    itMap++){
        if(temp.compare(itMap->first) == 0){
            ss << "111" << itMap->second;
        }
    }

    // cout << "analyse temp " << endl << endl;

    // for(int k = 0; k < temp.size(); k++){
    //     cout << (int)temp.at(k) << endl;
    // }


    // size_t found = temp.find("A");

    // // pour le a 
    // if (found != string::npos){
    //     ss << "0"; // il y a "A" dans comp dans a = 0
    // }else{
    //     ss << "1";
    // }
      
    // if (temp.find("|") != string::npos){// D|A ou D|M
    //     ss << "010101";
    // }else if(temp.find("D+A") == 0){ // D+A
    //     ss << "000010";
    // }else if(temp.find("D+1") == 0){ // D+1
    //     ss << "011111";
    // }else if(temp.find("A+1") == 0){ // A+1
    //     ss << "110111";
    // }else if(temp.find("M+1") == 0){ // M+1
    //     ss << "110111";
    // }else if(temp.find("D-1") == 0){ // D-1
    //     ss << "001110";
    // }else if(temp.find("D-A") == 0){ // D-A
    //     ss << "010011";
    // }else if(temp.find("D-M") == 0){ //D -M
    //     ss << "010011";
    // }else if(temp.find("&") != string::npos){ // D&A ou D&M
    //     ss << "000000";
    // }else if(temp.find("0") == 0){ // 0
    //     ss << "101010";
    // }else if (temp.find("1") == 0){ // 1
    //     ss << "111111";
    // }else if (temp.find("-1") == 0){ // -1
    //     ss << "111010";
    // }else if (temp.compare("D") == 0){ // D
    //     ss << "001100";
    // }else if(temp.compare("M") == 0){ // M
    //     ss << "110000";
    // }else if(temp.compare("A") == 0){ // A
    //     ss << "110000";
    // }
    
    cout <<  ss.str() << "  " << temp  << endl;


}

vector<std::string> assToBin(vector<std::string>* pt_listAss){
    for(int i = 0; i < pt_listAss->size(); i++){
        string instBin;
        string line = pt_listAss->at(i);
        string::iterator it_line = line.begin();
        string::iterator it_line_end = line.end();

        if(*it_line == '@'){ // si c'est une A instruction
            it_line++;
            instBin += '0';
            char str[16] = "";
            int j = 0;

            while (*it_line)
            {
                str[j] = *it_line;
                it_line ++;
                j++;
            }            
            string str_bin = strToBin(str);
            //rajout des zeros pour que ca fasse 16 bits
            for(int a = str_bin.length() + 1; a < 16; a ++){
                instBin += '0';
            }
            instBin += str_bin; //et on termine par l'addresse en binaire            
            
        }else{
            char listParse[3][7] = {{""},{""},{""}};
            char* temp;
            temp = (char*)malloc(sizeof(char)*7);
            memset(temp, 0, 7);

            if(temp == NULL){
                cerr << "error alloc";
                break;
            }
            int a = 0;
            while (*it_line != '=')
            {
                if(*it_line != ' ' && (int)*it_line != 13){ // pour ne prendre vraiment que l'instruction
                    temp[a] = *it_line;
                    a++;
                }
                it_line++;
            }
            memcpy(listParse[0], temp, a);

            memset(temp, 0, 7);
            a = 0;
            it_line ++; // on va apres le egal

            while (*it_line != ';' && *it_line)
            {
                if(*it_line != ' ' && (int)*it_line != 13){ // pour ne prendre vraiment que l'instruction
                    temp[a] = *it_line;
                    a++;
                }
                it_line++;
            }
            memcpy(listParse[1], temp, a);
            
            if(!*it_line){
                instBin = CInstruct(listParse); // on passe directement a la conversion en binaire si il y a rien d'autre a parser
            }else{
                memset(temp, 0, 7);
                a = 0;
                it_line ++; // on va apres le point virgule

                while (*it_line)
                {
                    if(*it_line != ' ' && (int)*it_line != 13){ // pour ne prendre vraiment que l'instruction
                        temp[a] = *it_line;
                        a++;
                    }
                    it_line++;
                }
                memcpy(listParse[2], temp, a);

                instBin = CInstruct(listParse); // on passe a la conversion en binaire 

            }            
        }
    }
}





int main(int argc, char** argv){

    if(argc < 2){
        std::cout << "usage: " << argv[0] << " Xxx.asm" << endl;
        return -1;
    }

    InstructionList instructionList(argv[1]);
    

    instructionList.parse();


    assToBin(instructionList.getVector());

    //instructionList.print();

}

