#ifndef WIDGETS_H
#define WIDGETS_H

#include "bar.h"
#include <sstream>

/*! \brief Declaration de la classe Widgets
 *
 * \param mabar slide bar de type Bar pour jauger le niveau de population d'une espece
 * \param m_x coordonnee en abscisse du widget
 * \param m_y coordonnee en ordonnee du widget
 * \param m_nb numero du sommet
 */

class Widgets
{
    public:
        /// Constructeur surcharche de la classe Widgets
        Widgets(int x, int y , int nb, int val);
        /// Destructeur de la classe
        ~Widgets();
        /// Fonction d'affichage
        void dessiner(sf::RenderWindow &window, int nb);
        /// Fonction de deplacement du widgets
        void mouvement(sf::RenderWindow &window, int nb);
        /// Mise a jour du widget et se ses composantes graphiques
        void update();
        /// Setteur d'image du widget
        void set_Texture(sf::Texture *mat, int i);
        /// Setteur de la valeur de la slide bar
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
