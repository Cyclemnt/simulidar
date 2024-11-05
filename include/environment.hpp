#ifndef _ENVIRONMENT_HPP_
#define _ENVIRONMENT_HPP_

#include "types.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()
#include<opencv2/opencv.hpp>


using Types::CellState;
using Types::Grid;

class Environment
{
private:
    int width; // Longueur de l'environnement (cm)
    int height;  // Largeur de l'environnement (cm)
    Grid grid;  // Occupancy grid
public:
    // Constructeur avec paramètres
    Environment(int length_, int width_);

    // Générer des obstacles aléatoires
    void generateRandomObstacles(int number, int maxSize);
    // Algorithme DDA pour tracer une ligne entre deux points et remplir la grille
    void drawLineDDA(int x1, int y1, int x2, int y2);
    // Vérifier si une cellule est libre pour placer le robot
    bool isCellFree(int x, int y, double robotDiameter) const;
    //bool isPathFree() const; mais doit permettre au robot d'avancer jusqu'à l'obstacle
    // Fonction pour afficher la grille
    void printGrid() const;

    // Getters
    int getWidth() const;
    int getHeight() const;

    ~Environment();
};

#endif //_ENVIRONMENT_HPP_