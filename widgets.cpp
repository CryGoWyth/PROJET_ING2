#include "widgets.h"

Widgets::Widgets(int x, int y , int nb, int val) : mabar(x - 7, y + 3, val), m_x(x), m_y(y), m_nb(nb), selected(false), divx(0)
{
    std::ostringstream buf;
    font.loadFromFile("arial.ttf");
    m_text.setFont(font);
    m_text.setColor(sf::Color::White);
    m_text.setCharacterSize(12);
    m_text.setStyle(sf::Text::Bold);
    m_text.setPosition(m_x  + 101, m_y + 50);
    buf << m_nb;
    m_text.setString(buf.str());

    l1.setPosition(sf::Vector2f(m_x - 23, m_y - 42));
    l1.setSize(sf::Vector2f(1, 139));
    l1.rotate(-90);

    l2.setPosition(sf::Vector2f(m_x + 115, m_y - 42));
    l2.setSize(sf::Vector2f(1, 102));

    l3.setPosition(sf::Vector2f(m_x - 23, m_y + 60));
    l3.setSize(sf::Vector2f(1, 139));
    l3.rotate(-90);

    l4.setPosition(sf::Vector2f(m_x - 23, m_y - 42));
    l4.setSize(sf::Vector2f(1, 102));

    background.setPosition(sf::Vector2f(m_x - 22, m_y - 42));
    background.setSize(sf::Vector2f(138, 102));
    background.setFillColor(sf::Color(0, 0, 0));

    support.setFillColor(sf::Color(0, 0, 0));
    support.setPosition(sf::Vector2f(m_x + 100, m_y + 50));
    support.setSize(sf::Vector2f(20, 12));
}

Widgets::~Widgets()
{}

void Widgets::dessiner(sf::RenderWindow &window, int nb)
{
    mouvement(window, nb);
    window.draw(background);
    mabar.dessiner(window, nb);
    window.draw(l1);
    window.draw(l2);
    window.draw(l3);
    window.draw(l4);
    window.draw(m_sprite);
    window.draw(support);
    window.draw(m_text);
}

void Widgets::set_Texture(sf::Texture *mat, int i)
{
    m_texture = *mat, nbImage = i;
    m_sprite.setTexture(*mat);
    m_sprite.setPosition(m_x + 12, m_y - 41);
}

void Widgets::mouvement(sf::RenderWindow &window, int nb)
{
    if((selected && !nb && sf::Mouse::isButtonPressed(sf::Mouse::Left)) || (!mabar.get_selected() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window)).x > m_x + 12 && (sf::Mouse::getPosition(window)).x < m_x + 112 && (sf::Mouse::getPosition(window)).y > m_y - 41 && (sf::Mouse::getPosition(window)).y < m_y + 61)){
        if((sf::Mouse::getPosition(window).x - m_x) > 0 && divx == 0) divx = (sf::Mouse::getPosition(window).x - m_x);
        if(divy == 0) divy = (sf::Mouse::getPosition(window).y - m_y);
        m_x = sf::Mouse::getPosition(window).x - divx, m_y = sf::Mouse::getPosition(window).y - divy, selected = true;
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && selected) selected = false;

    if(divx != 0 && !(selected && sf::Mouse::isButtonPressed(sf::Mouse::Left))) divx = 0;
    if(divy != 0 && !(selected && sf::Mouse::isButtonPressed(sf::Mouse::Left))) divy = 0;

    if(m_x + 116 > window.getSize().x) m_x = window.getSize().x - 116;
    if(m_x - 24 < 0) m_x = 24;
    if(m_y + 61 > window.getSize().y) m_y = window.getSize().y - 61;
    if(m_y - 43 < 0) m_y = 43;

    update();
}

void Widgets::update()
{
    l1.setPosition(sf::Vector2f(m_x - 23, m_y - 42));
    l2.setPosition(sf::Vector2f(m_x + 115, m_y - 42));
    l3.setPosition(sf::Vector2f(m_x - 23, m_y + 60));
    l4.setPosition(sf::Vector2f(m_x - 23, m_y - 42));
    m_text.setPosition(m_x  + 102, m_y + 45);
    support.setPosition(sf::Vector2f(m_x + 95, m_y + 47));
    background.setPosition(sf::Vector2f(m_x - 22, m_y - 42));
    m_sprite.setPosition(m_x + 12, m_y - 41);
    mabar.update(m_x - 7, m_y + 3);
}

void Widgets::set_value(int value)
{
    mabar.set_value(value);
}

int Widgets::get_nbImage()
{
    return nbImage;
}

int Widgets::getmx()
{
    return (m_x - 23) + (background.getSize().x / 2);
}

int Widgets::getmy()
{
    return (m_y - 42) + (background.getSize().y / 2);
}

int Widgets::get_nb()
{
    return m_nb;
}

int Widgets::get_mabar()
{
    return std::atoi(mabar.get_value().c_str());
}

bool Widgets::get_selected()
{
    if(selected == true)
        return selected;
    else return mabar.get_selected();
}
