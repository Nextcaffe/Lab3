#ifndef FILE_INTERACTION_H
#define FILE_INTERACTION_H

#include <memory>
#include <string>
#include "Cryptographer.h"

using Data = std::vector<uint8_t>;
using Text = const std::string&;

CryptoType parseCryptoType(const std::string& type);
Data transformation_message(Text TypeOfMethod, Text password, Text TypeOfOperation, Text input_message);

#endif //FILE_INTERACTION_H