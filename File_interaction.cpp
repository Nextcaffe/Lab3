#include <memory>
#include <stdexcept>
#include "Cryptographer.h"
#include "File_interaction.h"

Data transformation_message(Text TypeOfMethod, Text password, Text TypeOfOperation, Text input_message) {
    CryptoType type = parseCryptoType(TypeOfMethod);
    Data password_vector = {password.begin(), password.end()};
    std::shared_ptr<ICrypto> pCrypto = makeCrypto(type, password_vector);
    
    if (TypeOfOperation == "1") {
        Data output_message = pCrypto->encode({input_message.begin(), input_message.end()});
        return output_message;
    } else if (TypeOfOperation == "2") {
        Data output_message = pCrypto->encode({input_message.begin(), input_message.end()});
        return output_message;
    } else {
        throw std::runtime_error("Unknown operation");
    }
    // std::string encryptedText(encrypted.begin(), encrypted.end());

}

