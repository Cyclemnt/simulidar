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
    /// \param length_ Largeur d'environnement.
    /// \param width_ Hauteur d'environnement.
    Environment(int length_, int width_);

    /// \brief Générer des obstacles aléatoires.
    /// \param number Nombre d'obstacles.
    /// \param maxSize Dimension maximale d'obstacle.
    void generateRandomObstacles(int number, int maxSize);
    /// \brief Affiche l'environnement dans le terminal.
    void printRoom() const;

    // Getters
    Grid getRoom() const;
    int getWidth() const;
    int getHeight() const;

    ~Environment();
};

#endif //ENVIRONMENT_HPP