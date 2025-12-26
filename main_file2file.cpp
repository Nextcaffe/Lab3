#include <string>
#include <iostream>
#include <vector>
#include "File_interaction.h"
#include "readcreatefileenc.h"

// int main()
// {
//     std::string TypeOfMethod, password, TypeOfOperation, input_message = "";
//     //TypeOfMethod = ... тип кодировщика
//     //password = ... ключ значение шифрования
//     //TypeOfOperation = ... кодировка/декодировка (лучше "1" - кодировка, "2" - декодировка)
//     //input_message = ... cтрока вытянутая из файла с входными данными
    
//     auto output_message = transformation_message(TypeOfMethod, password, TypeOfOperation, input_message);

//     // перенос output_message в файл с выходными данными
// }

int main() {
    std::string pattern, TypeOfMethod, password, TypeOfOperation;
    
    std::cout << "Enter method of Cryptographer: ";
    std::getline(std::cin, TypeOfMethod, '\n');
    std::cout << "Enter password: ";
    std::getline(std::cin, password, '\n');
    std::cout << "Choose what to do:" << std::endl << "1 - encode, 2 - decode: ";
    std::getline(std::cin, TypeOfOperation, '\n');
    std::cout << "Enter a part or a full name of file for search: ";
    std::getline(std::cin, pattern, '\n');

    int aenc = std::stoi(TypeOfOperation); 
    std::string input_message = readfile(pattern, aenc);
    std::string output_message = transformation_message(TypeOfMethod, password, TypeOfOperation, input_message);

    
    if (!input_message.empty()) {
        // std::cout << input_massage << std::endl;
        createEncfile(pattern, output_message, aenc);
    }

    return 0;
}