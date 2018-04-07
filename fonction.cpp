#include "prototype.h"

void Kosaraju(Graphe mongraphe)
{
    std::stack<Espece> pile;

    ///On enleve la marque de tous les sommets du graphe au cas où
    for(auto elem : mongraphe.get_especes())
        elem->set_marque(false);

    std::cout << "Je suis dans la premiere etape de kosa" << std::endl << std::endl;
    ///On rempli la pile par ordre de fin de marquage des sommets
    for(auto elem: mongraphe.get_especes())
      fillorder(*elem,pile); ///Convertir proprement

    ///On créer un graphe similaire à G sauf que l'on a inversé l'orientation des aretes
    Graphe transpo(transposition(mongraphe));

    ///On enlève la marque de tous les sommets du graphe au cas où
    for(auto elem: transpo.get_especes())
        elem->set_marque(false);

    while(pile.empty()==false){ //Tant que la pile n'est pas vide
        ///Espece v = pile.top(); /// Ne fonctionne pas, RECODER POUR LE CREER CORRECTEMENT
        int v=pile.top().get_numS();

        if(pile.top().get_marque()==false){
            DFS(mongraphe,v);
            std::cout << std::endl << std::endl << std::endl;
        }
        pile.pop();
    }
}

void fillorder(Espece v,std::stack<Espece> pile1)
{

    ///On marque le sommet
    v.set_marque(true);
    std::cout << "Je suis dans fillorder" << std::endl << std::endl;

    ///On marque les sommets adjacents
    for(auto elem : v.get_adjacents()){
        std::cout << "Je suis dans la boucle for auto elem de fillorder" << std::endl;
        if(elem.get_marque()==false)
            fillorder(elem,pile1);
    }

    ///On stocke les sommets dans la Pile
    pile1.push(v);

}

Graphe transposition(Graphe mongraphe)
{
    Graphe M(mongraphe);

    for(auto &elem : M.get_aretes()){
        elem->set_first(elem->get_second());
        elem->set_second(elem->get_first());
    }

    return M;
}

void DFS(Graphe mongraphe,int v)
{
    (mongraphe.get_especes())[v]->set_marque(true);
    std::cout << v << " ";

    for(int i = mongraphe.get_especes()[v]->get_adjacents().front().get_numS(); i != mongraphe.get_especes()[v]->get_adjacents().back().get_numS(); ++i){
        if(!mongraphe.get_especes()[i]->get_marque()){
            DFS(mongraphe,i);
        }
    }
}
