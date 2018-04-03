#include "bar.h"

Bar::Bar(int x, int y) : m_x(x), m_y(y), my(y), selected(false)
{
    sf::Font font;
    if(!font.loadFromFile("arial.ttf")) std::cout << "Couldn't load the text" << std::endl;
    m_text.setFont(font);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(24);
    m_text.setString("Salut");
    m_text.setPosition(m_x, m_y + 40);

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

void Bar::dessiner(sf::RenderWindow &window)
{
    mouvement(window);
    window.draw(background);
    window.draw(l1);
    window.draw(l2);
    window.draw(l3);
    window.draw(l4);
    window.draw(m_bar);
    window.draw(m_button);
}

void Bar::mouvement(sf::RenderWindow &window)
{
    if((selected && sf::Mouse::isButtonPressed(sf::Mouse::Left)) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window)).x > m_x - 10 && (sf::Mouse::getPosition(window)).x < m_x + 10 && (sf::Mouse::getPosition(window)).y > m_y - 40 && (sf::Mouse::getPosition(window)).y < m_y + 40)){
        m_button.setPosition(sf::Vector2f(m_x - 8, sf::Mouse::getPosition(window).y)), my = sf::Mouse::getPosition(window).y - m_y, selected = true;
    }
    else selected = false;

    if(m_y == 100) std::cout << "my : " << my << ", m_y : " << m_y << std::endl;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) get_value();

    if(m_button.getPosition().y > m_y - 8 + 40) m_button.setPosition(sf::Vector2f(m_x - 8, m_y - 8 + 39));
    if(m_button.getPosition().y < m_y - 40) m_button.setPosition(sf::Vector2f(m_x - 8, m_y - 39));
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
    m_text.setPosition(x, y + 40);
    m_x = x, m_y = y;
}

void Bar::get_value()
{
    std::cout << "m_x : " << m_x << ", m_y : " << m_y << ", my : " << my << std::endl;//43 - (m_y - my)
}

bool Bar::get_selected()
{
    return selected;
}
