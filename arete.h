#ifndef ARETE_H
#define ARETE_H

#include "widgets.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <math.h>

#define M_PI 3.14159265358979323846

class Arete
{
    public:
        Arete(Widgets *premier, Widgets *deux);
        ~Arete();
        void createLine();
        void dessiner(sf::RenderWindow &window, int nb);
        Widgets* get_second();
        int get_mabar();
        bool get_selected();

    private:
        Widgets *first, *second;
        sf::RectangleShape line, background;
        Bar mabar;
};

#endif // ARETE_H
