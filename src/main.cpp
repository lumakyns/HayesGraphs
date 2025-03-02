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
        // Gather results
        std::vector<std::unordered_set<int>> graph = filepathToGraph(dataset.second);
        
        std::vector<std::vector<int>> CCResults    = findConnected(graph);
        std::vector<std::vector<int>> SCCResults   = findStronglyConnected(graph);
        std::pair<int, int> size3graphlets         = graphlet3(graph);

        std::pair<std::vector<int>, std::vector<int>> directedIODegrees   = inoutDegrees(graph);
        std::pair<std::vector<int>, std::vector<int>> undirectedIODegrees = inoutDegrees(toUndirected(graph));

        // Connected Components & Size-3 Graphlets
        std::cout << "**** " << dataset.first << " ****\n";
        std::cout << "  CC   : " << CCResults.size() << "\n";
        std::cout << "  SCC  : " << SCCResults.size() << "\n";
        std::cout << "  GR3  : " << "(Lines: " << size3graphlets.first << ") -- (Triangles : " << size3graphlets.second << ")" << "\n\n";

        // Degree distributions
        std::cout << "  Degree distributions:\n";
        std::cout << "     ______ ______ ______\n";
        std::cout << "    |INdeg |OUTdeg|Undir |\n";
   
        int maxLen = std::max(directedIODegrees.first.size(), undirectedIODegrees.first.size());
        for (int id = 0; id < maxLen; ++id) {

            std::cout << std::setw(4) << id << "|";

            if (id >= directedIODegrees.first.size()) std::cout << std::setw(6) << 0 << "|";
            else                                      std::cout << std::setw(6) << directedIODegrees.first[id] << "|";

            if (id >= directedIODegrees.second.size()) std::cout << std::setw(6) << 0 << "|";
            else                                       std::cout << std::setw(6) << directedIODegrees.second[id] << "|";

            if (id >= undirectedIODegrees.first.size()) std::cout << std::setw(6) << 0 << "|\n";
            else                                        std::cout << std::setw(6) << undirectedIODegrees.first[id] << "|\n";
        }
        std::cout << "     ______ ______ ______\n";
        std::cout << "\n\n";
    }
    
    return 0;
}
