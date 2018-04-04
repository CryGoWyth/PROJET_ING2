#ifndef GRAPHE_H
#define GRAPHE_H

#include "bar.h"
#include "widgets.h"
#include "arete.h"
#include <vector>

class Graphe
{
    public:
        Graphe();
        ~Graphe();
        void gameWhile();

    private:
        std::vector<Arete*> m_aretes;
        std::vector<Widgets*> m_widgets;
        sf::RenderWindow window;
        int nbControle;
};

#endif // GRAPHE_H
