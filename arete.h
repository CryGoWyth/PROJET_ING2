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
        Arete(Widgets *premier, Widgets *deux, int val);
        ~Arete();
        void createLine();
        void dessiner(sf::RenderWindow &window, int nb);
        void set_first(Widgets *premier);
        void set_second(Widgets *deuxieme);
        Widgets* get_second();
        Widgets* get_first();
        int get_mabar();
        bool get_selected();

    private:
        Widgets *first, *second;
        sf::RectangleShape line, background, droite, gauche;
        sf::CircleShape circle;
        Bar mabar;
};

#endif // ARETE_H
