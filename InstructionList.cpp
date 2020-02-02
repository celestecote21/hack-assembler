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

    InstructionList::init_symbol();  

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
    symbole();
}


void InstructionList::symbole(){
    int next_var_addr = 16;
    std::vector<std::string>::iterator it_v = listInstrinction.begin();

    /*
    * premiere passe pour trouver tout les symbole de Goto et les mettres dans la map des symboles
    */
    for(int current_line = 0; it_v != listInstrinction.end(); it_v++){
        std::string temp(*it_v);
        if(temp.at(0) == '('){
           
            std::string sym;
            for(int a = 1; temp.at(a) != ')'; a ++){
                sym += temp.at(a);
            }
            if(map_symbole.find(sym) == map_symbole.end()){ //si la reference n'est pas trouver
                map_symbole[sym] = current_line;
               current_line --; // on enleve une ligne car en fin de compte la ligne ou on declare les symbole sont pas compter
               listInstrinction.erase(it_v); // supression de la ligne dans la liste des instructions
               it_v--;
               //for_each(map_symbole.begin(), map_symbole.end(), [](std::pair<std::string, int> str){std::cout << str.second << std::endl;});
            }
        }
        
        
        current_line++;
    }
    /*
    * deuxieme passe ou on va changer tout les symboles par leur nombre qu'il faut
    */
    //InstructionList::print();
    it_v = listInstrinction.begin();
    for(int current_line = 0; it_v != listInstrinction.end(); it_v++){
        std::string temp(*it_v);

        if(temp.at(0) == '@'){
            temp.erase(temp.begin());
            // std::cout << "str : " <<  temp << std::endl;

            if((int)temp.at(0) >= 48 &&  (int)temp.at(0) <= 57){ // si c'est directement une addresse C'est bon

            }else{ // c'est pas directement une addresse
                std::string sym;
                for(int a = 0; (int)temp.at(a) > 30; a ++){ // prend que des caractere imprimable
                    sym += temp.at(a);
                    //std::cout << (int)temp.at(a);
                }                

                if(map_symbole.find(sym) == map_symbole.end()){ //si la reference n'est pas trouver
                    map_symbole[sym] = next_var_addr;
                    std::stringstream aa;
                    aa << "@";
                    aa << next_var_addr;
                    it_v->assign(aa.str());
                    next_var_addr++;
                    
                }else{
                    std::stringstream aa;
                    aa << "@";
                    aa << map_symbole.find(sym)->second;
                    it_v->assign(aa.str());
                }
            }
        }
    }
    //InstructionList::print();
}


void InstructionList::init_symbol(){
    std::stringstream ss;
    
    for(int s = 0; s < 16; s++){ // mise en place des register r0 a r15
        ss << 'R' << s;
        map_symbole[ss.str()] = s;
        ss.clear();
    }
    
    map_symbole["SP"] = 0;
    map_symbole["LCL"] = 1;
    map_symbole["ARG"] = 2;
    map_symbole["THIS"] = 3;
    map_symbole["THAT"] = 4;

    map_symbole["SCREEN"] = 16384;
    map_symbole["KBD"] = 24576;

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

std::string InstructionList::getName(){
    std::string result = _fileName;
    result += "hack";
    return result;
}