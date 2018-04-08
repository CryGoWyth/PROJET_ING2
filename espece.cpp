#include "espece.h"

Espece::Espece(int x, int y, int nb, int val, int N, int K)
{
    m_facteur = 1;
    m_widgets = new Widgets(x, y, nb, val);
    m_population = N;
    m_capacite = K;

    ///Remplir les proies et predateurs
}

Espece::~Espece()
{
    delete m_widgets;
}

void Espece::evo_pop(std::vector<Espece*> m_especes)
{
    ///N(t+1) = Nt + rNt(1-Nt/K)
    //m_population = m_population + m_facteur * m_population * (1 - m_population/m_capacite);

    //On soustrait ce que les prédateurs mangent
    for(auto elem : m_predateurs){
        m_population = m_population - elem->get_mabar() * get_pop(elem, m_especes);
        this->get_widgets()->set_value(m_population);
    }
}

void Espece::evo_cap(std::vector<Espece*> m_especes)
{
    m_capacite = 0; //On remet à 0 avant de recalculer la nouvelle capacité

    ///K = Coeff * Nproie + ... (autant de proie qu'il y en a)
    for(auto elem : m_proies)
        m_capacite = m_capacite + elem->get_mabar() * get_pop(elem, m_especes);
}

void Espece::dessiner(sf::RenderWindow &window, int nb)
{
    m_widgets->dessiner(window, nb);
}

int Espece::get_population()
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

Widgets* Espece::get_widgets()
{
    return m_widgets;
}

int Espece::get_pop(Arete *a, std::vector<Espece*> m_especes)
{
    for(unsigned int i = 0; i  < m_especes.size(); i++)
        if(m_especes[i]->get_widgets() == a->get_second()) return m_especes[i]->get_population();

    return 0;
}

int Espece::get_selected()
{
    return m_widgets->get_selected();
}

int Espece::get_number()
{
    return m_widgets->get_nb();
}

int Espece::get_numS()
{
    return m_numS;
}

void Espece::set_numS(int num)
{
    m_numS=num;
}

bool Espece::get_marque()
{
    return m_marque;
}

void Espece::set_marque(bool m)
{
    m_marque=m;
}

std::vector<Espece> Espece::get_adjacents() const
{
    return m_adjacents;
}

std::vector<Arete*> Espece::get_predateurs()
{
    return m_predateurs;
}
