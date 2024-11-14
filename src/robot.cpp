#include "../include/robot.hpp"
#include <cmath>
#include <iostream>

Robot::Robot()
    : lidar(nullptr), map(nullptr), x(0.0), y(0.0), orientation(0.0), diameter(1.0) {}

Robot::Robot(double diameter_)
    : lidar(nullptr), map(nullptr), x(0.0), y(0.0), orientation(0.0), diameter(diameter_) {}

// Fonction pour faire avancer le robot
void Robot::move(double distance) {
    x += distance * std::cos(orientation);
    y += distance * std::sin(orientation);
}

// Fonction pour faire tourner le robot
void Robot::rotate(double angle) {
    orientation = fmod((orientation + angle), (2 * M_PI));
}

// Fonction pour mettre à jour la carte du robot
void Robot::updateMap(std::vector<double> lidarMeasurements) {
    for (int i = 0; i < lidar->getRayCount(); i++) {
        double distance = lidarMeasurements[i];
        // Calculer l'angle du rayon relatif à l'orientation du robot
        double rayAngle = orientation + (i - 180) * (M_PI / 180.0);

        // Ray casting dans la grille pour adapter l'état des cases
        map->castRayAndMarkObstacle(x, y, rayAngle, distance);
    }
}

// Algorithme pour convertir un chemin en instructions
std::vector<std::pair<Direction, int>> Robot::convertPathToInstructions(const std::vector<std::pair<int, int>>& path) const {
    std::vector<std::pair<Direction, int>> instructions;
    if (path.empty()) return instructions;

    // Initialisation de la première direction et distance
    Direction currentDir;
    int currentDistance = 1;

    for (size_t i = 1; i < path.size(); ++i) {
        int dx = path[i].first - path[i - 1].first;
        int dy = path[i].second - path[i - 1].second;

        // Déterminer la direction du déplacement
        Direction newDir;
        if (dx == 0 && dy == 1) newDir = Direction::N;
        else if (dx == 0 && dy == -1) newDir = Direction::S;
        else if (dx == 1 && dy == 0) newDir = Direction::E;
        else if (dx == -1 && dy == 0) newDir = Direction::W;
        else continue; // Ignore tout mouvement non valide (diagonal, etc.)

        // Si la direction change, on ajoute l'instruction courante et on réinitialise
        if (i == 1 || newDir != currentDir) {
            if (i != 1) instructions.push_back({currentDir, currentDistance});
            currentDir = newDir;
            currentDistance = 1;
        } else {
            // Si la direction reste la même, on augmente la distance
            ++currentDistance;
        }
    }

    // Ajouter la dernière instruction
    instructions.push_back({currentDir, currentDistance});
    return instructions;
}

// Méthode pour suivre la liste d'instructions
void Robot::followInstructions(std::vector<std::pair<Direction, int>>) {

}

// Setters
void Robot::setLidar(Lidar* lidar_) {
    lidar = lidar_;
}
void Robot::setMap(Map* map_) {
    map = map_;
}
void Robot::setTimeStep(int timeStep_) {
    timeStep = timeStep_;
}

// Getters
double Robot::getX() const {
    return x;
}
double Robot::getY() const {
    return y;
}
double Robot::getOrientation() const {
    return orientation;
}
double Robot::getDiameter() const {
    return diameter;
}

Robot::~Robot() {}