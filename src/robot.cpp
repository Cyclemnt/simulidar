#include "../include/robot.hpp"
#include <cmath>
#include <algorithm> // Pour std::clamp()

#include <iostream>

#define ANG_V 2 * M_PI
#define SPEED 4

Robot::Robot()
    : lidar(nullptr), map(nullptr), x(0.0), y(0.0), orientation(0.0), targetPos({0, 0}) {}

// Fonction pour faire avancer le robot
void Robot::move(double distance) {
    x += distance * std::cos(orientation);
    y += distance * std::sin(orientation);
    // Pour contrer les potentielles erreurs de représentation binaire des virgules flottantes
    if (fabs(floor(x + 0.5) - x) < 1e-14) x = floor(x + 0.5); // Arrondir la position du robot
    if (fabs(floor(y + 0.5) - y) < 1e-14) y = floor(y + 0.5); // Arrondir la position du robot
}

// Fonction pour faire tourner le robot
void Robot::rotate(double angle) {
    orientation += angle;
    if (orientation > 2 * M_PI) orientation -= 2 * M_PI;
    if (orientation < -2 * M_PI) orientation += 2 * M_PI;
}

// Fonction pour mettre à jour la carte du robot
void Robot::updateMap(std::vector<double> lidarMeasurements) {
    for (int i = 0; i < lidar->getRayCount(); i++) {
        double distance = lidarMeasurements[i];
        // Calculer l'angle du rayon relatif à l'orientation du robot
        double rayAngle = orientation + (i - 180) * (M_PI / 180.0);
        // NE PAS PRENDRE LES DIAGONALES ------------+
        // car l'erreur de la représentation binaire |
        // des virgules flottantes est plus impactante
        if (fabs(fmod(fabs(rayAngle), M_PI_2) - M_PI_4) < (0.034)) continue;
        // Ray casting dans la grille pour adapter l'état des cases
        map->castRayAndMarkObstacle(x, y, rayAngle, distance);
    }
}

// Méthode pour suivre la liste d'instructions
bool Robot::executeInstruction(std::pair<int, int> targetPos_) {
    if (targetPos != targetPos_) targetPos = targetPos_;
    // Case actuelle du robot
    int mapX = floor(x + 0.5) + map->getLeftExtension();
    int mapY = floor(y + 0.5) + map->getBottomExtension();
    // Position actuelle du robot sur sa carte
    double robotX = x + map->getLeftExtension();
    double robotY = y + map->getBottomExtension();
    
    // Chemin à parcourir
    int dx = targetPos.first - mapX;
    int dy = targetPos.second - mapY;

    bool achievedTarget = false;

    // Détermine l'orientation cible en fonction de dx et dy
    double targetOrientation = orientation;
    if (dx > 0) targetOrientation = 0;                   // Droite
    else if (dx < 0) targetOrientation = M_PI;           // Gauche
    else if (dy > 0) targetOrientation = M_PI / 2.0;     // Haut
    else if (dy < 0) targetOrientation = 3 * M_PI / 2.0; // Bas

    double angleDiff = targetOrientation - orientation;
    // Ajuste la différence d'angle pour être dans [-π, π]
    if (angleDiff > M_PI) angleDiff -= 2 * M_PI;
    if (angleDiff < -M_PI) angleDiff += 2 * M_PI;
    
    if (angleDiff == 0) { // Si l'orientation est bonne, avancer
        double distance = fabs(targetPos.first - robotX) + fabs(targetPos.second - robotY);
        move(std::min(distance, SPEED * timeStep));
    } else { // Sinon, tourner
        rotate(std::clamp(angleDiff, -ANG_V * timeStep, ANG_V * timeStep)); // Ajuster l'orientation
    }
    // Recalcul de la position sur la carte
    robotX = x + map->getLeftExtension();
    robotY = y + map->getBottomExtension();
    // Si correspondance avec l'objectif, alors fin
    if (targetPos.first == robotX && targetPos.second == robotY) achievedTarget = true; // Pas de déplacement nécessaire
    
    return achievedTarget;
}


// Setters
void Robot::setLidar(Lidar* lidar_) {
    lidar = lidar_;
}
void Robot::setMap(Map* map_) {
    map = map_;
}
void Robot::setTimeStep(int timeStep_) {
    timeStep = timeStep_ / 1000.0;
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

Robot::~Robot() {}