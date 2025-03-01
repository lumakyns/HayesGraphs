#include "graphHelpers.hpp"

// Parses a file (given by `const std::string& path`) and turns it into a graph.
std::vector<std::unordered_set<int>> filepathToGraph(const std::string& path) {
    
    // Opening file
    std::ifstream inputFile(path);
    if (!inputFile.good()) {
        throw std::runtime_error("(filepathToGraph) Invalid path: " + path);
    }

    // Loading
    int graphSize;
    std::string line;

    // Number of vertices
    if (!getline(inputFile, line)) {
        throw std::runtime_error("(filepathToGraph) File may be empty: " + path);
    }

    graphSize = std::stoi(line);
    std::vector<std::unordered_set<int>> graph(graphSize);

    // Edges
    while (getline(inputFile, line)) {
        auto split = line.find(" ");
        int lhs    = std::stoi(line.substr(0, split));
        int rhs    = std::stoi(line.substr(split + 1));
        graph[lhs].insert(rhs);
    }

    return graph;
}

// Finds connected components in a graph using a regular DFS algorithm
std::vector<std::vector<int>> findConnected(const std::vector<std::unordered_set<int>>& graph) {
    std::vector<std::unordered_set<int>> undirectedGraph(graph.size());

    // Turn digraph into undirected graph
    for (int from = 0; from < graph.size(); ++from) {
        for (const int to : graph[from]) {
            undirectedGraph[from].insert(to);
            undirectedGraph[to].insert(from);
        }
    }

    // Find all connected components
    std::vector<std::vector<int>> connectedComponents;
    std::vector<bool>             found(graph.size(), false);
    std::stack<int>               DFSStack;

    for (int vert = 0; vert < graph.size(); ++vert) {
        if (!found[vert]) {
            connectedComponents.push_back({});
            DFSStack.push(vert);
            std::vector<int>* newComponent = &connectedComponents[connectedComponents.size()-1];

            // Run DFS to find all components connected to `vert`
            while (!DFSStack.empty()) {
                int currentVert = DFSStack.top();
                DFSStack.pop();

                if (found[currentVert]) continue;
                else found[currentVert] = true;

                newComponent->push_back(currentVert);
                for (const int neighbor : undirectedGraph[currentVert]) {
                    DFSStack.push(neighbor);
                }
            }
        }
    }

    return connectedComponents;
}

// Finds strongly connected components in a graph using Tarjan's algorithm
std::vector<std::vector<int>> findStronglyConnected(const std::vector<std::unordered_set<int>>& graph) {
    
    // Run Tarjan's algorithm
    // 1. Assign each vertex a number, based on the order it was found in a DFS search.
    // 2. Once a vertex explores all its children, check the lowest-order-number vertex it can reach (That isn't in a SCC).
    // 3. If that lowest-order-number is its own order number, create a SCC (Using a stack to remember which nodes were reached)
    std::vector<int> orderFound(graph.size(), -1);
    std::vector<int> lowestFound(graph.size(), -1);
    std::stack<int>  traversalStack;
    int              orderNumber = 0;

    std::vector<std::vector<int>>    stronglyConnectedComponents;
    std::stack<std::pair<int, bool>> DFSStack;
    
    for (int vert = 0; vert < graph.size(); ++vert) {
        if (orderFound[vert] == -1) {
            DFSStack.push({vert, true});

            // Run Tarjan's algorithm starting at `vert`
            while (!DFSStack.empty()) {
                int  currentVert = DFSStack.top().first;
                bool firstTime   = DFSStack.top().second;
                
                // Assign value to new vertex if needed.
                if (firstTime && orderFound[currentVert] != -1) {
                    DFSStack.pop();
                    continue;
                }

                if (firstTime) orderFound[currentVert] = lowestFound[currentVert] = orderNumber++;

                // Case 1: First time seeing this node -> Explore children.
                if (firstTime) {
                    traversalStack.push(currentVert);
                    DFSStack.top().second = false;

                    for (const int neighbor : graph[currentVert]) {
                        DFSStack.push({neighbor, true});
                    }

                    continue;
                }

                // Case 2: Build SCC if appropriate.
                else {
                    // Get the lowest-order-number reachable from children.
                    for (const int neighbor : graph[currentVert]) {
                        if (orderFound[neighbor] == -2) continue; // Neighbor is part of existing SCC
                        
                        lowestFound[currentVert] = std::min(lowestFound[currentVert], lowestFound[neighbor]);
                    }

                    // Create SCC if the lowest-order-number is our own number.
                    if (orderFound[currentVert] == lowestFound[currentVert]) {
                        stronglyConnectedComponents.push_back({});
                        std::vector<int>* newSCC = &stronglyConnectedComponents[stronglyConnectedComponents.size()-1];

                        while (traversalStack.top() != currentVert) {
                            newSCC->push_back(traversalStack.top());
                            orderFound[traversalStack.top()] = -2;
                            traversalStack.pop();
                        }

                        newSCC->push_back(currentVert);
                        orderFound[currentVert] = -2;
                        traversalStack.pop();
                    }

                    DFSStack.pop();
                }
            }
        }
    }

    return stronglyConnectedComponents;
}

// Returns a histogram of the in-out degrees for the graph.
// pair.first  = in degrees
// pair.second = out degrees
std::pair<std::vector<int>, std::vector<int>> inoutDegrees(const std::vector<std::unordered_set<int>>& graph) {
    std::vector<int> ins;
    std::vector<int> outs;

    std::vector<int> indegPerVertex(graph.size(), 0);
    std::vector<int> outdegPerVertex(graph.size(), 0);

    // Get values
    for (int vert = 0; vert < graph.size(); ++vert) {
        outdegPerVertex[vert] += graph[vert].size();

        for (const int neighbor : graph[vert]) {
            ++indegPerVertex[neighbor];
        }
    }

    // Bucketize
    for (int id = 0; id < graph.size(); ++id) {
        while (ins.size()  <= indegPerVertex[id])  ins.push_back(0);
        while (outs.size() <= outdegPerVertex[id]) outs.push_back(0);

        ++ins[indegPerVertex[id]];
        ++outs[outdegPerVertex[id]];
    }

    // Make lengths equal
    int maxLen = std::max(ins.size(), outs.size());
    while (ins.size()  < maxLen) ins.push_back(0);
    while (outs.size() < maxLen) outs.push_back(0);

    return {ins, outs};
}
