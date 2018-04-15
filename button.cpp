#include "button.h"

Button::Button(std::string msg) : m_state(false), m_msg(msg), m_x(0), m_y(0)
{
    /// Initialisation des entites graphiques de la classe
    m_font.loadFromFile("arial.ttf");
    m_text.setFont(m_font);
    m_text.setString(msg);

    backgd.setSize(sf::Vector2f(165, 33));
    backgd.setFillColor(sf::Color(25, 25, 35));
}

Button::~Button()
{}

void Button::survoler(sf::RenderWindow &window)
{
    /// Detection du contact entre la position de la souris et celle du bouton
    if(sf::Mouse::getPosition(window).x > m_x && sf::Mouse::getPosition(window).x < m_x + 155 && sf::Mouse::getPosition(window).y > m_y && sf::Mouse::getPosition(window).y < m_y + 35)
        m_onit = true;
    else m_onit = false;
    /// Detection de clique de la souris sur le bouton
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > m_x && sf::Mouse::getPosition(window).x < m_x + 155 && sf::Mouse::getPosition(window).y > m_y && sf::Mouse::getPosition(window).y < m_y + 35)
        m_state = true;
}

void Button::afficher(sf::RenderWindow &window, int x, int y)
{
    /// Affichage des elements graphiques du bouton
    m_x = x, m_y = y;
    survoler(window);
    backgd.setPosition(m_x - 10, m_y + 5);
    m_text.setPosition(x, y);
    if(m_onit) window.draw(backgd);
    window.draw(m_text);
}

int Button::gety()
{
    return 165;
}

void Button::set_state(bool s)
{
    m_state = s;
}

bool Button::get_state()
{
    ///Getteur de l'etat du bouton (cliquer ou pas)
    return m_state;
}

bool Button::getOnIt()
{
    ///Getteur de l'etat du bouton (survoler ou pas)
    return m_onit;
}
