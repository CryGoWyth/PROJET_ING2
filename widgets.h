#ifndef WIDGETS_H
#define WIDGETS_H

#include "bar.h"

class Widgets
{
    public:
        Widgets(int x, int y , int nb);
        ~Widgets();
        void dessiner(sf::RenderWindow &window);
        void mouvement(sf::RenderWindow &window);
        void update();
        void loadPictures();
        int getmx();
        int getmy();

    private:
        Bar mabar;
        sf::RectangleShape l1, l2, l3, l4, background;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        int m_x, m_y, m_nb, divx, divy;
        bool selected;
};

#endif // WIDGETS_H
