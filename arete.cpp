#include "arete.h"

Arete::Arete(Widgets *premier, Widgets *deux, int val) : first(premier), second(deux), mabar((first->getmx() + second->getmx()) / 2, (first->getmy() + second->getmy()) / 2, val)
{
    background.setPosition(sf::Vector2f(((first->getmx() + second->getmx()) / 2) - 12, ((first->getmy() + second->getmy()) / 2) - 42));
    background.setSize(sf::Vector2f(24, 84));
    background.setFillColor(sf::Color(0, 0, 0));
    circle.setFillColor(sf::Color(255, 0, 0));
    circle.setRadius(40);
}

Arete::~Arete()
{}

void Arete::createLine()
{
    int x1 = first->getmx(), y1 = first->getmy(), x2 = second->getmx(), y2 = second->getmy();
    line.setFillColor(sf::Color(255, 255, 255));
    line.setPosition(x1, y1);
    line.setSize(sf::Vector2f(2 + (std::atoi(mabar.get_value().c_str()) / 25), int(std::hypot(x1 - x2, y1 - y2))));

    float x = (std::acos((y2 - y1) / std::sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)))  * 180) / M_PI;

    line.setRotation((x2 - x1 > 0) ? -x : x); /// Bricolage
    background.setPosition(sf::Vector2f((first->getmx() + second->getmx()) / 2 - 12, ((first->getmy() + second->getmy()) / 2) - 42));
    mabar.update((first->getmx() + second->getmx()) / 2, (first->getmy() + second->getmy()) / 2);
    /// test->depx = (vitesse / moyenne) * (test->xdes - test->x);
    /// test->depy = (vitesse / moyenne) * (test->ydes - test->y);
    /// moyenne = sqrt(pow(test->xdes - test->x, 2) + pow(test->ydes - test->y, 2));
    int d = (first->getmx() + second->getmx()) / 10, f = (first->getmy() + second->getmy()) / 10;
    //std::cout << "D : " << d << ", f : " << f << std::endl;
    //circle.setPosition(x1 + d, y1 + f);
}

void Arete::dessiner(sf::RenderWindow &window, int nb)
{
    createLine();
    window.draw(line);
    window.draw(background);
    mabar.dessiner(window, nb);
    window.draw(circle);
}

bool Arete::get_selected()
{
    return mabar.get_selected();
}

int Arete::get_mabar()
{
    return std::atoi(mabar.get_value().c_str());
}

void Arete::set_first(Widgets *premier)
{
    first = premier;
}

void Arete::set_second(Widgets *deuxieme)
{
    second = deuxieme;
}

Widgets* Arete::get_first()
{
    return first;
}

Widgets* Arete::get_second()
{
    return second;
}
