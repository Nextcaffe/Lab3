#include <iostream>
#include <string>
#include <vector>
#include "File_interaction.h"

int main(int argc, char ** argv)
{
    bool add_separator = false;
    std::string TypeOfMethod, password, TypeOfOperation, input_message = "";
    TypeOfMethod = argv[1];
    password = argv[2];
    TypeOfOperation = argv[3];
    
    for (int i = 4; i < argc; i++) {
        input_message += argv[i];
    }

    std::string output_message = transformation_message(TypeOfMethod, password, TypeOfOperation, input_message);

    if (TypeOfOperation == "1") {
        std::cout << "Encrypted message:" << std::endl;
    } else if (TypeOfOperation == "2") {
        std::cout << "Decrypted message:" << std::endl;
    } else {
        throw std::runtime_error("Unknown operation");
    }
    
    for (size_t i = 0; i < output_message.size(); i++) {
        // std::cout << output_message[i] << std::setw(add_separator);
        std::cout << output_message[i];
    }
    std::cout << std::endl;

}
