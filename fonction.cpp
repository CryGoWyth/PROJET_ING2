#include <iostream>
#include <vector>
#include <stack>
#include "espece.h"
#include "graphe.h"
#include "arete.h"
#include "widgets.h"
#include "prototype.h"

void Kosaraju(Graphe *mongraphe)
{
    std::stack<Espece*> pile;

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

    for(auto elem: transpo->get_especes())
    {
        elem->set_marque(false);
    }



    while(pile.empty()==false)  //Tant que la pile n'est pas vide
    {
        ///Espece v = pile.top();
        //std::cout << "Taille pile second test " << pile.size() << std::endl;
        int v=0;
        v=pile.top()->get_numS();
        pile.pop();



        if(transpo->get_especes()[v]->get_marque()==false)
        {

            DFS(transpo,v);
            //std::cout << "Sortie du gros DFS ";
            std::cout << std::endl << std::endl << std::endl;

        }


    }



}

void fillorder(Graphe *monGraphe,Espece *v,std::stack<Espece*> &pile1)
{
    int numero=-1;

    ///On marque le sommet
    v->set_marque(true);
    ///On marque les sommets adjacents

    std::vector<Arete*> apple=v->get_predateurs();
    if(v->get_predateurs().size()!=0){
    for(auto elem : apple)
    {



            numero=elem->get_first()->get_nb();


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

void DFS(Graphe *graf,int v)
{


    graf->get_especes()[v]->set_marque(true);
     std::cout << v << " ";



    std::vector<Arete*> tomato=graf->get_especes()[v]->get_predateurs();
    std::vector <Arete*> reverse_tomato=graf->get_especes()[v]->get_proies();
    int numero=-1;
    std::cout << "Taille tomato: " << tomato.size() << " ";
    if(tomato.size()!=0 && reverse_tomato.size()!=0){



        for(auto elem: tomato)
        {

            numero=elem->get_first()->get_nb();

                if(graf->get_especes()[numero]->get_marque()==false && tomato.size()!=0 ){
                    DFS(graf,numero);
                }else{
                    return;

                    }
            /*numero=elem->get_second()->get_nb();
            if(graf->get_especes()[numero]->get_marque()==false)
                DFS(graf,numero);*/
        }

    }



}
