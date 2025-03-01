#include "main.hpp"

int main() {

    // Graphs
    std::vector<std::pair<std::string, std::string>> graphPaths = {
        {"n10", "resources/graphs/n10.txt"},
        {"n100", "resources/graphs/n100.txt"},
        {"n1000", "resources/graphs/n1000.txt"},
        {"n10000", "resources/graphs/n10000.txt"},
        {"s1", "resources/graphs/s1.txt"}
    };

    // Print out results
    for (const std::pair<std::string, std::string>& dataset : graphPaths) {
        std::vector<std::unordered_set<int>> graph = filepathToGraph(dataset.second);
        std::vector<std::vector<int>> CCResults    = findConnected(graph);
        std::vector<std::vector<int>> SCCResults   = findStronglyConnected(graph);

        std::pair<std::vector<int>, std::vector<int>> IODegrees = inoutDegrees(graph);

        std::cout << "**** " << dataset.first << " ****\n";
        std::cout << "  CC   : " << CCResults.size() << "\n";
        std::cout << "  SCC  : " << SCCResults.size() << "\n";

        std::cout << "  IN-D :\n";
        for (int id = 0; id < IODegrees.first.size(); ++id) {
            std::cout << "    Deg. " << id << " -> " << IODegrees.first[id] << "\n";
        }

        std::cout << "  OUT-D:\n";
        for (int id = 0; id < IODegrees.second.size(); ++id) {
            std::cout << "    Deg. " << id << " -> " << IODegrees.second[id] << "\n";
        }

        std::cout << "\n\n";
    }
    
    return 0;
    
}
