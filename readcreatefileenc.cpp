#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "readcreatefileenc.h"

std::string readfile(const std::string& pattern, int aenc) {

    if ( aenc !=1 && aenc != 2) {
        throw std::runtime_error("Unknown operation");
    }
    std::vector<std::string> foundFiles;

    std::string searchStr = (aenc == 1) ? "notenc" : "enc";

    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        std::string name = entry.path().filename().string();

        if (name.find(searchStr) == std::string::npos)
            continue;

        if (name.find(pattern) == std::string::npos)
            continue;

        if (entry.path().extension() != ".txt")
            continue;

        foundFiles.push_back(name);
    }

    if (foundFiles.empty()) {
        throw std::runtime_error("No files with such name");
    }
    if (foundFiles.size() > 1) {
        throw std::runtime_error("More than one files with such name");
    }

    std::string inputFile = foundFiles[0];

    std::ifstream fin(inputFile);
    if (!fin) {
        throw std::runtime_error("Failed to open file");
    }

    std::string input_massage;
    fin >> input_massage; 
    fin.close();

    return input_massage;
}

void createEncfile(const std::string& pattern, const std::string& output_massage, int aenc) {
    if ( aenc !=1 && aenc != 2) {
        throw std::runtime_error("Unknown operation");
    }
    
    
    std::vector<std::string> foundFiles;
    std::string sttr = (aenc == 1) ? "notenc" : "enc";

    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        std::string name = entry.path().filename().string();

        if (name.find(sttr) == std::string::npos)
            continue;

        if (name.find(pattern) == std::string::npos)
            continue;

        if (entry.path().extension() != ".txt")
            continue;

        foundFiles.push_back(name);
    }

    if (foundFiles.empty()) {
        throw std::runtime_error("No files with such name");
    }
    if (foundFiles.size() > 1) {
        throw std::runtime_error("More than one files with such name");
    }

    std::string inputFile = foundFiles[0];

    std::string outputFile = inputFile;
    if (aenc == 1) { 
        size_t pos = outputFile.find("notenc");
        if (pos != std::string::npos) {
            outputFile.replace(pos, 6, "enc");
        }
    } else {
        size_t pos = outputFile.find("enc");
        if (pos != std::string::npos) {
            outputFile.replace(pos, 3, "notenc");
        }
    }

    std::ofstream fout(outputFile);
    if (!fout) {
        throw std::runtime_error("Failed to create file");
    }

    fout << output_massage;
    fout.close();

    std::cout << "File: " << outputFile << " created" << std::endl;
}

