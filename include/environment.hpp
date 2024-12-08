#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "types.hpp"

using Types::Grid;

/// \brief Représente l'environnement dans lequel le robot évolue.
class Environment
{
private:
    int width;   // Longueur de l'environnement
    int height;  // Largeur de l'environnement
    Grid room;   // Occupancy grid
public:
    /// \brief Constructeur avec paramètres.
    /// Ce constructeur initialise un environnement de simulation représenté sous la forme d'une grille 2D initialisée avec l'état CellState::Free pour chaque cellule. Les cellules des bords de la grille (première et dernière rangée, première et dernière colonne) sont définies avec l'état CellState::Wall (mur), représentant des limites infranchissables.
    /// \param length_ Largeur d'environnement.
    /// \param width_ Hauteur d'environnement.
    Environment(int length_, int width_);

    /// \brief Générer des obstacles aléatoires.
    /// Cette méthode ajoute un nombre donné d'obstacles aléatoires dans la grille. Chaque obstacle est une région rectangulaire de cellules contiguës définies comme des murs (CellState::Wall).
    /// \param number Nombre d'obstacles.
    /// \param maxSize Dimension maximale des obstacles.
    void generateRandomObstacles(int number, int maxSize);
    /// \brief Affiche l'environnement dans le terminal.
    /// Cette méthode affiche la grille de l'environnement dans le terminal. Chaque type de cellule est représenté par un caractère spécifique
    void printRoom() const;

    // Getters
    Grid getRoom() const;
    int getWidth() const;
    int getHeight() const;

    ~Environment();
};

#endif //ENVIRONMENT_HPP