#ifndef _MAP_HPP_
#define _MAP_HPP_

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
    Map(/* args */);

    // Méthode pour afficher la carte dans le terminal
    void printMap() const;

    ~Map();
};

#endif // _MAP_HPP_