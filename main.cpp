#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <string.h>
#include <vector>

#include "InstructionList.hpp"
#include "TabConvert.hpp"


using namespace std;


unsigned long int_to_int(unsigned long k) {
    if (k == 0) return 0;
    if (k == 1) return 1;                       /* optional */
    return (k % 2) + 10 * int_to_int(k / 2);
}

/*
*convertie une string representant un nobre en binaire (donne l'addresse)
*/
string strToBin(string str){
    int nbDec = 0;
    try{
    nbDec = stoi(str);
    }
    catch(exception e){
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
    stringstream ss;
    ss << int_to_int(nbDec);
    string str_final = ss.str();
    return str_final;
}


/*
* a partir de la dest du comp et du jump va creer le code binnaire
* utilisation de la classe TabConvert ou sont resengner les equivalences
*/
string CInstruct(char listPars[3][7]){
    stringstream ss;
    //ss << "111";
    string temp = listPars[1];
    
    TabConvert tab_convert = TabConvert();
    
    ss << tab_convert.compToBin(temp);

    temp.clear();
    temp.assign(listPars[0]);

    if(temp.find("A") != string::npos){
        ss << '1';
    }else
    {
        ss << '0';
    }    
    if(temp.find("D") != string::npos){
        ss << '1';
    }else
    {
        ss << '0';
    }
    if(temp.find("M") != string::npos){
        ss << '1';
    }else
    {
        ss << '0';
    }

    temp.clear();
    temp.assign(listPars[2]);

    if(temp.empty()){
        ss << "000";
    }else{
        ss << tab_convert.jumpToBin(temp);    
    }
    // cout <<  ss.str() << "  " << temp  << endl;
    return ss.str();

}

/*
* convertie les lignes d'assembler en code binaire
* definie deja si c'est une A instruction ou une C instruction
* puis renvoie a des fonctions pour finir de les convertir en binaire
*/
vector<std::string> assToBin(vector<std::string>* pt_listAss){

    vector<std::string> v;

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
            while (*it_line != '=' && *it_line != ';')
            {
                if(*it_line != ' ' && (int)*it_line != 13){ // pour ne prendre vraiment que l'instruction
                    temp[a] = *it_line;
                    a++;
                }
                it_line++;
            }
            
            if(*it_line == '='){ // si il y a bien une partie destination
                memcpy(listParse[0], temp, a);
                memset(temp, 0, 7);
                a = 0;
                it_line ++; // on va apres le egal
            }else if(*it_line == ';'){ //si il n'a pas de parti destination, on met le dans la partie comp au lieu de dest et o laisse au ; pour pas que c continue
                memcpy(listParse[1], temp, a);
                // memset(temp, 0, 7); // on met pas a zeros car on va le remetre dans la memoire apres
                a = 0;
            }

            while (*it_line != ';' && *it_line){
                if(*it_line != ' ' && (int)*it_line != 13){ // pour ne prendre vraiment que l'instruction
                    temp[a] = *it_line;
                    a++;
                }
                it_line++;
            }
            memcpy(listParse[1], temp, a);
            
            if(!*it_line){
                memcpy(listParse[2], "", 7);
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
        // std::cout << instBin << std::endl;
        v.push_back(instBin);
    }
    return v;
}

/*
* enregistre le resultat de la converstion dans un fichier
*/
void saveToFile(std::vector<std::string> v, const char* name){
    
    std::ofstream file(name);
    std::vector<std::string>::iterator it = v.begin();
    for(it; it != v.end(); it++){
        file << *it << std::endl;
    }
}


int main(int argc, char** argv){

    if(argc < 2){
        std::cout << "usage: " << argv[0] << " Xxx.asm" << endl;
        return -1;
    }

    InstructionList instructionList(argv[1]);
    

    instructionList.parse();


    std::vector<std::string> v = assToBin(instructionList.getVector());

    saveToFile(v, instructionList.getName().c_str());
    //instructionList.print();

}

