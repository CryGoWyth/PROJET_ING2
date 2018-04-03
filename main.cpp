#include "bar.h"
#include "widgets.h"
#include "arete.h"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML works!");
    Widgets mywidgets1(25, 50, 0), mywidgets2(800, 150, 1), mywidgets3(25, 300, 2), mywidgets4(700, 600, 3), mywidgets5(200, 500, 4);

    std::vector<Arete> m_aretes;
    m_aretes.push_back(Arete(&mywidgets1, &mywidgets2));
    m_aretes.push_back(Arete(&mywidgets2, &mywidgets3));
    m_aretes.push_back(Arete(&mywidgets3, &mywidgets4));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                window.close();
        }

        window.clear();
        for(auto elem : m_aretes) elem.dessiner(window);
        mywidgets1.dessiner(window);
        mywidgets2.dessiner(window);
        mywidgets3.dessiner(window);
        mywidgets4.dessiner(window);
        mywidgets5.dessiner(window);
        window.display();


    }

    return 0;
}
