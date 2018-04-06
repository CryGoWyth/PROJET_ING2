#ifndef MENU_H
#define MENU_H

#include "button.h"
#include <vector>
#include <iostream>

class Menu
{
    public:
        Menu();
        ~Menu();
        void checkOpen(sf::RenderWindow &window);
        int afficher(sf::RenderWindow &window);

    private:
        sf::RectangleShape bg;
        std::vector<Button*> m_buttons;
        int m_x, m_y;
        bool open;
};

#endif // MENU_H
