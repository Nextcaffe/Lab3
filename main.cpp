#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "File_interaction.h"

int main()
{

    std::string TypeOfMethod, password, TypeOfOperation, input_message;
    std::cout << "Enter method of Cryptographer: ";
    std::getline(std::cin, TypeOfMethod, '\n');
    std::cout << "Enter password: ";
    std::getline(std::cin, password, '\n');
    std::cout << "Choose what to do:" << std::endl << "1 - encode, 2 - decode: ";
    std::getline(std::cin, TypeOfOperation, '\n');
    std::cout << "Enter message: ";
    std::getline(std::cin, input_message);

    auto output_message = transformation_message(TypeOfMethod, password, TypeOfOperation, input_message);

    if (TypeOfOperation == "1") {
        std::cout << "Encrypted message:" << std::endl;
    } else if (TypeOfOperation == "2") {
        std::cout << "Decrypted message:" << std::endl;
    } else {
        throw std::runtime_error("Unknown operation");
    }
    
    for (size_t i = 0; i < output_message.size(); i++) {
            std::cout << (int)output_message[i] << ' ';
        }
    std::cout << std::endl;


    
    return 0;
}
