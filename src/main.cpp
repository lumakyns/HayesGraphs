#include "main.hpp"

int main() {

    // Put graph name + file path here
    const std::vector<std::pair<std::string, std::string>> graphPaths = {
        {"n10", "resources/graphs/n10.txt"},
        {"n100", "resources/graphs/n100.txt"},
        {"n1000", "resources/graphs/n1000.txt"},
        {"n10000", "resources/graphs/n10000.txt"},
        {"s1", "resources/graphs/s1.txt"}
    };

    for (const std::pair<std::string, std::string>& dataset : graphPaths) {

        std::vector<std::unordered_set<int>> graph = filepathToGraph(dataset.second);

        DataResults data;
        data.fileName            = dataset.first;
        data.filePath            = dataset.second;
        data.CCResults           = findConnected(graph);
        data.SCCResults          = findStronglyConnected(graph);
        data.size3graphlets      = graphlet3(graph);
        data.directedIODegrees   = inoutDegrees(graph);
        data.undirectedIODegrees = inoutDegrees(toUndirected(graph));

        printMyData(data);
        // exportMyData(data, FolderPath);
    }
    
    return 0;
}

void printMyData(const DataResults& data) {
    // Statistics
    std::cout << "**** " << data.fileName << " ****\n";
    std::cout << "  CC   : " << data.CCResults.size() << "\n";
    std::cout << "  SCC  : " << data.SCCResults.size() << "\n";
    std::cout << "  GR3  : " << "(Lines: " << data.size3graphlets.first << ") -- (Triangles : " << data.size3graphlets.second << ")" << "\n\n";

    // Degrees
    std::cout << "  Degree distributions:\n";
    std::cout << "     ______ ______ ______\n";
    std::cout << "    |INdeg |OUTdeg|Undir |\n";

    int maxLen = std::max(data.directedIODegrees.first.size(), data.undirectedIODegrees.first.size());
    for (int id = 0; id < maxLen; ++id) {

        std::cout << std::setw(4) << id << "|";

        if (id >= data.directedIODegrees.first.size()) std::cout << std::setw(6) << 0 << "|";
        else                                           std::cout << std::setw(6) << data.directedIODegrees.first[id] << "|";

        if (id >= data.directedIODegrees.second.size()) std::cout << std::setw(6) << 0 << "|";
        else                                            std::cout << std::setw(6) << data.directedIODegrees.second[id] << "|";

        if (id >= data.undirectedIODegrees.first.size()) std::cout << std::setw(6) << 0 << "|\n";
        else                                             std::cout << std::setw(6) << data.undirectedIODegrees.first[id] << "|\n";
    }
    std::cout << "     ______ ______ ______\n";
    std::cout << "\n\n";
}

void exportMyData(const DataResults& data, std::string CSVFolderPath) {

    // Find and create folder
    try {
        std::filesystem::create_directories(CSVFolderPath);
    }

    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Failed to create directory: " << e.what() << "\n";
        return;
    }
    
    std::filesystem::path statsPath   = std::filesystem::path(CSVFolderPath) / (data.fileName + "_stats.csv");
    std::filesystem::path degreesPath = std::filesystem::path(CSVFolderPath) / (data.fileName + "_degrees.csv");
    
    // Write statistics file
    std::ofstream statsFile(statsPath);
    if (!statsFile.is_open()) {
        std::cerr << "Could not open file: " << statsPath << std::endl;
        return; 
    }

    statsFile << "CC,SCC,GR3Lines,GR3Triangles\n";
    statsFile << data.CCResults.size() << "," << data.SCCResults.size() << "," << data.size3graphlets.first << "," << data.size3graphlets.second << "\n";
    statsFile.close();

    // Write degrees file
    std::ofstream degreeFile(degreesPath);
    if (!degreeFile.is_open()) {
        std::cerr << "Could not open file: " << degreesPath << std::endl;
        return; 
    }

    degreeFile << "IN,OUT,UNDIR\n";
    int maxLen = std::max(data.directedIODegrees.first.size(), data.undirectedIODegrees.first.size());
    for (int id = 0; id < maxLen; ++id) {

        if (id >= data.directedIODegrees.first.size()) degreeFile << "0" << ",";
        else                                           degreeFile << data.directedIODegrees.first[id] << ",";

        if (id >= data.directedIODegrees.second.size()) degreeFile << "0" << ",";
        else                                            degreeFile << data.directedIODegrees.second[id] << ",";

        if (id >= data.undirectedIODegrees.first.size()) degreeFile << "0" << "\n";
        else                                             degreeFile << data.undirectedIODegrees.first[id] << "\n";
    }
    degreeFile.close();
}
