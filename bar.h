#ifndef BAR_H
#define BAR_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Bar
{
    public:
        Bar(int x, int y);
        ~Bar();
        void dessiner(sf::RenderWindow &window);
        void mouvement(sf::RenderWindow &window);
        void update(int x, int y);
        void get_value();
        bool get_selected();

    private:
        sf::RectangleShape m_button, m_bar, l1, l2, l3, l4, background;
        sf::Text m_text;
        int m_x, m_y, my;
        bool selected;
};

#endif // BAR_H
