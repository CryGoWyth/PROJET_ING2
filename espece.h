#ifndef ESPECE_H_INCLUDED
#define ESPECE_H_INCLUDED
#include "widgets.h"
#include <vector>
#include "arete.h"

class Espece
{
private :
    Widgets *m_widgets;

    std::vector<Arete> m_proies;
    std::vector<Arete> m_predateurs;
    int m_population; // N
    int m_capacite; // K
    int m_facteur; // r

public :
    Espece(int x, int y, int nb);
    ~Espece();

    ///Fonctions d'évolution
    void evo_pop();
    void evo_cap();

    ///Getter et Setter
    int get_pop();
    int get_cap();
    int get_fact();

    void set_fact(int r);
};

#endif // ESPECE_H_INCLUDED
