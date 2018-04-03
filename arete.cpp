#include "arete.h"

Arete::Arete(Widgets *premier, Widgets *deux) : first(premier), second(deux), mabar((first->getmx() + second->getmx()) / 2, (first->getmy() + second->getmy()) / 2)
{
    background.setPosition(sf::Vector2f(((first->getmx() + second->getmx()) / 2) - 12, ((first->getmy() + second->getmy()) / 2) - 42));
    background.setSize(sf::Vector2f(24, 84));
    background.setFillColor(sf::Color(0, 0, 0));
}

Arete::~Arete()
{}

void Arete::createLine()
{
    int x1 = first->getmx(), y1 = first->getmy(), x2 = second->getmx(), y2 = second->getmy();
    line.setFillColor(sf::Color(255, 255, 255));
    line.setPosition(x1, y1);
    line.setSize(sf::Vector2f(2, int(std::hypot(x1 - x2, y1 - y2))));

    float x = (std::acos((y2 - y1) / std::sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)))  * 180) / M_PI;

    line.setRotation((x2 - x1 > 0) ? -x : x); /// Bricolage
    background.setPosition(sf::Vector2f((first->getmx() + second->getmx()) / 2 - 12, ((first->getmy() + second->getmy()) / 2) - 42));
    mabar.update((first->getmx() + second->getmx()) / 2, (first->getmy() + second->getmy()) / 2);
}

void Arete::dessiner(sf::RenderWindow &window)
{
    createLine();
    window.draw(line);
    window.draw(background);
    mabar.dessiner(window);
}
