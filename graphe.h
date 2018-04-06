#ifndef GRAPHE_H
#define GRAPHE_H

#include "bar.h"
#include "espece.h"
#include "arete.h"
#include "menu.h"
#include "prototype.h"
#include <vector>
#include <fstream>
#include <SFML/System.hpp>

class Graphe
{
    public:
        Graphe();
        Graphe(const Graphe &monGraphe);
        ~Graphe();
        void gameWhile();
        void menu(sf::RenderWindow &window);
        void action(int nb);
        void evolution();
        void information(std::string msg);
        int selectionner();
        int display();
        std::string proposerFichier();
        std::vector<Arete*> get_aretes() const;
        std::vector<Espece*> get_especes() const;

        void save(); /// fonction de base
        void load();
        void ajouter();
        void modifier();
        void supprimer();

    private:
        std::vector<Arete*> m_aretes;
        std::vector<Espece*> m_especes;
        std::string m_msg;
        Menu m_menu;
        sf::Font m_font;
        sf::Text m_text;
        sf::RectangleShape bg;
        sf::RenderWindow window;
        bool ok, simul;
        int nbControle;
        sf::Thread T1;
        sf::Clock m_clock;
};

#endif // GRAPHE_H
