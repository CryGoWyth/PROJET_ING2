#ifndef MENU_H
#define MENU_H

#include "button.h"
#include <vector>
#include <iostream>

/*! \brief Declaration de la classe Menu
 *
 *  Cette classe correspond au menu creer lors d'un clique droit sur l'application
 * \param m_buttons vecteur de pointeur de Button regroupant les actions realisables sur le graphe courant
 * \param m_x coordonnee en abscisse du menu
 * \param m_y coordonnee en ordonnee du menu
 * \param open booleen traduisant l'etat du menu (ouvert ou ferme)
 */


class Menu
{
    public:
        /// Constructeur par defaut de la classe Menu
        Menu();
        /// Destructeur de la classe
        ~Menu();
        /// Fonction de detection d'evenement sur le menu
        void checkOpen(sf::RenderWindow &window);
        /// Fonction d'affichage
        int afficher(sf::RenderWindow &window);

    private:
        sf::RectangleShape bg;
        std::vector<Button*> m_buttons;
        int m_x, m_y;
        bool open;
};

#endif // MENU_H
