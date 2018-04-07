#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button(std::string msg);
        ~Button();
        void survoler(sf::RenderWindow &window);
        void afficher(sf::RenderWindow &window, int x, int y);
        void set_state(bool s);
        int gety();
        bool get_state();
        bool getOnIt();

    private:
        sf::Font m_font;
        sf::Text m_text;
        sf::RectangleShape backgd;
        std::string m_msg;
        int m_x, m_y;
        bool m_state;
        bool m_onit;
};

#endif // BUTTON_H
