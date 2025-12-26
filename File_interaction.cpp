#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include "Cryptographer.h"
#include "File_interaction.h"


Text uint8_to_text(uint8_t x) {
    std::vector<Text> hex = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    Text new_x;
    new_x = hex[x/16] + hex[x%16];
    return new_x;
}

Text Data_to_Text(const Data& data) {
    Text text;
    for (size_t i = 0; i < data.size(); i++) {
        text += (uint8_to_text(data[i]));
    }
    return text;
}


uint8_t text_to_uint8(const Text& x, size_t pos) {
    if (pos + 2 > x.size()) {
        throw std::runtime_error("text_to_uint8 invalid position");
    }
    uint8_t new_x = 0;
    for (int i = 0; i < 2; i++) {
        uint8_t tmp = x[i + pos];
        if (tmp >= 'A') {
            tmp -= 'A';
            tmp += 10;
        } else {
            tmp -= '0';
        }
        new_x = (new_x << 4) + tmp;
    }
    return new_x;
}

Data Text_to_Data(const Text& text) {
    Data new_data;
    for (size_t pos = 0; pos < text.size(); pos+=2) {
        new_data.push_back(text_to_uint8(text, pos));
    }
    return new_data;
}




// Data2 Text_to_Data2(const Text& text) {
//     Data2 data;
//     for (size_t i = 0; i < text.size(); i += 2) {
//         Text tmp(text.begin()+i, text.begin()+i+2);
//         data.push_back(tmp);
//     }
//     return data;
// }

Text transformation_message(const Text& TypeOfMethod, const Text& password, 
    const Text& TypeOfOperation, const Text& input_message) {
    
    CryptoType type = parseCryptoType(TypeOfMethod);
    Data password_vector = {password.begin(), password.end()};
    std::shared_ptr<ICrypto> pCrypto = makeCrypto(type, password_vector);
    
    if (TypeOfOperation == "1") {
        Data data = {input_message.begin(), input_message.end()};
        Data output = pCrypto->encode(data);
        Text output_message = Data_to_Text(output);
        return output_message;
    } else if (TypeOfOperation == "2") {
        if (input_message.size() % 2 != 0) {
            throw std::runtime_error("Invalid input message to decode");
        }
        Data data = Text_to_Data(input_message);
        
        Data output = pCrypto->decode(data);
        Text output_message(output.begin(), output.end());
        return output_message;
    } else {
        throw std::runtime_error("Unknown operation");
    }
    // std::string encryptedText(encrypted.begin(), encrypted.end());

}

