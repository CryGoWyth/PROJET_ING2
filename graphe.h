#ifndef GRAPHE_H
#define GRAPHE_H

#include "bar.h"
#include "espece.h"
#include "arete.h"
#include "menu.h"
#include "prototype.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

/*! \brief Declaration de la classe Graphe
 *
 * \param m_menu objet de type Menu pour selectionner les especes a ajouter au graphe
 * \param m_aretes vecteur de pointeur d'Arete regroupant les aretes du graphe
 * \param m_especes vecteur de pointeur d'Espece regroupant les especes du graphe
 * \param m_textures vecteur de texture des images de chaque espece (Utile pour la SFML)
 */

class Graphe
{
    public:
        /// Constructeur par defaut de la classe Graphe
        Graphe(int type = 0);
        /// Constructeur par copie
        Graphe(const Graphe &monGraphe);
        /// Destructeur de la classe
        ~Graphe();
        /// Fonction comportant la boucle principale de l'application
        void gameWhile();
        /// Menu principal du programme
        void mainMenu();
        /// Action des boutons du menu
        void action(int nb);
        /// Evolution des donnees en temps reel
        void evolution();
        /// Consigne apparaissant sur le haut de la fenetre
        void information(std::string msg);
        /// Charger les Images d'un graphe
        void loadImage();
        /// Choix d'espece d'un sommet a ajouter
        int selectFamilie();
        /// Selection d'un sommet
        int selectionner();
        /// Fonction d'affichage
        int display();
        int getSommet(int nb);
        std::string proposerFichier();
        std::vector<Arete*> get_aretes() const;
        std::vector<Espece*> get_especes() const;

        int load();
        void save();
        void creer();
        void ajouter();
        void modifier();
        void supprimer();

    private:
        std::vector<Arete*> m_aretes;
        std::vector<Espece*> m_especes;
        std::vector<sf::Texture> m_texture;
        std::string m_msg;
        int nbControle, nbType;
        bool ok, simul;
        Menu m_menu;
        sf::Music music;
        sf::Font m_font;
        sf::Text m_text;
        sf::RectangleShape bg;
        sf::RenderWindow window;
        sf::Thread T1;
        sf::Clock m_clock;
};

#endif // GRAPHE_H
