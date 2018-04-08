#ifndef BAR_H
#define BAR_H

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

class Bar
{
    public:
        Bar(int x, int y, int val);
        ~Bar();
        void dessiner(sf::RenderWindow &window, int nb);
        void mouvement(sf::RenderWindow &window, int nb);
        void update(int x, int y);
        void set_value(int value);
        bool get_selected();
        std::string get_value();

    private:
        sf::RectangleShape m_button, m_bar, l1, l2, l3, l4, background;
        sf::Text m_text;
        sf::Font font;
        int m_x, m_y, my;
        bool selected;
};

#endif // BAR_H
