#include "InstructionList.hpp"


using namespace std;

InstructionList::InstructionList(string fileName)
{
    fileAssembler.open(fileName);

    // donne le nom du ficher sans l'extension
    char c = ' ';
    int i = 0;
    while(c != '.'){
        c = fileName[i];
        _fileName += c;
        i++;
    }    

}

InstructionList::~InstructionList()
{
    fileAssembler.close();
}


void InstructionList::parse(){
    string line;
    string instruction;

    while (fileAssembler)
    {        
        getline(fileAssembler, line);
        if(line[0] != '/'){
            for(int j = 0; j < line.size(); j++){
                if( line[j] == '/'){
                    j = line.size(); // on arret de mettre dans l'instruction
                }
                if(line[j] != ' '){ // on met tout sauf les espaces 
                    instruction += line[j];
                }
            }
            if(instruction.size() > 2){ // on met pas dans la liste les instruction qui sont que des espaces
                listInstrinction.push_back(instruction);
            }
        }
        instruction.clear();

    }
    
}



void InstructionList::print(){

    for (int i = 0; i < listInstrinction.size(); i++)
    {
        cout << listInstrinction[i] << endl;
    }
    
}


vector<string>* InstructionList::getVector(){
    return &listInstrinction;
}