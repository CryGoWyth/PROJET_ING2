#include "espece.h"

Espece::Espece(int x, int y, int nb, int val, int K)
{
    m_facteur = 1;
    m_widgets = new Widgets(x, y, nb, val);
    m_population = val;
    m_capacite = K;
}

void Espece::load_vect(std::vector<Arete*> m_aretes)
{
    for(auto elem : m_aretes)
    {
        if(elem->get_first()->get_nb()==this->get_number())
        {
            m_proies.push_back(new Arete(elem->get_first(), elem->get_second(), elem->get_mabar()));
        }

        if(elem->get_second()->get_nb()==this->get_number())
        {
            m_predateurs.push_back(new Arete(elem->get_first(), elem->get_second(), elem->get_mabar()));
        }
    }
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
    for(auto elem : m_predateurs)
        m_population = m_population - elem->get_mabar() * get_pop(elem, m_especes, true);

    this->get_widgets()->set_value(m_population);
}

void Espece::evo_cap(std::vector<Espece*> m_especes)
{
    m_capacite = 0; //On remet à 0 avant de recalculer la nouvelle capacité

    ///K = Coeff * Nproie + ... (autant de proie qu'il y en a)
    for(auto elem : m_proies)
        m_capacite = m_capacite + elem->get_mabar() * get_pop(elem, m_especes, false);
}

void Espece::dessiner(sf::RenderWindow &window, int nb)
{
    m_population = m_widgets->get_mabar();
    m_widgets->dessiner(window, nb);
}

int Espece::get_population()
{
    return m_population;
}

int Espece::get_capacite()
{
    return m_capacite;
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

void Espece::eraseVect()
{
    m_predateurs.erase(m_predateurs.begin(), m_predateurs.end());
    m_proies.erase(m_proies.begin(), m_proies.end());
}

Widgets* Espece::get_widgets()
{
    return m_widgets;
}

int Espece::get_pop(Arete *a, std::vector<Espece*> m_especes, bool situation)
{
    if(situation==false){
    for(unsigned int i = 0; i  < m_especes.size(); i++)
        if(m_especes[i]->get_widgets() == a->get_second()) return m_especes[i]->get_population();
    }

    if(situation==true){
            for(unsigned int i = 0; i  < m_especes.size(); i++)
        if(m_especes[i]->get_widgets() == a->get_first()) return m_especes[i]->get_population();
    }

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

int Espece::get_numAS()
{
    return m_numAS;
}

void Espece::set_numAS(int numA)
{
    m_numAS=numA;
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

std::vector<Arete*> Espece::get_proies()
{
    return m_proies;
}
