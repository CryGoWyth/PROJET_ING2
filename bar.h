#ifndef BAR_H
#define BAR_H

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

/*! \brief Declaration de la classe Bar
 *
 * \param my floatant correspondant a la distance de bouton de la slide bar
 * \param selected booleen dessignant l'etat de selection de la slide bar
 * \param m_x coordonnee en abscisse de la slide bar
 * \param m_y coordonnee en ordonnee de la slide bar
 */

class Bar
{
    public:
        /// Constructeur de la classe Bar
        Bar(int x, int y, int val);
        /// Destructeur de la classe
        ~Bar();
        /// Fonction d'affichage
        void dessiner(sf::RenderWindow &window, int nb);
        /// Fonction de deplacement du bouton de la slide bar
        void mouvement(sf::RenderWindow &window, int nb);
        /// Fonction de mise a jour des valeurs des elements graphiques
        void update(int x, int y);
        /// Setteur de la valeur de la slide bar
        void set_value(int value);
        bool get_selected();
        /// Getteur de la valeur de la slide bar
        std::string get_value();

    private:
        sf::RectangleShape m_button, m_bar, l1, l2, l3, l4, background;
        sf::Text m_text;
        sf::Font font;
        int m_x, m_y;
        float my;
        bool selected;
};

#endif // BAR_H
