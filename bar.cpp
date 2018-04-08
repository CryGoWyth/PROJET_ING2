#include "bar.h"

Bar::Bar(int x, int y, int val) : m_x(x), m_y(y), selected(false)
{
    my = -((((val + 25) * 72) / 100) - 50);
    font.loadFromFile("arial.ttf");
    m_text.setFont(font);
    m_text.setColor(sf::Color::White);
    m_text.setCharacterSize(12);
    m_text.setStyle(sf::Text::Bold);
    m_text.setPosition(m_x - 13, m_y + 41);

    m_button.setPosition(sf::Vector2f(m_x - 8, m_y - 4));
    m_button.setSize(sf::Vector2f(16, 8));
    m_button.setFillColor(sf::Color(105, 105, 105));

    m_bar.setPosition(sf::Vector2f(m_x - 2, m_y - 40));
    m_bar.setSize(sf::Vector2f(3, 80));
    m_bar.setFillColor(sf::Color(128, 128, 128));

    l1.setPosition(sf::Vector2f(m_x - 12, m_y - 42));
    l1.setSize(sf::Vector2f(1, 24));
    l1.rotate(-90);

    l2.setPosition(sf::Vector2f(m_x + 11, m_y - 42));
    l2.setSize(sf::Vector2f(1, 84));

    l3.setPosition(sf::Vector2f(m_x - 12, m_y + 43));
    l3.setSize(sf::Vector2f(1, 24));
    l3.rotate(-90);

    l4.setPosition(sf::Vector2f(m_x - 12, m_y - 42));
    l4.setSize(sf::Vector2f(1, 84));
}

Bar::~Bar()
{}

void Bar::dessiner(sf::RenderWindow &window, int nb)
{
    mouvement(window, nb);
    window.draw(background);
    m_text.setString(get_value());
    window.draw(m_text);
    window.draw(l1);
    window.draw(l2);
    window.draw(l3);
    window.draw(l4);
    window.draw(m_bar);
    window.draw(m_button);
}

void Bar::set_value(int value)
{
    my = -((((value + 25) * 72) / 100) - 50);
}

void Bar::mouvement(sf::RenderWindow &window, int nb)
{
    if((selected && !nb && sf::Mouse::isButtonPressed(sf::Mouse::Left)) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window)).x > m_x - 10 && (sf::Mouse::getPosition(window)).x < m_x + 10 && (sf::Mouse::getPosition(window)).y > m_y - 44 && (sf::Mouse::getPosition(window)).y < m_y + 44)){
        m_button.setPosition(sf::Vector2f(m_x - 8, sf::Mouse::getPosition(window).y)), my = sf::Mouse::getPosition(window).y - m_y, selected = true;
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && selected) selected = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) get_value();

    if(m_button.getPosition().y > m_y - 8 + 40) m_button.setPosition(sf::Vector2f(m_x - 8, m_y - 8 + 40)), my = 32;
    if(m_button.getPosition().y < m_y - 40) m_button.setPosition(sf::Vector2f(m_x - 8, m_y - 40)), my = -40;
}

void Bar::update(int x, int y)
{
    l4.setPosition(sf::Vector2f(x - 12, y - 42));
    l3.setPosition(sf::Vector2f(x - 12, y + 43));
    l2.setPosition(sf::Vector2f(x + 11, y - 42));
    l1.setPosition(sf::Vector2f(x - 12, y - 42));
    background.setPosition(sf::Vector2f(m_x - 12, m_y - 42));
    m_bar.setPosition(sf::Vector2f(x - 2, y - 40));
    m_button.setPosition(sf::Vector2f(x - 8, y + my));
    m_text.setPosition(x - 13, y + 41);
    m_x = x, m_y = y;
}

std::string Bar::get_value()
{
    std::ostringstream test;
    int i = 0;
    i = (((100 - (my + 50)) * 100) / 72) - 24;
    test << i;
    return test.str();
}

bool Bar::get_selected()
{
    return selected;
}
