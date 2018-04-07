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

class Graphe
{
    public:
        Graphe(int type = 0); /// Constructeur par defaut
        Graphe(const Graphe &monGraphe); /// Constructeur par copie
        ~Graphe();
        void gameWhile(); /// Boucle de programme principale
        void mainMenu(); /// Menu principal du programme
        void action(int nb); /// Action des boutons du menu
        void evolution(); /// Evolution des donnees en temps reel
        void information(std::string msg); /// Consigne apparaissant sur le haut de la fenetre
        void loadImage(); /// Charger les Images d'un graphe
        int selectFamilie(); /// Choix d'espece d'un sommet a ajouter
        int selectionner(); /// Selection d'un sommet
        int display(); /// Fonction d'affichage
        std::string proposerFichier();
        std::vector<Arete*> get_aretes() const;
        std::vector<Espece*> get_especes() const;

        int load(); /// Return 1 si probleme
        void save();
        void creer();
        void ajouter(); /// fonction de la premiere partie
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
        sf::Font m_font; /// Ecriture sfml
        sf::Text m_text;
        sf::RectangleShape bg;
        sf::RenderWindow window;
        sf::Thread T1;
        sf::Clock m_clock;
};

#endif // GRAPHE_H
