#ifndef GRAPHE_H
#define GRAPHE_H

#include "bar.h"
#include "espece.h"
#include "arete.h"
#include <vector>

class Graphe
{
    public:
        Graphe();
        ~Graphe();
        void gameWhile();
        std::vector<Arete*> get_aretes();
        std::vector<Espece*> get_especes();

    private:
        std::vector<Arete*> m_aretes;
        std::vector<Espece*> m_especes;
        sf::RenderWindow window;
        int nbControle;
};

#endif // GRAPHE_H
