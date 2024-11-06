#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "types.hpp"

using Types::CellState;
using Types::Grid;

class Environment
{
private:
    int width;   // Longueur de l'environnement (cm)
    int height;  // Largeur de l'environnement (cm)
    Grid room;   // Occupancy room
public:
    // Constructeur avec paramètres
    Environment(int length_, int width_);

    // Générer des obstacles aléatoires
    void generateRandomObstacles(int number, int maxSize);
    // Algorithme DDA pour tracer une ligne entre deux points et remplir la grille
    void drawLineDDA(int x1, int y1, int x2, int y2);
    // Vérifier si une cellule est libre pour placer le robot
    bool isCellFree(int x, int y, double robotDiameter) const;
    // Fonction pour afficher la grille
    void printRoom() const;

    // Getters
    Grid getRoom() const;
    int getWidth() const;
    int getHeight() const;

    ~Environment();
};

#endif //ENVIRONMENT_HPP