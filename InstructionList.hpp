#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class InstructionList
{
private:
    std::ifstream fileAssembler;
    std::vector<std::string> listInstrinction;
    std::string _fileName;
public:
    InstructionList(std::string fileName);
    ~InstructionList();
    void parse();
    void print();
    std::vector<std::string>* getVector(); 

};


