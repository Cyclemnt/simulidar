#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "types.hpp"

using Types::Grid;

class Environment
{
private:
    int width;   // Longueur de l'environnement (cm)
    int height;  // Largeur de l'environnement (cm)
    Grid room;   // Occupancy grid
public:
    // Constructeur avec paramètres
    Environment(int length_, int width_);

    // Générer des obstacles aléatoires
    void generateRandomObstacles(int number, int maxSize);
    // Fonction pour afficher la grille dans le terminal
    void printRoom() const;

    // Getters
    Grid getRoom() const;
    int getWidth() const;
    int getHeight() const;

    ~Environment();
};

#endif //ENVIRONMENT_HPP