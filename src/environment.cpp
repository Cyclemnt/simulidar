#include "../include/environment.hpp"
#include <iostream>
#include <cmath>

using Types::CellState;

Environment::Environment(int width_, int height_)
    : width(width_), height(height_), room(width_, std::vector<CellState>(height_, CellState::Free)) {
        // Placer les murs en bordure
        for (int i = 0; i < width; i++) {
            room[i][0] = CellState::Wall;
            room[i][height - 1] = CellState::Wall;
        }
        for (int i = 0; i < height; i++) {
            room[0][i] = CellState::Wall;
            room[width - 1][i] = CellState::Wall;
        }
    }

// Générer des obstacles aléatoires
void Environment::generateRandomObstacles(int number, int maxSize) {
    srand(time(0));
    for (int i = 0; i < number; i++) {
        // Générer des dimensions aléatoire pour l'obstacle
        int obstacleWidth = rand() % maxSize + 1;
        int obstacleHeight = rand() % maxSize + 1;
        // Générer une position aléatoire
        int x = 0, y = 0;
        do {
            x = rand() % (width - 1 - obstacleWidth) + 1;
            y = rand() % (height - 1 - obstacleHeight) + 1;
        } while (room[x][y] != CellState::Free);
        // Placer les murs dans la grille
        for (int j = x; j < x + obstacleWidth; j++) {
            for (int k = y; k < y + obstacleHeight; k++) {
                room[j][k] = CellState::Wall;
            }
        }
    }
}

// Fonction pour afficher la grille dans le terminal
void Environment::printRoom() const {
        for (int y = room[0].size() - 1; y >= 0; --y) {  // Parcourt les lignes de bas en haut
        for (int x = 0; x < room.size(); ++x) {          // Parcourt chaque colonne de gauche à droite
            switch (room[x][y]) {
            case CellState::Wall: std::cout << "█";
                break;
            case CellState::Free: std::cout << " ";
                break;
            case CellState::Unknown: std::cout << "?";
                break;
            }
        }
        std::cout << std::endl;
    }    
}

// Getters
Grid Environment::getRoom() const {
    return room;
}
int Environment::getWidth() const {
    return width;
}
int Environment::getHeight() const {
    return height;
}

Environment::~Environment() {}