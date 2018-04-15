#ifndef ESPECE_H_INCLUDED
#define ESPECE_H_INCLUDED

#include "widgets.h"
#include "arete.h"
#include <vector>

/*! \brief Declaration de la classe Espece
 *
 * \param m_widgets element de type Widgets appartenant a l'espece
 * \param m_proies vecteur de pointeur d'arete regroupant les proies de l'espece
 * \param m_predateurs vecteur de pointeur d'arete regroupant les predateurs de l'espece
 * \param m_adjacents vecteur d'espece regroupant les proies et predateurs de l'espece
 * \param m_population nombre de population de l'espece
 * \param m_capacite capacite de population d'une espece
 */

class Espece
{
    private :

        Widgets *m_widgets;
        std::vector<Arete*> m_proies;
        std::vector<Arete*> m_predateurs;
        std::vector<Espece> m_adjacents;
        int get_pop(Arete *a, std::vector<Espece*> m_especes, bool situation);
        int m_population, m_capacite, m_facteur; /// N, K, r
        int popupdate;
        int m_numS; ///ATTENTION!! : Numero du sommet
        int m_numAS; //Numero du plus petit sommet adjacent de numS
        bool m_marque; //Bool de marquage

    public :
        /// Constructeur de la classe Espece
        Espece(int x, int y, int nb, int N, int K);
        /// Destructeur de la classe
        ~Espece();
        /// Fonction pour remplir le vecteur predateur et proie
        void load_vect(std::vector<Arete*> m_aretes);
        /// Fonction pour vider les vecteurs m_predateurs et m_proies
        void eraseVect();
        /// Fonction d'evolution : calcul de la population
        void evo_pop(std::vector<Espece*> m_especes);
        /// Fonction d'evolution : calcul de la capacite
        void evo_cap(std::vector<Espece*> m_especes);
        /// Fonction d'affichage des elements graphiques
        void dessiner(sf::RenderWindow &window, int nb);
        /// Mise a jour de la population
        void update();

        int get_number();
        int get_selected();
        int get_population();
        int get_capacite();
        int get_cap();
        int get_fact();
        int get_numS();
        int get_numAS();
        bool get_marque();
        std::vector<Espece> get_adjacents() const;
        Widgets* get_widgets();
        std::vector<Arete*> get_predateurs();
        std::vector<Arete*> get_proies();

        void set_numS(int num);
        void set_fact(int r);
        void set_numAS(int numA);
        void set_marque(bool m);
        void set_adjacents(std::vector<Espece> A);
};

#endif // ESPECE_H_INCLUDED
