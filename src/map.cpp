#include "../include/map.hpp"
#include <iostream>

Map::Map()
    : robotMap(1, std::vector<CellState>(1, CellState::Free)) {
}

// Fonction pour afficher la carte
void Map::printMap() const {
    for (int y = robotMap[0].size() - 1; y >= 0; --y) {  // Parcourt les lignes de bas en haut
        for (int x = 0; x < robotMap.size(); ++x) {    // Parcourt chaque colonne de gauche à droite
            switch (robotMap[x][y])
            {
            case CellState::Wall:
                std::cout << "█";
                break;
            case CellState::Free:
                std::cout << " ";
                break;
            case CellState::Unknown:
                std::cout << "?";
                break;

            default:
                break;
            }
        }
        std::cout << std::endl;
    }
}

Map::~Map() {}