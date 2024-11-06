#include "../include/environment.hpp"

Environment::Environment(int width_, int height_)
    : width(width_), height(height_), room(width_, std::vector<CellState>(height_, CellState::Free)) {
        // Placer les murs en bordure
        for (int i = 0; i < width; i++)
        {
            room[i][0] = CellState::Wall;
            room[i][height - 1] = CellState::Wall;
        }
        for (int i = 0; i < height; i++)
        {
            room[0][i] = CellState::Wall;
            room[width - 1][i] = CellState::Wall;
        }
    }

// Générer des obstacles aléatoires
void Environment::generateRandomObstacles(int number, int maxSize) {
    srand(time(0));
    for (int i = 0; i < number; i++)
    {
        // Générer des dimensions aléatoire pour l'obstacle
        int obstacleWidth = rand() % maxSize + 1;
        int obstacleHeight = rand() % maxSize + 1;
        // Générer une position aléatoire
        int x = 0, y = 0;
        do
        {
            x = rand() % (width - 1 - obstacleWidth) + 1;
            y = rand() % (height - 1 - obstacleHeight) + 1;
        } while (room[x][y] != CellState::Free);
        // Placer les murs dans la grille
        for (int j = x; j < x + obstacleWidth; j++)
        {
            for (int k = y; k < y + obstacleHeight; k++)
            {
                room[j][k] = CellState::Wall;
            }
        }
    }
}

// Algorithme DDA pour tracer une ligne entre deux points et remplir la grille
void Environment::drawLineDDA(int x1, int y1, int x2, int y2) {
    // Différences dans les coordonnées
    double dx = x2 - x1;
    double dy = y2 - y1;

    // Calculer le nombre de pas nécessaires pour marcher sur la ligne
    int steps = std::max(std::abs(dx), std::abs(dy));

    // Incréments par pas dans chaque direction
    double xIncrement = dx / steps;
    double yIncrement = dy / steps;

    // Position de départ
    double x = x1;
    double y = y1;

    // Remplir la grille en traçant la ligne
    for (int i = 0; i <= steps; i++) {
        // Placer un 1 dans la cellule correspondante de la grille
        if (x >= 0 && x < room.size() && y >= 0 && y < room[0].size()) {
            room[std::round(x)][std::round(y)] = CellState::Wall;
        }
        // Avancer dans la direction du prochain point
        x += xIncrement;
        y += yIncrement;
    }
}

// Vérifier si une cellule est libre pour placer le robot
bool Environment::isCellFree(int x, int y, double robotDiameter) const {
    // Vérifier les cellules dans un carré de taille robotDiameter centré autour de (x, y)
    
    int radius = std::round(robotDiameter / 2);

    for (int i = y - radius; i <= y + radius; ++i) {
        for (int j = x - radius; j <= x + radius; ++j) {
            // On s'assure qu'on est bien dans la grille et que la cellule est libre (0)
            if (i < 0 || i >= room.size() || j < 0 || j >= room[0].size() || room[i][j] != CellState::Free) {
                return false;  // Hors limites ou occupé
            }
        }
    }
    return true;  // Toutes les cellules sont libres
}

// Fonction pour afficher la grille
void Environment::printRoom() const {
        for (int y = room[0].size() - 1; y >= 0; --y) {  // Parcourt les lignes de bas en haut
        for (int x = 0; x < room.size(); ++x) {    // Parcourt chaque colonne de gauche à droite
            switch (room[x][y])
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