#include <memory>
#include <stdexcept>
#include "Cryptographer.h"
#include "File_interaction.h"

Text Data2_to_Text(const Data2& data) {
    Text text;
    for (size_t i = 0; i < data.size(); i++) {
        text += data[i];
    }
    return text;
}

Data2 Text_to_Data2(const Text& text) {
    Data2 data;
    for (size_t i = 0; i < text.size(); i += 2) {
        Text tmp(text.begin()+i, text.begin()+i+2);
        data.push_back(tmp);
    }
    return data;
}

Text transformation_message(const Text& TypeOfMethod, const Text& password, 
    const Text& TypeOfOperation, const Text& input_message) {
    
    CryptoType type = parseCryptoType(TypeOfMethod);
    Data1 password_vector = {password.begin(), password.end()};
    std::shared_ptr<ICrypto> pCrypto = makeCrypto(type, password_vector);
    
    if (TypeOfOperation == "1") {
        Data1 data = {input_message.begin(), input_message.end()};
        Data2 output = pCrypto->encode(data);
        Text output_message = Data2_to_Text(output);
        return output_message;
    } else if (TypeOfOperation == "2") {
        if (input_message.size() % 2 != 0) {
            throw std::runtime_error("Invalid input message to decode");
        }
        Data2 data = Text_to_Data2(input_message);
        Data1 output = pCrypto->decode(data);
        Text output_message(output.begin(), output.end());
        return output_message;
    } else {
        throw std::runtime_error("Unknown operation");
    }
    // std::string encryptedText(encrypted.begin(), encrypted.end());

}

