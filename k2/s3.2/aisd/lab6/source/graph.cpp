#include "graph.h"

Graph::Graph(int num) : numSubjects(num), adjList(num), inDegree(num, 0) {}

void Graph::addEdge(int subject1, int subject2) {
    adjList[subject2].push_back(subject1);
    inDegree[subject1]++;
}

bool Graph::topologicalSort(std::vector<int>& result) {
    std::queue<int> q;
    for (int i = 0; i < numSubjects; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int visitedCount = 0;

    while (!q.empty()) {
        int subject = q.front();
        q.pop();
        result.push_back(subject);

        for (int next : adjList[subject]) {
            inDegree[next]--;
            if (inDegree[next] == 0) {
                q.push(next);
            }
        }

        visitedCount++;
    }

    return visitedCount == numSubjects;
}

void Graph::displayGraph() {
    for (int i = 0; i < numSubjects; ++i) {
        std::cout << "Subject " << i << ": ";
        for (int j : adjList[i]) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}
