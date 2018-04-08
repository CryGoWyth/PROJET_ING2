#ifndef WIDGETS_H
#define WIDGETS_H

#include "bar.h"
#include <sstream>

class Widgets
{
    public:
        Widgets(int x, int y , int nb, int val);
        ~Widgets();
        void dessiner(sf::RenderWindow &window, int nb);
        void mouvement(sf::RenderWindow &window, int nb);
        void update();
        void set_Texture(sf::Texture *mat, int i);
        void set_value(int value);
        bool get_selected();
        int get_nbImage();
        int get_mabar();
        int get_nb();
        int getmx();
        int getmy();

    private:
        Bar mabar;
        sf::RectangleShape l1, l2, l3, l4, background, support;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Text m_text;
        sf::Font font;
        int m_x, m_y, m_nb, divx, divy, nbImage;
        bool selected;
};

#endif // WIDGETS_H
