#include "../include/map.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

Map::Map()
    : robotMap(1, std::vector<CellState>(1, CellState::Free)), leftExtension(0), bottomExtension(0) {
}

// Méthode pour tracer un chemin de cases vides terminé par un mur
void Map::traceAndUpdateGrid(double startX, double startY, double rayAngle, double distance) {
    // Calcul des coordonnées relatives du point de contact du rayon
    double dx = cos(rayAngle) * distance;
    double dy = sin(rayAngle) * distance;

    // Convertir les coordonnées en indices de grille
    int x0 = std::round(startX);
    int y0 = std::round(startY);
    int x1 = std::round(dx + (dx < 0 ? -0.5 : 0.5)); // N'enlève pas toutes les cases mal placées
    int y1 = std::round(dy + (dy < 0 ? -0.5 : 0.5)); // N'enlève pas toutes les cases mal placées

    // Extension à gauche si la cible est hors de la grille à gauche
    int colsToAddLeft =  -x1 - leftExtension - x0;
    if (colsToAddLeft > 0) {
        // Ajoute "colsToAdd" colonnes à gauche de chaque ligne
        std::vector<CellState> newCol(robotMap[0].size(), CellState::Unknown);
        for (int i = 0; i < colsToAddLeft; ++i) {
            robotMap.insert(robotMap.begin(), newCol);
        }
        leftExtension += colsToAddLeft;
    }

    // Extension à droite si la cible est hors de la grille à droite
    int colsToAddRight = x1 - (robotMap.size() - leftExtension - 1 - x0);
    if (colsToAddRight > 0) {
        // Ajoute "colsToAdd" colonnes à droite de chaque ligne
        std::vector<CellState> newCol(robotMap[0].size(), CellState::Unknown);
        for (int i = 0; i < colsToAddRight; ++i) {
            robotMap.push_back(newCol);
        }
    }
    
    // Extension en bas si la cible est hors de la grille en dessous
    int rowsToAddBottom = -y1 - bottomExtension - y0;
    if (rowsToAddBottom > 0) {
        // Ajoute "rowsToAdd" lignes en dessous 
        for (auto& row : robotMap) {
            row.insert(row.begin(), rowsToAddBottom, CellState::Unknown);
        }
        bottomExtension += rowsToAddBottom;
    }
    // Extension en haut si la cible est hors de la grille au dessus
    int rowsToAddTop = y1 - (robotMap[0].size() - (bottomExtension + y0 + 1));
    if (rowsToAddTop > 0) {
        // Ajoute "rowsToAdd" colonnes à droite de chaque ligne
        for (auto& row : robotMap) {
            row.insert(row.end(), rowsToAddTop, CellState::Unknown);
        }
    }
}

// Fonction pour afficher la carte
void Map::printMap() const {
    int width = robotMap.size();
    int height = width > 0 ? robotMap[0].size() : 0;
    
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    for (int y = height - 1; y >= 0; --y) {
        std::cout << "|";
        for (int x = 0; x < width; ++x) {
            switch (robotMap[x][y]) {
                case CellState::Wall: std::cout << "█"; break;
                case CellState::Free: std::cout << " "; break;
                case CellState::Unknown: std::cout << "?"; break;
                default: break;
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
}

Map::~Map() {}