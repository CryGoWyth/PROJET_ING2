#include "graphe.h"

Graphe::Graphe() : window(sf::VideoMode(1024, 720), "ING2_PROJECT"), ok(false), T1(&Graphe::evolution, this), simul(false)
{
    m_font.loadFromFile("arial.ttf");
    m_text.setFont(m_font);
}

Graphe::Graphe(const Graphe &monGraphe) : T1(&Graphe::evolution, this), simul(false)
{
    m_font.loadFromFile("arial.ttf");
    m_text.setFont(m_font);
    this->m_aretes = monGraphe.get_aretes();
    this->m_especes = monGraphe.get_especes();
}

Graphe::~Graphe()
{
    for(auto elem : m_aretes) delete elem;
    for(auto elem : m_especes) delete elem;
}

void Graphe::gameWhile()
{
    int state = -1;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::P)) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                Kosaraju(*this);
        }

        nbControle = 0;
        for(auto elem : m_aretes) if(elem->get_selected()) nbControle++;
        for(auto elem : m_especes) if(elem->get_selected()) nbControle++;

        state = display();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ /// Remplacer par le bouton simu
            // ... Le bouléen passe à vrai pour indiqué que nous somme en simulation
            simul = true;
            //On relance la clock à 0 vu qu'on ne peut pas arrêter ou relancer une clock
            m_clock.restart();
        }

        //Si on est en simulation ...
        if(simul == true){
            //On effectue le Thread en boucle
            T1.launch();
        }
        //Si on appuie sur pause ...
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) simul=false; // ... On arrête la sim

        if(state != -1) action(state);
    }
}

void Graphe::action(int nb)
{
    if(nb == 0) load();/// charger fait -> choix fichier
    else if(nb == 1) save();/// sauver fait -> choix fichier
    else if(nb == 2) ajouter(); /// ajouter fait -> choix famille
    else if(nb == 3) modifier();/// modifier
    else if(nb == 4) supprimer();/// supprimer
}

void Graphe::information(std::string msg)
{
    m_msg = msg;
    m_text.setString(m_msg);
    m_text.setCharacterSize(30);
    m_text.setPosition(600 - ((m_msg.size() * 20) / 2), 0);
    bg.setPosition(600 - ((m_msg.size() * 20 + 10) / 2), 0);
    bg.setSize(sf::Vector2f(m_msg.size() * 14 + 10, 35));
    bg.setFillColor(sf::Color(5, 5, 5));
    window.draw(bg);
    window.draw(m_text);
}

void Graphe::evolution()
{
    //on crée notre timer qui va stocker la quantité de temps écoulée depuis le dernier restarts de la clock
    sf::Time m_time = m_clock.getElapsedTime();
    //Toutes les 5 secondes ...
    if(m_time.asSeconds() >= 1){
        std::cout << "Time : " << m_time.asSeconds() << std::endl; //Test
        //On appelle les fonctions d'évolution
        for(auto elem : m_especes){
            elem->evo_cap(m_especes);
            elem->evo_pop(m_especes);
        }

        //On remet à 0 la clock, logique ...
        m_clock.restart();
    }
}

void Graphe::supprimer()
{
    int i = -1;
    ok = true;
    information("Cliquez sur une espece pour la supprimer");
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    while(i == -1) i = selectionner();
    for(auto it = m_aretes.begin(); it != m_aretes.end(); it++){ /// On supprime dabord les aretes relier au sommet
        if((*it)->get_first()->get_nb() == i || (*it)->get_second()->get_nb() == i){
            m_aretes.erase(it);
            it = m_aretes.begin() - 1;
        }
    }
    for(auto it = m_especes.begin(); it != m_especes.end(); it++){
        if((*it)->get_widgets()->get_nb() == i){
            m_especes.erase(it);
            break;
        }
    }
    ok = false;
}

void Graphe::modifier()
{
    int i = -1, j = -1;
    ok = true;
    bool check = false;
    information("Cliquez sur une premiere espece : le prédateur");
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    display();
    while(i == -1) i = selectionner();
    information("Cliquez sur deuxieme espece : la proie");
    display();
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    while(j == -1 || j == i) j = selectionner();

    std::cout << "i : " << i << ", j : " << j << std::endl;

    for(auto it = m_aretes.begin(); it != m_aretes.end(); it++){
        if(((*it)->get_first()->get_nb() == i && (*it)->get_second()->get_nb() == j) || ((*it)->get_first()->get_nb() == j && (*it)->get_second()->get_nb() == i)){
            m_aretes.erase(it), check = true;
            std::cout << "here" << std::endl;
            break;
        }
    }
    if(!check) m_aretes.push_back(new Arete(m_especes[i]->get_widgets(), m_especes[j]->get_widgets(), 0));
    ok = false;
}

int Graphe::selectionner()
{
    for(auto elem : m_especes){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > elem->get_widgets()->getmx() && sf::Mouse::getPosition(window).x < elem->get_widgets()->getmx() + 100 && sf::Mouse::getPosition(window).y > elem->get_widgets()->getmy() - 50 && sf::Mouse::getPosition(window).y < elem->get_widgets()->getmy() + 50)
            return elem->get_number();
    }
    display();
    return -1;
}

void Graphe::ajouter()
{
    ok = true;
    information("Cliquez pour faire apparaitre une espece");
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    display();
    while(!sf::Mouse::isButtonPressed(sf::Mouse::Left));
    m_especes.push_back(new Espece(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 9, 0, 0, 0));
    ok = false;
}

void Graphe::save()
{
    std::cout << "Saving..." << std::endl;
    std::ofstream file(proposerFichier(), std::ios::out);

    if(file){
        file << m_especes.size() << '\n';
        for(auto elem : m_especes)
            file << elem->get_number() << ' ' << elem->get_widgets()->get_mabar() << ' ' << elem->get_widgets()->getmx() << ' ' << elem->get_widgets()->getmy() << '\n';
        file << m_aretes.size() << '\n';
        for(auto elem : m_aretes)
            file << elem->get_first()->get_nb() << ' ' << elem->get_second()->get_nb() << ' ' << elem->get_mabar() << '\n';
        file.close();
    }
    else std::cout << "Couldn't open the file" << std::endl;
}

void Graphe::load()
{
    m_especes.erase(m_especes.begin(), m_especes.end());
    m_aretes.erase(m_aretes.begin(), m_aretes.end());

    std::cout << "Loading..." << std::endl;
    std::ifstream file(proposerFichier(), std::ios::in);
    int tailleEspece = 0, tailleArete = 0, nb = 0, val, mx = 0, my = 0;
    if(file){
        file >> tailleEspece;
        for(int i = 0; i < tailleEspece; i++){
            file >> nb >> val >> mx >> my;
            m_especes.push_back(new Espece(mx, my, nb, val, 0, 0));
        }
        file >> tailleArete;
        for(int i = 0; i < tailleArete; i++){
            file >> mx >> my >> val;
            m_aretes.push_back(new Arete(m_especes[mx]->get_widgets(), m_especes[my]->get_widgets(), val));
        }
        file.close();
    }
    else std::cout << "Couldn't open the file" << std::endl;

    for(auto elem : m_especes)
    {
        elem->load_vect(m_aretes);
    }
}

int Graphe::display()
{
    int state = 0;
    window.clear(sf::Color(15, 15, 15));
    for(auto elem : m_aretes) elem->dessiner(window, nbControle);
    for(auto elem : m_especes) elem->dessiner(window, nbControle);
    state = m_menu.afficher(window);
    if(ok){
        window.draw(bg);
        window.draw(m_text);
    }
    window.display();
    return state;
}

std::string Graphe::proposerFichier()
{
    std::string buf;
    sf::Text montext = m_text;
    sf::Event e;
    ok = true;
    bg.setPosition(window.getSize().x / 4, window.getSize().y / 4);
    bg.setSize(sf::Vector2f(2 * window.getSize().x / 4, (2 * window.getSize().y / 4) / 2));
    bg.setFillColor(sf::Color(5, 5, 5));

    m_text.setPosition(window.getSize().x / 4 + 50, window.getSize().y / 4 + 10);
    m_text.setString("Saississez un nom de fichier : ");
    montext.setPosition(window.getSize().x / 4 + 25, window.getSize().y / 4 + 80);
    display();
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        while(window.pollEvent(e)){
            if(e.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && buf.size() > 0) buf.pop_back();
                else if(e.key.code < 36 && e.key.code >= 0 && buf.size() < 27){
                    buf += char(e.key.code + ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 65 : 97)));
                }
                else std::cout << e.key.code << std::endl;
            }
        }
        montext.setString(buf + ".txt");
        window.clear(sf::Color(15, 15, 15));
        for(auto elem : m_aretes) elem->dessiner(window, nbControle);
        for(auto elem : m_especes) elem->dessiner(window, nbControle);
        window.draw(bg);
        window.draw(m_text);
        window.draw(montext);
        window.display();
    }
    ok = false;
    return buf + ".txt";
}

std::vector<Arete*> Graphe::get_aretes() const
{
    return m_aretes;
}

std::vector<Espece*> Graphe::get_especes() const
{
    return m_especes;
}
