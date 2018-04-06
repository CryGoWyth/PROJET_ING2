#include "button.h"

Button::Button(std::string msg) : m_state(false), m_msg(msg), m_x(0), m_y(0)
{
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
    if(sf::Mouse::getPosition(window).x > m_x && sf::Mouse::getPosition(window).x < m_x + 155 && sf::Mouse::getPosition(window).y > m_y && sf::Mouse::getPosition(window).y < m_y + 35)
        m_onit = true;
    else m_onit = false;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > m_x && sf::Mouse::getPosition(window).x < m_x + 155 && sf::Mouse::getPosition(window).y > m_y && sf::Mouse::getPosition(window).y < m_y + 35)
        m_state = true;
}

void Button::afficher(sf::RenderWindow &window, int x, int y)
{
    m_x = x, m_y = y;
    survoler(window);
    backgd.setPosition(m_x - 10, m_y + 5);
    m_text.setPosition(x, y);
    if(m_onit) window.draw(backgd);
    window.draw(m_text);
}

void Button::set_state(bool s)
{
    m_state = s;
}

bool Button::get_state()
{
    return m_state;
}
