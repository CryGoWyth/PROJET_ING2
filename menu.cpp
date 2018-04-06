#include "menu.h"

Menu::Menu() : open(false)
{
    m_buttons.push_back(new Button("Charger"));
    m_buttons.push_back(new Button("Sauver"));
    m_buttons.push_back(new Button("Ajouter"));
    m_buttons.push_back(new Button("Modifier"));
    m_buttons.push_back(new Button("Supprimer"));

    bg.setSize(sf::Vector2f(175, m_buttons.size() * 35 + 8));
    bg.setFillColor(sf::Color(5, 5, 5));
}

Menu::~Menu()
{}

void Menu::checkOpen(sf::RenderWindow &window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        open = true;
        if(sf::Mouse::getPosition(window).x > 1024 - 175) m_x = sf::Mouse::getPosition(window).x - 175;
        else m_x = sf::Mouse::getPosition(window).x;
        if(sf::Mouse::getPosition(window).y < m_buttons.size() * 35 + 8) m_y = sf::Mouse::getPosition(window).y;
        else m_y = sf::Mouse::getPosition(window).y - m_buttons.size() * 35 + 8;
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && ((sf::Mouse::getPosition(window).x < m_x || sf::Mouse::getPosition(window).x > m_x + 175) || (sf::Mouse::getPosition(window).y < m_y || sf::Mouse::getPosition(window).y > m_y + m_buttons.size() * 35 + 8)))
        open = false;
}

int Menu::afficher(sf::RenderWindow &window)
{
    checkOpen(window);

    if(open){
        bg.setPosition(m_x, m_y);
        window.draw(bg);
        for(int i = 0; i < m_buttons.size(); i++){
            m_buttons[i]->afficher(window, m_x + 15, m_y + i * 35);
            if(m_buttons[i]->get_state()){
                open = false, m_buttons[i]->set_state(false);
                return i;
            }
        }
    }
    return -1;
}
