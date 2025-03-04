#pragma once

#include <iostream>
#include <iomanip>
#include <filesystem>

#include "graphHelpers.hpp"

struct DataResults {
    std::string fileName;
    std::string filePath;
    std::vector<std::vector<int>> CCResults;
    std::vector<std::vector<int>> SCCResults;
    std::pair<int, int> size3graphlets;
    std::pair<std::vector<int>, std::vector<int>> directedIODegrees;
    std::pair<std::vector<int>, std::vector<int>> undirectedIODegrees;
};

void printMyData(const DataResults& data);

void exportMyData(const DataResults& data, std::string CSVFolderPath);

