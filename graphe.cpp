#include "graphe.h"

Graphe::Graphe() : window(sf::VideoMode(1024, 720), "ING2_PROJECT")
{
    m_especes.push_back(new Espece(25, 50, 0, 0, 0));
    m_especes.push_back(new Espece(800, 150, 1, 0, 0));
    m_especes.push_back(new Espece(25, 300, 2, 0, 0));
    m_especes.push_back(new Espece(700, 600, 3, 0, 0));
    m_especes.push_back(new Espece(200, 500, 4, 0, 0));

    m_aretes.push_back(new Arete(m_especes[0]->get_widgets(), m_especes[1]->get_widgets()));
    m_aretes.push_back(new Arete(m_especes[1]->get_widgets(), m_especes[2]->get_widgets()));
    m_aretes.push_back(new Arete(m_especes[2]->get_widgets(), m_especes[3]->get_widgets()));
}

Graphe::~Graphe()
{
    for(auto elem : m_aretes) delete elem;
    for(auto elem : m_especes) delete elem;
}

void Graphe::gameWhile()
{
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                window.close();
        }

        nbControle = 0;
        for(auto elem : m_aretes) if(elem->get_selected()) nbControle++;
        for(auto elem : m_especes) if(elem->get_selected()) nbControle++;

        window.clear();
        for(auto elem : m_aretes) elem->dessiner(window, nbControle);
        for(auto elem : m_especes) elem->dessiner(window, nbControle);
        window.display();
    }
}

std::vector<Arete*> Graphe::get_aretes()
{
    return m_aretes;
}

std::vector<Espece*> Graphe::get_especes()
{
    return m_especes;
}
