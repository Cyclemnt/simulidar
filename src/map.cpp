#include "../include/map.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

Map::Map()
    : robotMap(20, std::vector<CellState>(20, CellState::Free)), leftExtension(0), bottomExtension(0) {
}

// Méthode pour tracer un chemin de cases vides terminé par un mur
void Map::traceAndUpdateGrid(double startX, double startY, double rayAngle, double distance) {
/*
    // Ajouter la distance entre bord et centre de case en fonction de l'orientation
    if ((-M_PI <= rayAngle && rayAngle < -3 * M_PI / 4) || (3 * M_PI / 4 <= rayAngle && rayAngle < M_PI)) {  // left
        distance += 0.5 / -std::cos(rayAngle);
    }
    else if (-3 * M_PI / 4 <= rayAngle && rayAngle < -M_PI / 4) {  // bottom
        distance += 0.5 / -std::sin(rayAngle);
    }
    else if (-M_PI / 4 <= rayAngle && rayAngle <  M_PI / 4) {      // right
        distance += 0.5 / std::cos(rayAngle);
    }
    else if (M_PI / 4 <= rayAngle && rayAngle <  3 * M_PI / 4) {   // top
        distance += 0.5 / std::sin(rayAngle);
    }
*/

    // Calcul des coordonnées relatives du point de contact du rayon
    double dx = cos(rayAngle) * distance;
    double dy = sin(rayAngle) * distance;

    // Convertir les coordonnées en indices de grille
    int x0 = std::round(startX);
    int y0 = std::round(startY);
    int x1 = std::round((dx + (dx < 0 ? -0.5 : 0)) * 2) / 2; // N'enlève pas toutes les cases mal placées
    int y1 = std::round((dy + (dy < 0 ? -0.5 : 0)) * 2) / 2; // N'enlève pas toutes les cases mal placées

std::cout << std::round(rayAngle * 180 / M_PI) << '\t';
std::cout << std::setprecision(13) << "(" << dx << ", " << dy << ")" << '\t' << "(" << x1 << ", " << y1 << ") " << distance << " " << rayAngle << std::endl; 
robotMap[x1 + 10][y1 + 10] = CellState::Wall;
/*
    // Extension à gauche si la cible est hors de la grille à gauche
    if ((x0 + leftExtension + x1) < 0) {
        int colsToAdd = -(x0 + leftExtension + x1);
        // Ajoute "colsToAdd" colonnes à gauche de chaque ligne
        std::vector<CellState> newCol(robotMap[0].size(), CellState::Unknown);
        for (int i = 0; i < colsToAdd; ++i) {
            robotMap.insert(robotMap.begin(), newCol);
        }
        leftExtension += colsToAdd;
    }
    // Extension à droite si la cible est hors de la grille à droite
    if ((x0 + leftExtension + x1) >= robotMap.size()) {
        int colsToAdd = (x0 + leftExtension + x1) - robotMap.size() + 1;
        // Ajoute "colsToAdd" colonnes à droite de chaque ligne
        std::vector<CellState> newCol(robotMap[0].size(), CellState::Unknown);
        for (int i = 0; i < colsToAdd; ++i) {
            robotMap.push_back(newCol);
        }
    }
    
    // Extension en bas si la cible est hors de la grille en dessous
    if ((y0 + bottomExtension + y1) < 0) {
        int linesToAdd = -(y0 + bottomExtension + y1);
        // Ajoute "linesToAdd" lignes en dessous 
        for (auto& row : robotMap) {
            row.insert(row.begin(), linesToAdd, CellState::Unknown);
        }
        bottomExtension += linesToAdd;
    }
    // Extension en haut si la cible est hors de la grille au dessus
    if ((y0 + leftExtension + y1) >= robotMap[0].size()) {
        int linesToAdd = (y0 + bottomExtension + y1) - robotMap[0].size() + 1;
        // Ajoute "rowsToAdd" colonnes à droite de chaque ligne
        for (auto& row : robotMap) {
            row.insert(row.end(), linesToAdd, CellState::Unknown);
        }
    }   
*/

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