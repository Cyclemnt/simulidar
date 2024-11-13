#include "../include/map.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

Map::Map()
    : robotMap(1, std::vector<CellState>(1, CellState::Free)), leftExtension(0), bottomExtension(0) {
}

// Méthode pour agrandir la carte
void Map::adjustMapBounds(int amount, Direction dir) {
    if (amount <= 0) return; // Pas besoin d'extension si amount <= 0

    int mapWidth = robotMap.size();
    int mapHeight = robotMap[0].size();

    std::vector<CellState> newCol(robotMap[0].size(), CellState::Unknown);

    switch (dir) {
        case Direction::W: // Gauche
            for (int i = 0; i < amount; ++i) {
                robotMap.insert(robotMap.begin(), newCol); // Ajoute des colonnes à gauche de chaque ligne
            }
            leftExtension += amount;
            break;

        case Direction::E:
            for (int i = 0; i < amount; ++i) {
                robotMap.push_back(newCol); // Ajoute des colonnes à droite de chaque ligne
            }
            break;

        case Direction::S:
            for (auto& row : robotMap) {
                row.insert(row.begin(), amount, CellState::Unknown); // Ajoute des lignes en bas
            }
            bottomExtension += amount;
            break;

        case Direction::N:
            for (auto& row : robotMap) {
                row.insert(row.end(), amount, CellState::Unknown); // Ajoute des lignes en haut
            }
            break;
    }
}

// Méthode pour tracer un chemin de cases vides terminé par un mur
void Map::castRayAndMarkObstacle(double startX, double startY, double rayAngle, double distance) {
    if (distance == -1) {
        distance = 30.0;
    }

    // Vecteur directeur du rayon
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    // Calcul des coordonnées relatives du point de contact du rayon
    double dx = rayDirX * distance;
    double dy = rayDirY * distance;

    // Convertir les coordonnées en indices de grille
    int x0 = std::round(startX);
    int y0 = std::round(startY);
    int x1 = std::round(dx + (dx < 0 ? -0.5 : 0.5)); // Sur estimer, pour l'extension
    int y1 = std::round(dy + (dy < 0 ? -0.5 : 0.5)); // Sur estimer, pour l'extension

    // Calculs pour les extensions dans chaque direction
    int colsToAddLeft =  -x1 - leftExtension - x0;
    int colsToAddRight = x1 - robotMap.size() + leftExtension + 1 + x0;
    int rowsToAddBottom = -y1 - bottomExtension - y0;
    int rowsToAddTop = y1 - robotMap[0].size() + bottomExtension + 1 + y0;

    // Application des extensions avec la fonction adjustMapBounds
    adjustMapBounds(colsToAddLeft, Direction::W);
    adjustMapBounds(colsToAddRight, Direction::E);
    adjustMapBounds(rowsToAddBottom, Direction::S);
    adjustMapBounds(rowsToAddTop, Direction::N);

    // Ray Casting identique au fonctionnement du Lidar
    // Mise à jour de l'état des cases

    int mapWidth = robotMap.size();
    int mapHeight = robotMap[0].size();

    // Longueur du rayon pour un déplacement unitaire en x ou y
    double rayUnitStepSizeX = sqrt(1 + (rayDirY / rayDirX) * (rayDirY / rayDirX));
    double rayUnitStepSizeY = sqrt(1 + (rayDirX / rayDirY) * (rayDirX / rayDirY));

    // Case à vérifier
    int mapCheckX = int(startX + 0.5);
    int mapCheckY = int(startY + 0.5);

    // Longueur accumulée
    double rayLengthX = 0.0;
    double rayLengthY = 0.0;

    // Pas sur chaque composante
    int stepX = 0;
    int stepY = 0;

    // Définir la direction et la distance à l'intersection de la première ligne/colonne
    if (rayDirX < 0) {
        stepX = -1;
        rayLengthX = (0.5 - mapCheckX + startX) * rayUnitStepSizeX;
    }
    else {
        stepX = 1;
        rayLengthX = (0.5 + mapCheckX - startX) * rayUnitStepSizeX;
    }
    if (rayDirY < 0) {
        stepY = -1;
        rayLengthY = (0.5 - mapCheckY + startY) * rayUnitStepSizeY;
    }
    else {
        stepY = 1;
        rayLengthY = (0.5 + mapCheckY - startY) * rayUnitStepSizeY;
    }
    
    double walkDistance = 0.0;
    while (walkDistance < distance) {
        // Walk
        if (rayLengthX < rayLengthY) {
            mapCheckX += stepX;
            walkDistance = rayLengthX;
            rayLengthX += rayUnitStepSizeX;
        }
        else {
            mapCheckY += stepY;
            walkDistance = rayLengthY;
            rayLengthY += rayUnitStepSizeY;
        }
        
        if ((mapCheckX + leftExtension) >= 0 && (mapCheckX + leftExtension) < mapWidth && (mapCheckY + bottomExtension) >= 0 && (mapCheckY + bottomExtension) < mapHeight) {
            robotMap[mapCheckX + leftExtension][mapCheckY + bottomExtension] = CellState::Free;
        }
    }

    if (distance != 30) {
        robotMap[mapCheckX + leftExtension][mapCheckY + bottomExtension] = CellState::Wall;
    }
}

// Méthode pour déterminer la prochaine case à explorer 
std::pair<int, int> Map::findNearestInterestPoint(double startX, double startY) const {
    int ShortestManhattanDistance = std::numeric_limits<int>::max();
    std::pair<int, int> interestPoint(-1, -1);
    startX += leftExtension;
    startY += bottomExtension;
    //Calcul de la case inconue la plus proche adjacente à une case libre
    for (int y = robotMap[0].size() - 1; y > 0; y--) {
        for (int x = 0; x < robotMap.size(); x++) {
            if (robotMap[x][y] == CellState::Unknown) {
                for (int i = 0; i < 4; i++) {
                    int dx = ((i + 1) % 2) * (i - 1);
                    int dy = (i % 2) * (i - 2);
                    if (x + dx >= 0 && x + dx < robotMap.size() && y + dy >= 0 && y + dy < robotMap[0].size()) {
                        if (robotMap[x + dx][y + dy] == CellState::Free) {
                            if ((abs(startX - x) + abs(startY - y)) < ShortestManhattanDistance) {
                                ShortestManhattanDistance = (abs(startX - x) + abs(startY - y));
                                interestPoint.first = x;
                                interestPoint.second = y;
                            }
                        }
                    }
                }
            }
        }
    }
    return interestPoint;
}

// Méthode pour trouver un chemin 
std::vector<std::pair<int, int>> Map::findPath(int startX, int startY, int goalX, int goalY) const {
    std::vector<std::pair<int, int>> path = {};
    return path;
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

//Getter 
Grid Map::getRobotMap() const {
    return robotMap;
}
int Map::getWidth() const {
    return robotMap.size();
}
int Map::getHeight() const {
    return robotMap[0].size();
}
int Map::getLeftExtension() const {
    return leftExtension;
}
int Map::getBottomExtension() const {
    return bottomExtension;
}

Map::~Map() {}