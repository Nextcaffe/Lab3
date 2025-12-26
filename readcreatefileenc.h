#ifndef READCREATEFILEENC_H
#define READCREATEFILEENC_H

#include <string>

std::string readfile(const std::string& pattern, int aenc);
void createEncfile(const std::string& pattern, const std::string& output_massage, int aenc);

#endif //READCREATEFILEENC_H