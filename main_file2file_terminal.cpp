#include <string>
#include <iostream>
#include <vector>
#include "File_interaction.h"
#include "readcreatefileenc.h"

int main(int argc, char ** argv) {

    bool add_separator = false;
    std::string pattern, TypeOfMethod, password, TypeOfOperation;
    TypeOfMethod = argv[1];
    password = argv[2];
    TypeOfOperation = argv[3];
    pattern = argv[4];

    int aenc = std::stoi(TypeOfOperation); 
    std::string input_message = readfile(pattern, aenc);
    std::string output_message = transformation_message(TypeOfMethod, password, TypeOfOperation, input_message);

    
    if (!output_message.empty()) {
        // std::cout << input_massage << std::endl;
        createEncfile(pattern, output_message, aenc);
    }

    return 0;
}