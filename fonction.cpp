#include "prototype.h"

void Kosaraju(Graphe &mongraphe)
{
    std::stack<Espece*> pile;

    ///On enleve la marque de tous les sommets du graphe au cas où
    for(auto elem : mongraphe.get_especes())
        elem->set_marque(false);


    ///On rempli la pile par ordre de fin de marquage des sommets
    for(auto elem: mongraphe.get_especes())
    {
        if(elem->get_marque()==false)
        {
            std::cout << elem->get_numS() << " tour de boucle de fillorder" << std::endl;

            fillorder(mongraphe,elem,pile);
        }
   }
    /*if(mongraphe.get_especes()[0]->get_marque()==false){
        fillorder(mongraphe,mongraphe.get_especes()[0],pile);
    }*/

    ///On créer un graphe similaire à G sauf que l'on a inversé l'orientation des aretes
    Graphe transpo(transposition(mongraphe));

    ///On enlève la marque de tous les sommets du graphe au cas où
    for(auto elem: transpo.get_especes())
        elem->set_marque(false);

    while(pile.empty()==false)  //Tant que la pile n'est pas vide
    {
        ///Espece v = pile.top(); /// Ne fonctionne pas, RECODER POUR LE CREER CORRECTEMENT
        int v=pile.top()->get_numS();

        if(pile.top()->get_marque()==false)
        {
            DFS(mongraphe,v);
            std::cout << std::endl << std::endl << std::endl;

        }
        pile.pop();
    }
}

void fillorder(Graphe monGraphe,Espece *v,std::stack<Espece*> &pile1)
{
    int numero=-1;



    ///On marque le sommet
    v->set_marque(true);
    std::cout << "Je suis dans fillorder" << std::endl;

    ///On marque les sommets adjacents

    std::vector<Arete*> apple=v->get_predateurs();
    std::cout << "Apple=Vecteur predateur" << std::endl;

        for(auto elem : apple)
        {

            std::cout << "For auto elem de Apple" << std::endl;
            if(elem->get_first()!=0)  ///Si le sommet à bien un predateur
            {
                std::cout << "Vecteur predateur non nul Poids:" << elem->get_first()->get_mabar() << std::endl;
                numero=elem->get_first()->get_nb();


                if(monGraphe.get_especes()[numero]->get_marque()==false)
                {
                    std::cout << "Condition de non-parcours du sommet valider" << std::endl;
                    std::cout << "Numero du Sommet explorer: " << numero << std::endl;
                    fillorder(monGraphe,monGraphe.get_especes()[numero],pile1);

                }
                else
                {

                    std::cout << "Condition de non-parcours non valider" << std::endl;
                }
            }
        }

    ///On stocke les sommets dans la Pile

    pile1.push(v);
    std::cout << "Taille de la pile " << pile1.size() << "  et Valeur: " << pile1.top()->get_numS() << " " << v->get_numS() <<std::endl;


}

Graphe transposition(Graphe &mongraphe)
{
    Graphe M(mongraphe);

    for(auto &elem : M.get_aretes())
    {
        elem->set_first(elem->get_second());
        elem->set_second(elem->get_first());
    }

    return M;
}

void DFS(Graphe mongraphe,int v)
{
    (mongraphe.get_especes())[v]->set_marque(true);
    std::cout << v << " ";

    for(int i = mongraphe.get_especes()[v]->get_adjacents().front().get_numS(); i != mongraphe.get_especes()[v]->get_adjacents().back().get_numS(); ++i)
    {
        if(!mongraphe.get_especes()[i]->get_marque())
        {
            DFS(mongraphe,i);
        }
    }
}
