# Graph Algorithms for Prof. Hayes #
This repository contains some graph algorithms.

### Algorithms available ###
- Finding Connected Components
- Finding Strongly Connected Components (Tarjan's)
- Size 3 Graphlet finder

### Graph Format (in resources/graphs) ###
- 1st line     : # of vertices in graph, N.
- Rest of lines: A directed edge between two numbered vertices [0, N-1], separated by a single space

EG. <br/>
3   <br/>
0 1 <br/>
0 2 <br/>
1 2 <br/>

### Notice ###
Due to possibly dealing with large amounts of data, and for speed, algorithms are implemented without recursion.