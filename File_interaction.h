#ifndef FILE_INTERACTION_H
#define FILE_INTERACTION_H

#include <memory>
#include <string>
#include "Cryptographer.h"

using Text = std::string;

Text transformation_message(const Text& TypeOfMethod, const Text& password, 
    const Text& TypeOfOperation, const Text& input_message);

#endif //FILE_INTERACTION_H