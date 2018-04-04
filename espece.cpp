#include "espece.h"

Espece::Espece(int x, int y, int nb, int N, int K)
{
    m_facteur = 1;
    m_widgets = new Widgets(x, y, nb);
    m_population = N;
    m_capacite = K;

    ///Remplir les proies et predateurs
}

Espece::~Espece()
{
    delete m_widgets;
}

void Espece::evo_pop()
{
    ///N(t+1) = Nt + rNt(1-Nt/K)
    m_population = m_population + m_facteur * m_population * (1 - m_population/m_capacite);

    //On soustrait ce que les prédateurs mangent
    for(auto elem : m_predateurs)
    {
        m_population = m_population - elem.get_mabar() * elem.get_second().get_pop();
    }
}

void Espece::evo_cap()
{
    m_capacite = 0; //On remet à 0 avant de recalculer la nouvelle capacité

    ///K = Coeff * Nproie + ... (autant de proie qu'il y en a)
    for(auto elem : m_proies)
    {
        m_capacite = m_capacite + elem.get_mabar() * elem.get_second().get_pop();
    }
}

int Espece::get_pop()
{
    return m_population;
}

int Espece::get_cap()
{
    return m_capacite;
}

int Espece::get_fact()
{
    return m_facteur;
}

void Espece::set_fact(int r)
{
    m_facteur = r;
}
