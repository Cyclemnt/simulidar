#ifndef MAP_HPP
#define MAP_HPP

#include "types.hpp"
#include <iostream>
#include <vector>

using Types::CellState;
using Types::Grid;

class Map
{
private:
    Grid robotMap;  // Occupancy grid
public:
    // Constructeur qui initialise le carte du robot
    Map();

    // Méthode pour afficher la carte dans le terminal
    void printMap() const;

    ~Map();
};

#endif // MAP_HPP