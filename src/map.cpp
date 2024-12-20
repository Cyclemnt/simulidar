#include "../include/map.hpp"
#include <iostream> // pour afficher en terminal
#include <cmath>
#include <map>   // pour aStar
#include <set>   // pour aStar
#include <queue> // pour aStar
#include <limits> // pour std::numeric_limits<double>::infinity()

using Types::CellState;

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
            for (int i = 0; i < amount; ++i) robotMap.insert(robotMap.begin(), newCol); // Ajoute des colonnes à gauche de chaque ligne
            leftExtension += amount;
            break;
        case Direction::E:
            for (int i = 0; i < amount; ++i) robotMap.push_back(newCol); // Ajoute des colonnes à droite de chaque ligne
            break;
        case Direction::S:
            for (auto& row : robotMap) row.insert(row.begin(), amount, CellState::Unknown); // Ajoute des lignes en bas
            bottomExtension += amount;
            break;
        case Direction::N:
            for (auto& row : robotMap) row.insert(row.end(), amount, CellState::Unknown); // Ajoute des lignes en haut
            break;
    }
}

// Méthode pour tracer un chemin de cases vides terminé par un mur
void Map::castRayAndMarkObstacle(double startX, double startY, double rayAngle, double distance) {
    if (distance == -1) distance = LIDAR_MAX_RANGE;

    // Vecteur directeur du rayon
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    // Calcul des coordonnées relatives du point de contact du rayon
    double dx = rayDirX * distance;
    double dy = rayDirY * distance;

    // Convertir les coordonnées en indices de grille
    int x0 = std::round(startX);
    int y0 = std::round(startY);
    int x1 = std::round(dx + (dx < 0 ? -1 : 1)); // Sur estimer, pour l'extension
    int y1 = std::round(dy + (dy < 0 ? -1 : 1)); // Sur estimer, pour l'extension

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
    int mapCheckX = floor(startX + 0.5);
    int mapCheckY = floor(startY + 0.5);

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
    while (walkDistance < (distance - 1e-12)) { // 1e-12 pour contourner les erreurs dues au binaire
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
        // Sur le chemin du rayon, placer des cases libres
        if ((mapCheckX + leftExtension) >= 0 && (mapCheckX + leftExtension) < mapWidth && (mapCheckY + bottomExtension) >= 0 && (mapCheckY + bottomExtension) < mapHeight) {
            robotMap[mapCheckX + leftExtension][mapCheckY + bottomExtension] = CellState::Free;
        }
    }
    // Si mesure dans les limites, placer un mur à la fin
    if (distance != LIDAR_MAX_RANGE) {
        robotMap[mapCheckX + leftExtension][mapCheckY + bottomExtension] = CellState::Wall;
    }
}

// Méthode pour déterminer la prochaine case à explorer 
std::pair<int, int> Map::findNearestInterestPoint(double startX, double startY) const {
    int ShortestManhattanDistance = std::numeric_limits<int>::max();
    std::pair<int, int> interestPoint(-1, -1);
    startX += leftExtension;
    startY += bottomExtension;
    // Calcul de la case inconue la plus proche adjacente à une case libre, en distance de Manhattan
    for (int y = robotMap[0].size() - 1; y >= 0; y--) {
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

// Algorithme A* pour trouver le chemin le plus court entre "start" et "goal"
std::vector<std::pair<int, int>> Map::aStar(std::pair<int, int> start, std::pair<int, int> goal) const {
    // Algorithme de recherche A* =================================
    // https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode

    int width = robotMap.size();          // Largeur de la carte (nombre de colonnes)
    int height = robotMap[0].size();      // Hauteur de la carte (nombre de lignes)

    // Ensemble des nœuds à explorer, initialisé avec le nœud de départ
    std::set<std::pair<int, int>> openSet = {start};
    
    // Dictionnaire pour conserver le chemin le plus efficace trouvé pour chaque nœud
    std::map<std::pair<int, int>, std::pair<int, int>> cameFrom;
    
    // Initialisation de gScore avec Infinity pour tous les nœuds sauf le départ
    std::map<std::pair<int, int>, double> gScore;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            gScore[{x, y}] = std::numeric_limits<double>::infinity();  // Coût infini pour les nœuds non encore explorés
        }
    }
    gScore[start] = 0;  // Coût de départ est zéro pour le point de départ

    // Initialisation de fScore avec Infinity, sauf pour le départ où fScore est la distance de Manhattan jusqu'au but
    std::map<std::pair<int, int>, double> fScore;
    fScore[start] = std::abs(start.first - goal.first) + std::abs(start.second - goal.second);

    // File de priorité pour les nœuds à explorer, triée par fScore (priorité aux nœuds avec le coût estimé le plus bas)
    auto cmp = [&fScore](std::pair<int, int> left, std::pair<int, int> right) { return fScore[left] > fScore[right]; };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> openQueue(cmp);
    openQueue.push(start);

    while (!openQueue.empty()) {
        // Récupère le nœud avec le coût estimé (fScore) le plus bas
        std::pair<int, int> current = openQueue.top();
        openQueue.pop();

        // Si on atteint le but, reconstruire et retourner le chemin
        if (current == goal) {
            std::vector<std::pair<int, int>> totalPath = {current};
            while (cameFrom.find(current) != cameFrom.end()) {
                current = cameFrom[current];
                totalPath.insert(totalPath.begin(), current);  // Insère au début pour obtenir l'ordre de départ vers l'arrivée
            }
            return totalPath;  // Retourne le chemin complet
        }

        // Retire le nœud actuel de openSet, car il a été exploré
        openSet.erase(current);

        // Génère les voisins orthogonaux (haut, bas, gauche, droite)
        std::vector<std::pair<int, int>> neighbors = {
            {current.first + 1, current.second},
            {current.first - 1, current.second},
            {current.first, current.second + 1},
            {current.first, current.second - 1}
        };

        // Parcourt chaque voisin du nœud actuel
        for (std::pair<int, int> neighbor : neighbors) {
            // Vérifie si le voisin est dans les limites de la grille
            if (neighbor.first < 0 || neighbor.first >= width || neighbor.second < 0 || neighbor.second >= height) {
                continue;  // Ignore le voisin s'il est hors des limites
            }

            // Ignore le voisin s'il est un mur
            if (robotMap[neighbor.first][neighbor.second] == CellState::Wall) {
                continue;
            }

            // Calcule le gScore provisoire du voisin (coût depuis le départ jusqu'à ce voisin)
            double tentative_gScore = gScore[current] + 1;  // Coût de déplacement = 1 pour les déplacements orthogonaux

            // Si le nouveau chemin est plus court ou si le voisin n'a jamais été visité
            if (tentative_gScore < gScore[neighbor]) {
                // Met à jour le chemin optimal pour atteindre le voisin
                cameFrom[neighbor] = current;
                
                // Met à jour le gScore et le fScore pour le voisin
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = tentative_gScore + std::abs(neighbor.first - goal.first) + std::abs(neighbor.second - goal.second);

                // Ajoute le voisin à openQueue s'il n'est pas déjà dans openSet
                if (openSet.find(neighbor) == openSet.end()) {
                    openSet.insert(neighbor);
                    openQueue.push(neighbor);
                }
            }
        }
    }
    
    // Retourne un chemin vide si l'objectif n'est pas atteint
    return {};
}

// Fonction pour afficher la carte dans le terminal
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