#include "espece.h"

Espece::Espece(int x, int y, int nb, int val, int K)
{
    m_facteur = 1, m_numS = nb, m_population = val, m_capacite = K;
    m_widgets = new Widgets(x, y, nb, val);
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

void Espece::update()
{
    m_population = popupdate;
}

void Espece::evo_pop(std::vector<Espece*> m_especes)
{
    ///N(t+1) = Nt + rNt(1-Nt/K)
    float f;
    std::cout << "Pop first : " << m_population << ", fact : " << m_facteur << ", cap : " << m_capacite << std::endl;
    if(m_capacite > 0){
        f = float(m_population) + (float(m_facteur) * float(m_population) * (1 - (float(m_population) / float(m_capacite))));
        popupdate = f;
    }

    //On soustrait ce que les prédateurs mangent
    std::cout << "Capacite : " << m_capacite << ", pop : " << f << std::endl;
    for(auto elem : m_predateurs)
        popupdate = popupdate - (elem->get_mabar() * m_especes[elem->get_first()->get_nb()]->get_population());//get_pop(elem, m_especes, true);
    std::cout << "Fresh pop : " << popupdate << std::endl;
    this->get_widgets()->set_value(popupdate);
}

void Espece::evo_cap(std::vector<Espece*> m_especes)
{
    m_capacite = 0; //On remet à 0 avant de recalculer la nouvelle capacité

    ///K = Coeff * Nproie + ... (autant de proie qu'il y en a)
    for(auto elem : m_proies){
        std::cout << "Get mabar de " << this->get_number() << " : " << elem->get_mabar() << ", pop : " <<  m_especes[elem->get_second()->get_nb()]->get_population() << ", nb : " << elem->get_first()->get_nb()<< std::endl;

        m_capacite = m_capacite + (elem->get_mabar() *  m_especes[elem->get_second()->get_nb()]->get_population());///get_pop(elem, m_especes, false);
    }
    std::cout << "Fresh cap " << this->get_number() << " : " << m_capacite << std::endl;
}

void Espece::dessiner(sf::RenderWindow &window, int nb)
{
    m_population = m_widgets->get_mabar();
    //for(auto elem : m_predateurs)
        //std::cout << "Predateur : " << get_population() << std::endl;
    if(m_population == 0)
        while(1 == 1);
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
        for(unsigned int i = 0; i  < m_especes.size(); i++){
            if(m_especes[i]->get_number() == a->get_second()->get_nb()){
                std::cout << "1-Pop : " << m_especes[i]->get_population() << ", i = " << i << std::endl;
                return m_especes[i]->get_population();
            }
        }
    }

    if(situation){
        for(unsigned int i = 0; i  < m_especes.size(); i++){
            if(m_especes[i]->get_number() == a->get_second()->get_nb()){
                std::cout << "2-Pop : " << m_especes[i]->get_population() << ", i = " << i << std::endl;
                return m_especes[i]->get_population();
            }
        }
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
