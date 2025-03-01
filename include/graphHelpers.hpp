#pragma once

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>

// File Processing
std::vector<std::unordered_set<int>> filepathToGraph(const std::string& path);

// Connected Components
std::vector<std::vector<int>> findConnected(const std::vector<std::unordered_set<int>>& graph);

// Strongly Connected Components
std::vector<std::vector<int>> findStronglyConnected(const std::vector<std::unordered_set<int>>& graph);

// Vertex Degrees
std::pair<std::vector<int>, std::vector<int>> inoutDegrees(const std::vector<std::unordered_set<int>>& graph);
