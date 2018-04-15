#include "graphe.h"

Graphe::Graphe(int type) : window(sf::VideoMode(1024, 720), "ING2_PROJECT"), ok(false), T1(&Graphe::evolution, this), simul(false), nbType(2)
{
    /// Initialisation des elements graphiques et audio
    m_font.loadFromFile("arial.ttf");
    m_text.setFont(m_font);
    loadImage();
    music.setVolume(100);
    music.setLoop(true);
}

Graphe::Graphe(const Graphe &monGraphe) : T1(&Graphe::evolution, this), simul(false)
{
    /// Initialisation en fonction des donnees du graphe recues en parametre
    m_font.loadFromFile("arial.ttf");
    m_text.setFont(m_font);
    this->m_aretes = monGraphe.get_aretes();
    this->m_especes = monGraphe.get_especes();
}

Graphe::~Graphe()
{
    /// Destruction des elements alloue dynamiquement
    for(auto elem : m_aretes) delete elem;
    for(auto elem : m_especes) delete elem;
}

void Graphe::gameWhile()
{
    int state = -1;
    std::vector<std::vector<int> > compo_connexe;
    mainMenu();
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                Kosaraju(this, compo_connexe);
                for(int i = 0; i < compo_connexe.size(); i++){
                    for(auto elem : compo_connexe[i]){
                        for(auto it : compo_connexe[i]){
                            for(auto aret : m_aretes){
                                if(aret->get_first()->get_nb() == m_especes[elem]->get_number() && aret->get_second()->get_nb() == m_especes[it]->get_number())
                                    aret->set_couleur_compo(1);
                                if(aret->get_first()->get_nb() == m_especes[it]->get_number() && aret->get_second()->get_nb() == m_especes[elem]->get_number())
                                    aret->set_couleur_compo(1);
                            }
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                for(int i = 0; i < compo_connexe.size(); i++){
                    for(auto elem : compo_connexe[i]){
                        for(auto it : compo_connexe[i]){
                            for(auto aret : m_aretes){
                                if(aret->get_first()->get_nb() == m_especes[elem]->get_number() && aret->get_second()->get_nb() == m_especes[it]->get_number())
                                    aret->set_couleur_compo(0);
                                if(aret->get_first()->get_nb() == m_especes[it]->get_number() && aret->get_second()->get_nb() == m_especes[elem]->get_number())
                                    aret->set_couleur_compo(0);
                            }
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                for(auto elem : m_aretes) std::cout << "Arete : " << elem->get_first()->get_nb() << ", " << elem->get_second()->get_nb() << std::endl;
        }

        nbControle = 0;
        for(auto elem : m_aretes) if(elem->get_selected()) nbControle++;
        for(auto elem : m_especes) if(elem->get_selected()) nbControle++;

        state = display();

        if(simul == true)T1.launch();
        if(state != -1) action(state);
    }
}

void Graphe::action(int nb)
{
    /// Les differentes actions en fonction de l'option choisie sont :
    if(nb == 0) creer();/// creer un nouveau graphe
    else if(nb == 1) load();/// charger un graphe
    else if(nb == 2) save();/// sauver un graphe
    else if(nb == 3) ajouter(); /// ajouter une espece
    else if(nb == 4) modifier();/// modifier une arete
    else if(nb == 5) supprimer();/// supprimer une espece
    else if(nb == 6){
        if(simul) simul = false;
        else{
            save();
            simul = true, m_clock.restart();/// Simulation
        }
    }
}

void Graphe::information(std::string msg)
{
    /// Affichage de la marche a suivre en fonction de l'action a effectue
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
    /// Calcul de l'evolution des populations
    sf::Time m_time = m_clock.getElapsedTime();
    if(m_time.asSeconds() >= 1){
        std::cout << "Time : " << m_time.asSeconds() << std::endl;

        for(auto elem : m_especes)
            elem->evo_cap(m_especes);
        /// Appelle des fonctions d'evolution de chaque espece

        std::cout << std::endl << std::endl;
        for(auto elem : m_especes)
            elem->evo_pop(m_especes);
        std::cout << std::endl << std::endl;
        for(auto elem : m_especes)
            elem->update();
        m_clock.restart();
    }
}

void Graphe::mainMenu()
{
    /// Menu principal de l'application :
    music.openFromFile("audio/menu_principal.wav");
    music.play();
    sf::Text choix1 = m_text, choix2 = m_text, titre = m_text;
    sf::RectangleShape support;
    titre.setCharacterSize(64);
    titre.setStyle(sf::Text::Underlined);
    support.setOutlineThickness(3);
    support.setOutlineColor(sf::Color(200, 200, 200));
    support.setFillColor(sf::Color(30, 30, 30));
    support.setPosition(65, 370);
    support.setSize(sf::Vector2f(300, 40));
    /// Creer un graphe
    choix1.setString("Créer un graphe"), choix2.setString("Charger un graphe"), titre.setString("Piscine de Code");
    /// Charger un graphe
    titre.setPosition(300, 70);
    choix1.setPosition(70, 340);
    choix2.setPosition(70, 410);
    bool ok = false;
    while(!ok){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                    window.close();
                    return;
            }
        }

        window.clear(sf::Color(30, 30, 30));
        if(sf::Mouse::getPosition(window).x > 70 && sf::Mouse::getPosition(window).x < 70 + 300 && sf::Mouse::getPosition(window).y > 340 && sf::Mouse::getPosition(window).y < 340 + 40){
            support.setPosition(65, 340);
            window.draw(support);
        }
        else if(sf::Mouse::getPosition(window).x > 70 && sf::Mouse::getPosition(window).x < 70 + 300 && sf::Mouse::getPosition(window).y > 410 && sf::Mouse::getPosition(window).y < 410 + 40){
            support.setPosition(65, 410);
            window.draw(support);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > 70 && sf::Mouse::getPosition(window).x < 70 + 300 && sf::Mouse::getPosition(window).y > 340 && sf::Mouse::getPosition(window).y < 340 + 40)
            creer(), ok = true;
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > 70 && sf::Mouse::getPosition(window).x < 70 + 300 && sf::Mouse::getPosition(window).y > 410 && sf::Mouse::getPosition(window).y < 410 + 40)
            load(), ok = true;

        window.draw(choix1);
        window.draw(choix2);
        window.draw(titre);
        window.display();
    }
}

void Graphe::supprimer()
{
    /// Suppression d'une espece apres avoir clique dessus
    int i = -1;
    ok = true;
    information("Cliquez sur une espece pour la supprimer");
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    while(i == -1) i = selectionner();
    for(auto it = m_aretes.begin(); it != m_aretes.end(); it++){ /// On supprime dabord les aretes reliees au sommet
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
    /// Fonction permettant de modifier une connexion entre especes
    int i = -1, j = -1;
    ok = true;
    /// Possibilite de supprimer une connexion
    bool check = false;
    information("Cliquez sur une premiere espece : le prédateur");
    display();
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    while(i == -1) i = selectionner();
    if(i == -2){ok = false;return;}
    information("Cliquez sur deuxieme espece : la proie");
    display();
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    while(j == -1 || j == i) j = selectionner();
    if(j == -2){ok = false;return;} /// Possibilite d'annuler l'action en cours

    for(auto it = m_aretes.begin(); it != m_aretes.end(); it++){
        if(((*it)->get_first()->get_nb() == i && (*it)->get_second()->get_nb() == j) || ((*it)->get_first()->get_nb() == j && (*it)->get_second()->get_nb() == i)){
            m_aretes.erase(it), check = true;
            break;
        }
    }
    if(!check){
        for(auto elem1 : m_especes){
            for(auto elem2 : m_especes){
                if(elem1->get_number() == i && elem2->get_number() == j){
                    m_aretes.push_back(new Arete(elem1->get_widgets(), elem2->get_widgets(), 0));
                    break;
                }
            }
        }
    }
    ok = false;
}

int Graphe::selectionner()
{
    /// Fonction permettant de selectionner une espece et de retourner son indice
    for(auto elem : m_especes){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > elem->get_widgets()->getmx() - 50 && sf::Mouse::getPosition(window).x < elem->get_widgets()->getmx() + 50 && sf::Mouse::getPosition(window).y > elem->get_widgets()->getmy() - 50 && sf::Mouse::getPosition(window).y < elem->get_widgets()->getmy() + 50)
            return elem->get_number();
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) return -2;
    display();
    return -1;
}

void Graphe::ajouter()
{
    /// Fonction d'ajout d'une espece en fonction de l'univers du graphe
    ok = true;
    int i = selectFamilie(), a = 0;
    if(i == - 2){ok = false; return;}
    information("Cliquez pour faire apparaitre une espece");
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    display();
    while(!sf::Mouse::isButtonPressed(sf::Mouse::Left));
    for(unsigned int b = 0; a < m_especes.size(); b = 0, a++){
        for(auto elem : m_especes)
            if(elem->get_number() == a) b++;
        if(b == 0) break;
    }
    m_especes.push_back(new Espece(sf::Mouse::getPosition(window).x - 5, sf::Mouse::getPosition(window).y, a, 0, 0));
    m_especes[m_especes.size()-1]->get_widgets()->set_Texture(&m_texture[i], i);
    m_especes[m_especes.size()-1]->load_vect(m_aretes);
    ok = false;
}

void Graphe::loadImage()
{
    /// Chargement des images des especes
    std::string buf, buffer; int taille = 0, mysize = 0;
    std::ostringstream ss;
    sf::Texture m_textur;
    m_texture.erase(m_texture.begin(), m_texture.end());
    if(nbType == 1) buf = "pics/image_graphe1/", taille = 14;
    else if(nbType == 2) buf = "pics/image_graphe2/", taille = 12;
    else if(nbType == 3) buf = "pics/image_graphe3/", taille = 11;

    for(int i = 0; i < taille; i++){
        ss << buf << "img" << i << ".png";
        m_textur.loadFromFile(ss.str());
        m_texture.push_back(sf::Texture(m_textur));
        ss.str("");
    }
}

void createButton(std::vector<Button*> &mesButtons, int nbType)
{
    /// Creation des bouton des especes
    std::string buf, buffer; int taille = 0, mysize = 0;
    if(nbType == 1) buf = "pics/image_graphe1/", taille = 14;
    else if(nbType == 2) buf = "pics/image_graphe2/", taille = 12;
    else if(nbType == 3) buf = "pics/image_graphe3/", taille = 11;

    std::ifstream file(buf + "fichier.txt", std::ios::in);
    file >> mysize;
    for(int i = 0; i < mysize; i++)
        file >> buffer, mesButtons.push_back(new Button(buffer));
    file.close();
}

int Graphe::selectFamilie()
{
    /// Selection de l'espece a ajouter
    bool check = false;
    std::vector<Button*> mesButtons;
    sf::Sprite m_sprite;
    ok = true;
    /// Affichage de l'image de l'espece survole par la souris
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    if(m_texture.size() < 1) loadImage();
    createButton(mesButtons, nbType);

    bg.setSize(sf::Vector2f(window.getSize().x / 2, mesButtons.size() * 35 + 70));
    bg.setPosition((window.getSize().x / 2) - (bg.getSize().x / 2), (window.getSize().y / 2) - (bg.getSize().y / 2));
    bg.setFillColor(sf::Color(5, 5, 25));

    m_text.setPosition(bg.getPosition().x + 50, bg.getPosition().y + 5);
    m_text.setString("Saississez une espece : ");
    m_sprite.setPosition(window.getSize().x / 4 + 300, window.getSize().y / 2 - 50);

    while(!check){
        window.clear(sf::Color(30, 30, 30));
        for(auto elem : m_aretes) elem->dessiner(window, nbControle);
        for(auto elem : m_especes) elem->dessiner(window, nbControle);
        window.draw(bg);
        window.draw(m_text);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window).x < bg.getPosition().x || sf::Mouse::getPosition(window).x > bg.getPosition().x + bg.getSize().x || sf::Mouse::getPosition(window).y < bg.getPosition().y || sf::Mouse::getPosition(window).y > bg.getPosition().y + bg.getSize().y))
            return -2;
        for(int i = 0; i < mesButtons.size(); i++){
            mesButtons[i]->afficher(window, window.getSize().x / 4 + 30, bg.getPosition().y + 50 + i * 35);
            m_sprite.setTexture(m_texture[i]);
            if(mesButtons[i]->getOnIt()) window.draw(m_sprite);
            if(mesButtons[i]->get_state()){
                for(auto elem : mesButtons) delete elem;
                return i;
            }
        }

        window.display();
    }
    ok = false;
    return 1;
}

void Graphe::creer()
{
    /// Creation d'un nouveau graphe en fonction de l'univers choisi
    music.stop();
    window.clear(sf::Color(30, 30, 30));
    window.display();
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
    m_especes.erase(m_especes.begin(), m_especes.end());
    m_aretes.erase(m_aretes.begin(), m_aretes.end()); /// On efface le graphe present
    std::vector<Button*> mesButtons;
    mesButtons.push_back(new Button("Foret"));
    mesButtons.push_back(new Button("Ocean")); /// Creation des boutons
    mesButtons.push_back(new Button("Desert"));

    bg.setSize(sf::Vector2f(window.getSize().x / 2 + 40, 3 * 35 + 70));
    bg.setPosition((window.getSize().x / 2) - (bg.getSize().x / 2), (window.getSize().y / 2) - (bg.getSize().y / 2));
    bg.setFillColor(sf::Color(5, 5, 15)); /// On creer le cadre de la demande ...

    m_text.setString("Saississez une univers pour le graphe"); /// ...Et la consigne
    m_text.setPosition(bg.getPosition().x + 20, bg.getPosition().y + 8);

    while(1 == 1){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                    window.close();
                    return;
            }
        }
        window.clear(sf::Color(30, 30, 30));
        window.draw(bg);
        window.draw(m_text); /// On les affiches

        for(int i = 0; i < mesButtons.size(); i++){
            mesButtons[i]->afficher(window, (window.getSize().x / 2) - mesButtons[i]->gety() / 2, bg.getPosition().y + 50 + i * 35);
            if(mesButtons[i]->get_state()){
                nbType = i + 1; /// Car les univers sont : 1, 2, 3
                loadImage(); /// On charge ensuite les images du bon univers
                for(auto elem : mesButtons) delete elem;
                if(nbType == 1) music.openFromFile("audio/foret.wav");
                else if(nbType == 2) music.openFromFile("audio/mer.wav");
                else if(nbType == 3) music.openFromFile("audio/savane.wav");
                music.play();
                return;
            }
        }
        window.display();
    }
}

int Graphe::getSommet(int nb)
{
    for(int i = 0; i < m_especes.size(); i++)
        if(m_especes[i]->get_number() == nb) return i;

    return 0;
}

void Graphe::save()
{
    /// Sauvegarde de tous les elements du graphe courant dans un fichier
    std::ofstream file(proposerFichier(), std::ios::out);
    std::cout << "Saving..." << std::endl;

    if(file){
        file << m_especes.size() << ' ' << nbType <<'\n';
        for(auto elem : m_especes)
            file << elem->get_number() << ' ' << elem->get_widgets()->get_mabar() << ' ' << elem->get_widgets()->getmx() << ' ' << elem->get_widgets()->getmy() << ' ' << elem->get_widgets()->get_nbImage() << '\n';
        file << m_aretes.size() << '\n';
        for(auto elem : m_aretes)
            file << elem->get_first()->get_nb() << ' ' << elem->get_second()->get_nb() << ' ' << elem->get_mabar() << '\n';
        file.close();
        for(auto elem : m_especes){
            elem->eraseVect();
            elem->load_vect(m_aretes);
        }
    }

    else return;
}

int Graphe::load()
{
    /// Chargement de tous les elements d'un fichier dans le graphe
    music.stop();
    m_especes.erase(m_especes.begin(), m_especes.end());
    m_aretes.erase(m_aretes.begin(), m_aretes.end());

    if(m_texture.size() == 0) loadImage();

    std::ifstream file(proposerFichier(), std::ios::in);
    std::cout << "Loading..." << std::endl;
    int tailleEspece = 0, tailleArete = 0, nb = 0, val, mx = 0, my = 0, nbImage = 0;
    if(file){
        file >> tailleEspece >> nbType;
        loadImage();
        for(int i = 0; i < tailleEspece; i++){
            file >> nb >> val >> mx >> my >> nbImage;
            m_especes.push_back(new Espece(mx, my, nb, val, 0));
            m_especes[m_especes.size() - 1]->get_widgets()->set_Texture(&m_texture[nbImage], nbImage);
        }
        file >> tailleArete;
        for(int i = 0; i < tailleArete; i++){
            file >> mx >> my >> val;
            m_aretes.push_back(new Arete(m_especes[getSommet(mx)]->get_widgets(), m_especes[getSommet(my)]->get_widgets(), val));
        }
        file.close();
        for(auto elem : m_especes) elem->load_vect(m_aretes);
        if(nbType == 1) music.openFromFile("audio/foret.wav");
        else if(nbType == 2) music.openFromFile("audio/mer.wav");
        else if(nbType == 3) music.openFromFile("audio/savane.wav");
        music.play();
    }
    else return 1;
    return 0;
}

int Graphe::display()
{
    /// Affichage de tous les elements graphiques du graphe
    int state = 0;
    window.clear(sf::Color(30, 30, 30));
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
    /// Choix du fichier (pour la sauvegarde ou le chargement)
    std::string buf;
    sf::Text montext = m_text;
    sf::Event e;
    ok = true;
    bg.setPosition(window.getSize().x / 4, window.getSize().y / 4);
    bg.setSize(sf::Vector2f(2 * window.getSize().x / 4, (2 * window.getSize().y / 4) / 2));
    bg.setFillColor(sf::Color(30, 39, 44));

    m_text.setPosition(window.getSize().x / 4 + 50, window.getSize().y / 4 + 10);
    m_text.setString("Saississez un nom de fichier : ");
    montext.setPosition(window.getSize().x / 4 + 25, window.getSize().y / 4 + 80);
    display();
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        while(window.pollEvent(e)){
            if(e.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && buf.size() > 0) buf.pop_back();
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window).x < bg.getPosition().x || sf::Mouse::getPosition(window).x > bg.getPosition().x + bg.getSize().x || sf::Mouse::getPosition(window).y < bg.getPosition().y || sf::Mouse::getPosition(window).y > bg.getPosition().y + bg.getSize().y))
                    return "txt";
                else if(e.key.code < 36 && e.key.code >= 0 && buf.size() < 27){
                    buf += char(e.key.code + ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 65 : 97)));
                }
            }
            if(e.type == sf::Event::Closed){
                window.close(); return " ";
            }
        }

        montext.setString(buf + ".txt");
        window.clear(sf::Color(30, 30, 30));
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
