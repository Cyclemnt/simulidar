#ifndef MAP_HPP
#define MAP_HPP

#include "types.hpp"

using Types::CellState;
using Types::Grid;

class Map
{
private:
    Grid robotMap;      // Occupancy grid
    int leftExtension, bottomExtension;  // Quantité de cases ajoutées à gauche et en bas de la position initiale
    //double resolution;  // Résolution de la carte
public:
    // Constructeur qui initialise le carte du robot
    Map();

    // Binarisation de la grille en "libre", "occupé" et "inconnu"
    //Grid binarizeGrid(double freeThreshold, double occupiedThreshold);
    // Méthode pour tracer un chemin de cases vides terminé par un mur
    void traceAndUpdateGrid(double startX, double startY, double rayAngle, double distance);
    // Méthode pour afficher la carte dans le terminal
    void printMap() const;

    ~Map();
};

#endif // MAP_HPP