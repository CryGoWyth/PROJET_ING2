#include "widgets.h"

Widgets::Widgets(int x, int y , int nb) : mabar(x - 7, y + 3), m_x(x), m_y(y), m_nb(nb), selected(false), divx(0)
{
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

    loadPictures();
}

Widgets::~Widgets()
{}

void Widgets::dessiner(sf::RenderWindow &window)
{
    mouvement(window);
    window.draw(background);
    mabar.dessiner(window);
    window.draw(l1);
    window.draw(l2);
    window.draw(l3);
    window.draw(l4);
    window.draw(m_sprite);
}

void Widgets::loadPictures()
{
    std::string name = "pics/clown";
    name += char(m_nb + 49);
    name += ".jpg";
    std::cout << "name : " << name << std::endl;
    if (!m_texture.loadFromFile(name.c_str()))
        std::cout << "Couldn't load the image" << std::endl;

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_x + 12, m_y - 41);
}

void Widgets::mouvement(sf::RenderWindow &window)
{
    if((selected && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mabar.get_selected()) || (!mabar.get_selected() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window)).x > m_x + 12 && (sf::Mouse::getPosition(window)).x < m_x + 112 && (sf::Mouse::getPosition(window)).y > m_y - 41 && (sf::Mouse::getPosition(window)).y < m_y + 61)){
        if((sf::Mouse::getPosition(window).x - m_x) > 0 && divx == 0) divx = (sf::Mouse::getPosition(window).x - m_x);
        if(divy == 0) divy = (sf::Mouse::getPosition(window).y - m_y);
        m_x = sf::Mouse::getPosition(window).x - divx, m_y = sf::Mouse::getPosition(window).y - divy, selected = true;
    }
    else selected = false;

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
    background.setPosition(sf::Vector2f(m_x - 22, m_y - 42));
    m_sprite.setPosition(m_x + 12, m_y - 41);
    mabar.update(m_x - 7, m_y + 3);
}

int Widgets::getmx()
{
    return m_x;
}

int Widgets::getmy()
{
    return m_y;
}
