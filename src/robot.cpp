#include "../include/robot.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>      // std::setprecision

#define ANG_V M_PI/2.0
#define SPEED 1

Robot::Robot()
    : lidar(nullptr), map(nullptr), x(0.0), y(0.0), orientation(0.0), targetPos({0, 0}) {}

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

// Méthode pour suivre la liste d'instructions
bool Robot::executeInstruction(std::pair<int, int> targetPos_) {
    if (targetPos != targetPos_) { targetPos = targetPos_; }
    // Case actuelle du robot
    int mapX = floor(x + 0.5) + map->getLeftExtension();
    int mapY = floor(y + 0.5) + map->getBottomExtension();
    // Position actuelle du robot sur sa carte
    double robotX = x + map->getLeftExtension();
    double robotY = y + map->getBottomExtension();
    // Chemin à parcourir
    int dx = round(targetPos.first - mapX);
    int dy = round(targetPos.second - mapY);

    bool achievedTarget = false;

    // Détermine l'orientation cible en fonction de dx et dy
    double targetOrientation = orientation;
    if (dx > 0) targetOrientation = 0;                   // Droite
    else if (dx < 0) targetOrientation = M_PI;           // Gauche
    else if (dy > 0) targetOrientation = M_PI / 2.0;     // Haut
    else if (dy < 0) targetOrientation = 3 * M_PI / 2.0; // Bas

    double diff = targetOrientation - orientation;
    
    // Ajuste la différence d'angle pour être dans [-π, π]
    if (diff > M_PI) diff -= 2 * M_PI;
    if (diff < -M_PI) diff += 2 * M_PI;
    
    if (diff == 0) { // Si l'orientation est bonne, avancer
        move(std::min(std::max(fabs(targetPos.first - robotX), fabs(targetPos.second - robotY)), SPEED * timeStep)); // Orientation correcte, avancer
    } else { // Sinon, tourner
        rotate(std::clamp(diff, -ANG_V * timeStep, ANG_V * timeStep)); // Ajuster l'orientation
    }
    // Recalcul de la position sur la carte
    robotX = x + map->getLeftExtension();
    robotY = y + map->getBottomExtension();
    // Si correspondance avec l'objectif, alors fin
    if (targetPos.first == robotX && targetPos.second == robotY) {
        achievedTarget = true; // Pas de déplacement nécessaire
    }
    
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
void Robot::setX(double x_) {
    x = x_;
}
void Robot::setY(double y_) {
    y = y_;
}
void Robot::setOrientation(double orientation_) {
    orientation = orientation_;
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