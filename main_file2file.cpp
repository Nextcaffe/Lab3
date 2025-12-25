#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include "File_interaction.h"

int main()
{
    std::string TypeOfMethod, password, TypeOfOperation, input_message = "";
    //TypeOfMethod = ... тип кодировщика
    //password = ... ключ значение шифрования
    //TypeOfOperation = ... кодировка/декодировка (лучше "1" - кодировка, "2" - декодировка)
    //input_message = ... cтрока вытянутая из файла с входными данными
    
    auto output_message = transformation_message(TypeOfMethod, password, TypeOfOperation, input_message);

    // перенос output_message в файл с выходными данными
}