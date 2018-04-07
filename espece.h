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
        int get_pop(Arete *a, std::vector<Espece*> m_especes, bool situation);
        int m_population, m_capacite, m_facteur; /// N, K, r
        int m_numS; ///ATTENTION!! : Numero du sommet
        int m_numAS; //Numero du plus petit sommet adjacent de numS
        bool m_marque; //Bool de marquage
        std::vector<Espece> m_adjacents;

    public :
        Espece(int x, int y, int nb, int val, int N, int K);
        ~Espece();

        ///Remplissage vecteur préda et proie
        void load_vect(std::vector<Arete*> m_aretes);

        ///Fonctions d'évolution
        void evo_pop(std::vector<Espece*> m_especes);
        void evo_cap(std::vector<Espece*> m_especes);
        void dessiner(sf::RenderWindow &window, int nb);


        ///Getter et Setter
        int get_number();
        int get_selected();
        int get_population();
        int get_cap();
        int get_fact();
        int get_numS();
        int get_numAS();
        bool get_marque();
        std::vector<Espece> get_adjacents() const;
        Widgets* get_widgets();

        void set_numS(int num);
        void set_fact(int r);
        void set_numAS(int numA);
        void set_marque(bool m);
        void set_adjacents(std::vector<Espece> A);
};

#endif // ESPECE_H_INCLUDED
