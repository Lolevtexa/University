#ifndef UTILS_H
#define UTILS_H

#include "graph.h"

void displayMenu();
int getUserInput(const std::string& prompt);
void enterDependencies(Graph& graph);

#endif // UTILS_H
