#include <iostream>
#include <fstream>
#include <string.h>
#include <random>
#include <string>
#include <program1.hxx>
#include <program2.hxx>

int main() { 
    CreateData cd;
    // std::cout << valid.validate(cd.second_stream());
    
    // std::string temp = "43243";
    // char* buffer = new char[temp.size() + 1];
    // strcpy(buffer, temp.c_str());

    std::ofstream ofs("../data.txt");
    std::srand(std::time(NULL));

    int i = 0;
    while(i++ < 10000) {
        unsigned long long val = rand() * -1;
        std::string str_val = std::to_string(val);
        while(str_val.size() < 63) {
            str_val += str_val[rand() % 10];
        }
        ofs << str_val << "\n";
    }

    ofs.close();

    std::ifstream ifs("../data.txt");
    std::string line;
    while (std::getline(ifs, line)) {
        std::string odd_hash = cd.first_stream(line);
        ValidateData valid(cd);
        int stream_value = cd.second_stream(odd_hash);
        valid.validate(stream_value);
    }
    
    ifs.close();
    
}