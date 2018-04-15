#include <iostream>
#include <vector>
#include <stack>
#include "espece.h"
#include "graphe.h"
#include "arete.h"
#include "widgets.h"
#include "prototype.h"

void Kosaraju(Graphe *mongraphe,std::vector<std::vector<int>> &compo)
{
    std::vector<int> connexe;
    std::stack<Espece*> pile;
    int i=1;

    ///On enleve la marque de tous les sommets du graphe au cas ou
    for(auto elem : mongraphe->get_especes())
        elem->set_marque(false);


    ///On rempli la pile par ordre de fin de marquage des sommets
    for(auto elem: mongraphe->get_especes())
    {
        if(elem->get_marque()==false)
        {
            fillorder(mongraphe,elem,pile);
        }
    }

    ///On creer un graphe similaire a G sauf que l'on a inverse l'orientation des aretes

    ///On enleve la marque de tous les sommets du graphe
    for(auto elem: mongraphe->get_especes())
        elem->set_marque(false);

    while(pile.empty() == false)
    {
        int v = pile.top()->get_numS();
        pile.pop();

        if(mongraphe->get_especes()[v]->get_marque()==false)
        {
            DFS(mongraphe,v,connexe);

            if(connexe.size()>2)
                compo.push_back(connexe);
            connexe.erase(connexe.begin(),connexe.end());
            i++;
        }
    }
}

void fillorder(Graphe *monGraphe,Espece *v,std::stack<Espece*> &pile1)
{
    int numero=-1;

    ///On marque le sommet
    v->set_marque(true);
    ///On marque les sommets adjacents

    std::vector<Arete*> apple=v->get_proies();
    if(v->get_proies().size()!=0){
        for(auto elem : apple){
            numero=elem->get_second()->get_nb();
            if(monGraphe->get_especes()[numero]->get_marque()==false)
                fillorder(monGraphe,monGraphe->get_especes()[numero],pile1);
        }
    }

    ///On stocke les sommets dans la Pile

    if(v->get_numS() < monGraphe->get_especes().size())
        pile1.push(v);
}

Graphe* transposition(Graphe *mongraphe)
{
    Graphe *M(mongraphe);
    int v=0;
    for(auto &elem : M->get_aretes()){
        elem->set_first(mongraphe->get_aretes()[v]->get_second());
        elem->set_second(mongraphe->get_aretes()[v]->get_first());
        v++;
    }
    return M;
}

void DFS(Graphe *graf,int v,std::vector<int> &connexe)
{
    graf->get_especes()[v]->set_marque(true);
    connexe.push_back(v);
    std::vector<Arete*> tomato=graf->get_especes()[v]->get_predateurs();
    std::vector <Arete*> reverse_tomato=graf->get_especes()[v]->get_proies();
    int numero=-1;

    for(auto elem: tomato){
        numero=elem->get_first()->get_nb();
        if(graf->get_especes()[numero]->get_marque()==false)
            DFS(graf,numero,connexe);
    }
}

void color(Graphe *monGraphe, std::vector<std::vector<int>> &compo)
{
    for(auto elem: compo){
        for(int v=0; v<elem.size(); v++){
            for(int i=0; i<monGraphe->get_especes()[elem[v]]->get_predateurs().size(); i++){
                for(int j=0; j<elem.size();j++){
                    if(monGraphe->get_especes()[elem[v]]->get_predateurs()[i]->get_second()->get_nb()==elem[j])
                        monGraphe->get_especes()[elem[v]]->get_predateurs()[i]->set_couleur_compo(1);
                }
            }
        }
    }
}
