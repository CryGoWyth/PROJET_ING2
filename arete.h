#ifndef ARETE_H
#define ARETE_H

#include "widgets.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <math.h>

#define M_PI 3.14159265358979323846

/*! \brief Declaration de la classe Arete
 *
 * \param *first pointeur de Widgets correspondant au predateur de l'arete
 * \param *second pointeur de Widgets correspondant a la proie de l'arete
 * \param mabar slide bar de l'arete de type Bar
 *
 */

class Arete
{
    public:
        /// Constructeur de la classe Arete
        Arete(Widgets *premier, Widgets *deux, int val);
        /// Destructeur de la classe
        ~Arete();
        /// Fonction dessinant les lignes entre sommets relies
        void createLine();
        /// Fonction d'affichage de la classe
        void dessiner(sf::RenderWindow &window, int nb);
        void set_first(Widgets *premier);
        void set_second(Widgets *deuxieme);
        Widgets* get_second();
        Widgets* get_first();
        int get_mabar();
        bool get_selected();
        void set_couleur_compo(int i);

    private:
        int m_couleur_compo;
        Widgets *first, *second;
        sf::RectangleShape line, background, droite, gauche;
        Bar mabar;
};

#endif // ARETE_H
