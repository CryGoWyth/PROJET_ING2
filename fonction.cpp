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

    ///On enleve la marque de tous les sommets du graphe au cas où
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


    ///On créer un graphe similaire à G sauf que l'on a inversé l'orientation des aretes
    Graphe *transpo(transposition(mongraphe));

    ///On enlève la marque de tous les sommets du graphe
    for(auto elem: mongraphe->get_especes())
        elem->set_marque(false);



    while(pile.empty()==false)  //Tant que la pile n'est pas vide
    {
        ///Espece v = pile.top();
        //std::cout << "Taille pile second test " << pile.size() << std::endl;
        int v=0;
        v=pile.top()->get_numS();
        pile.pop();



        if(transpo->get_especes()[v]->get_marque()==false)
        {

            DFS(transpo,v,connexe);
            //std::cout << "Sortie du gros DFS ";
            std::cout << " i= " << i << std::endl << std::endl << std::endl;
            if(connexe.size()>2)
            {
                compo.push_back(connexe);
            }
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
    if(v->get_proies().size()!=0)
    {
        for(auto elem : apple)
        {



            numero=elem->get_second()->get_nb();


            if(monGraphe->get_especes()[numero]->get_marque()==false)
            {

                fillorder(monGraphe,monGraphe->get_especes()[numero],pile1);

            }


        }
    }

    ///On stocke les sommets dans la Pile

    if(v->get_numS() < monGraphe->get_especes().size())
    {
        std::cout << "Sommet: " << v->get_numS() << std::endl;
        pile1.push(v);
    }


}

Graphe* transposition(Graphe *mongraphe)
{
    Graphe *M(mongraphe);

    for(auto &elem : M->get_aretes())
    {
        elem->set_first(elem->get_second());
        elem->set_second(elem->get_first());
    }

    return M;
}

void DFS(Graphe *graf,int v,std::vector<int> &connexe)
{


    graf->get_especes()[v]->set_marque(true);
    std::cout << v << " ";
    connexe.push_back(v);



    std::vector<Arete*> tomato=graf->get_especes()[v]->get_predateurs();
    std::vector <Arete*> reverse_tomato=graf->get_especes()[v]->get_proies();
    int numero=-1;


    for(auto elem: tomato)
    {


        numero=elem->get_first()->get_nb();
        if(graf->get_especes()[numero]->get_marque()==false)
        {
            DFS(graf,numero,connexe);
        }


    }





}
