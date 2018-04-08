#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

#include <iostream>
#include <vector>
#include <stack>
#include "espece.h"
#include "graphe.h"
#include "arete.h"
#include "widgets.h"

class Graphe;

void Kosaraju(Graphe *monGraphe,std::vector<std::vector<int>> &compo) ;
void fillorder(Graphe *monGraphe,Espece *v,std::stack<Espece*> &pile1);
Graphe* transposition(Graphe *graf);
void DFS(Graphe *monGraphe, int v,std::vector<int> &connexe);

#endif // PROTOTYPE_H_INCLUDED
