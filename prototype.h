#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

#include <iostream>
#include <vector>
#include <stack>
#include "espece.h"
#include "graphe.h"

class Graphe;

void Kosaraju(Graphe monGraphe);
void fillorder(Espece v,std::stack<Espece> pile1);
Graphe transposition(Graphe monGraphe);
void DFS(Graphe monGraphe, int v);

#endif // PROTOTYPE_H_INCLUDED