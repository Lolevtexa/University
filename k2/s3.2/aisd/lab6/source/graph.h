#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>

class Graph {
private:
    int numSubjects;
    std::vector<std::vector<int>> adjList;
    std::vector<int> inDegree;

public:
    Graph(int num);
    void addEdge(int subject1, int subject2);
    bool topologicalSort(std::vector<int>& result);
    void displayGraph();
};

#endif // GRAPH_H
