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

/*! \brief Fonction de calcul avec l'algorithme Kosaraju
 */

/// Algorithme Kosaraju
void Kosaraju(Graphe *monGraphe, std::vector<std::vector<int>> &compo);
void fillorder(Graphe *monGraphe,Espece *v,std::stack<Espece*> &pile1);
/// Fonction pour inverser le sens des fleches du graphe
Graphe* transposition(Graphe *graf);
/// Fonction permettant de faire un DFS sur une composante connexe
void DFS(Graphe *monGraphe, int v,std::vector<int> &connexe);
/// Fonction qui colorise les composantes fortement connexes du graphe
void color(Graphe *monGraphe, std::vector<std::vector<int>> &compo);

#endif // PROTOTYPE_H_INCLUDED
