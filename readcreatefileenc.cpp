#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "readcreatefileenc.h"

std::string readfile(const std::string& pattern, int aenc) {
    if (aenc != 1 && aenc != 2) {
        throw std::runtime_error("Unknown operation");
    }
    std::vector<std::string> foundFiles;

    std::string searchStr = (aenc == 1) ? "input" : "output";

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
    if (aenc != 1 && aenc != 2) {
        throw std::runtime_error("Unknown operation");
    }
    
    std::vector<std::string> foundFiles;
    std::string sttr = (aenc == 1) ? "input" : "output";

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

    std::string baseOutputFile = inputFile;
    if (aenc == 1) { 
        size_t pos = baseOutputFile.find("input");
        if (pos != std::string::npos) {
            baseOutputFile.replace(pos, 5, "output");
        }
    } else {
        size_t pos = baseOutputFile.find("output");
        if (pos != std::string::npos) {
            baseOutputFile.replace(pos, 6, "input");
        }
    }

    std::string outputFile = baseOutputFile;

    std::string baseName = baseOutputFile.substr(0, baseOutputFile.find_last_of('.'));
    std::string extension = baseOutputFile.substr(baseOutputFile.find_last_of('.'));

    int counter = 1;
    while (std::filesystem::exists(outputFile)) {
        outputFile = baseName + " (" + std::to_string(counter++) + ")" + extension;
    }

    std::ofstream fout(outputFile);
    if (!fout) {
        throw std::runtime_error("Failed to create file");
    }

    fout << output_massage;
    fout.close();

    std::cout << "File: " << outputFile << " created" << std::endl;
}