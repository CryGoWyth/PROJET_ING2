#include "graphe.h"

Graphe::Graphe() : window(sf::VideoMode(1024, 720), "ING2_PROJECT")
{
    m_widgets.push_back(new Widgets(25, 50, 0));
    m_widgets.push_back(new Widgets(800, 150, 1));
    m_widgets.push_back(new Widgets(25, 300, 2));
    m_widgets.push_back(new Widgets(700, 600, 3));
    m_widgets.push_back(new Widgets(200, 500, 4));

    m_aretes.push_back(new Arete(m_widgets[0], m_widgets[1]));
    m_aretes.push_back(new Arete(m_widgets[1], m_widgets[2]));
    m_aretes.push_back(new Arete(m_widgets[2], m_widgets[3]));
}

Graphe::~Graphe()
{}

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
        for(auto elem : m_widgets) if(elem->get_selected()) nbControle++;

        window.clear();
        for(auto elem : m_aretes) elem->dessiner(window, nbControle);
        for(auto elem : m_widgets) elem->dessiner(window, nbControle);
        window.display();
    }
}
