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

// Graph Algorithms
std::vector<std::vector<int>> findConnected(const std::vector<std::unordered_set<int>>& graph);
std::vector<std::vector<int>> findStronglyConnected(const std::vector<std::unordered_set<int>>& graph);
std::pair<int, int> graphlet3(const std::vector<std::unordered_set<int>>& graph);
std::pair<std::vector<int>, std::vector<int>> inoutDegrees(const std::vector<std::unordered_set<int>>& graph);

// Helpers
std::vector<std::unordered_set<int>> toUndirected(const std::vector<std::unordered_set<int>>& graph);
