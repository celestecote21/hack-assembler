#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>

class InstructionList
{
private:
    std::ifstream fileAssembler;
    std::vector<std::string> listInstrinction;
    std::string _fileName;
    std::map<std::string, int> map_symbole;
public:
    InstructionList(std::string fileName);
    ~InstructionList();
    void parse();
    void symbole();
    void init_symbol();
    void print();
    std::vector<std::string>* getVector();
    std::string getName();

};


