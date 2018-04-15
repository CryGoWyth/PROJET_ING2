#include "arete.h"

Arete::Arete(Widgets *premier, Widgets *deux, int val) : first(premier), second(deux), mabar((first->getmx() + second->getmx()) / 2, (first->getmy() + second->getmy()) / 2, val)
{
    /// Initialisation des entites graphiques
    background.setPosition(sf::Vector2f(((first->getmx() + second->getmx()) / 2) - 12, ((first->getmy() + second->getmy()) / 2) - 42));
    background.setSize(sf::Vector2f(24, 84));
    background.setFillColor(sf::Color(0, 0, 0));
    /// Initialisation des attributs en fonction des valeurs recues en parametre
}

Arete::~Arete()
{}

void Arete::createLine()
{
    /// Creation d'une ligne graphique entre les sommets des deux Widgets de l'arete
    int x1 = first->getmx(), y1 = first->getmy(), x2 = second->getmx(), y2 = second->getmy();
    line.setFillColor(sf::Color(255, 255, 255));
    line.setPosition(x1, y1);
    line.setSize(sf::Vector2f(2 + (std::atoi(mabar.get_value().c_str()) / 25), int(std::hypot(x1 - x2, y1 - y2))));

    float x = (std::acos((y2 - y1) / std::sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)))  * 180) / M_PI;

    line.setRotation((x2 - x1 > 0) ? -x : x); /// Calcul des coordonnees de chaque entite
    droite = line, droite.setRotation((x2 - x1 > 0) ? -(x + 225) : x + 225);
    gauche = line, gauche.setRotation((x2 - x1 > 0) ? -(x - 225) : x - 225);
    droite.setPosition((first->getmx() + second->getmx()) / 2, (first->getmy() + second->getmy()) / 2);
    droite.setSize(sf::Vector2f(2 + (std::atoi(mabar.get_value().c_str()) / 25), 30));
    gauche.setPosition((first->getmx() + second->getmx()) / 2, (first->getmy() + second->getmy()) / 2);
    gauche.setSize(sf::Vector2f(2 + (std::atoi(mabar.get_value().c_str()) / 25), 30));
    background.setPosition(sf::Vector2f((first->getmx() + second->getmx()) / 2 - 12, ((first->getmy() + second->getmy()) / 2) - 42));
    mabar.update((first->getmx() + second->getmx()) / 2, (first->getmy() + second->getmy()) / 2);
    int d = (first->getmx() + second->getmx()) / 10, f = (first->getmy() + second->getmy()) / 10;
    if(m_couleur_compo==1){
        line.setFillColor(sf::Color (255,0,0)); /// Determination de la couleur d'affichage
        droite.setFillColor(sf::Color (255,0,0));
        gauche.setFillColor(sf::Color (255,0,0));
    }
    else{
        line.setFillColor(sf::Color (255,255,255));
        droite.setFillColor(sf::Color (255,255,255));
        gauche.setFillColor(sf::Color (255,255,255));
    }
}

void Arete::dessiner(sf::RenderWindow &window, int nb)
{
    createLine();
    window.draw(line);
    window.draw(background);
    mabar.dessiner(window, nb);
    window.draw(droite);
    window.draw(gauche);
}

bool Arete::get_selected()
{
    return mabar.get_selected();
}

int Arete::get_mabar()
{
    return std::atoi(mabar.get_value().c_str()); /// Getteur retournant les valeur de la mabar
}

void Arete::set_first(Widgets *premier)
{
    first = premier; /// Setteur pour modifier le predateur d'une arete
}

void Arete::set_second(Widgets *deuxieme)
{
    second = deuxieme; /// Setteur pour modifier la proie d'une arete
}

void Arete::set_couleur_compo(int i)
{
    m_couleur_compo = i;
}

Widgets* Arete::get_first()
{
    return first; /// Getteur retournant le predateur
}

Widgets* Arete::get_second()
{
    return second; /// Getteur retournant la proie
}

