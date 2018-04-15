#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

/*! \brief Declaration de la classe Button
 *
 * \param m_msg std::string correspondant au text du bouton
 * \param m_x coordonnee en abscisse du bouton
 * \param m_y coordonnee en ordonnee du bouton
 * \param m_onit booleen de survolement du bouton
 * \param m_state booleen d'action sur le bouton
 *
 */

class Button
{
    public:
        /// Constructeur de la classe recevant le texte du bouton
        Button(std::string msg);
        /// Destructeur detruisant les elements allouer dynamiquement
        ~Button();
        /// Fonction de detection du survolement du bouton par la souris
        void survoler(sf::RenderWindow &window);
        /// Fonction d'affichage du bouton
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
