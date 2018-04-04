#ifndef ESPECE_H_INCLUDED
#define ESPECE_H_INCLUDED

#include "widgets.h"
#include "arete.h"
#include <vector>

class Espece
{
    private :
        Widgets *m_widgets;
        std::vector<Arete*> m_proies;
        std::vector<Arete*> m_predateurs;
        int m_population; // N
        int m_capacite; // K
        int m_facteur; // r

    public :
        Espece(int x, int y, int nb, int N, int K);
        ~Espece();

        ///Fonctions d'évolution
        void evo_pop(std::vector<Espece*> m_especes);
        void evo_cap(std::vector<Espece*> m_especes);
        int get_pop(Arete *a, std::vector<Espece*> m_especes);
        void dessiner(sf::RenderWindow &window, int nb);


        ///Getter et Setter
        int get_selected();
        int get_population();
        int get_cap();
        int get_fact();
        Widgets* get_widgets();

        void set_fact(int r);
};

#endif // ESPECE_H_INCLUDED
