#include "../include/robot.hpp"
#include <cmath>

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
void Robot::updateMap(std::vector<double> lidarMeasures) {}

// Algorithme pour explorer efficacement
void Robot::explore() {}

// Setters
void Robot::setLidar(Lidar* lidar_) {
    lidar = lidar_;
}
void Robot::setMap(Map* map_) {
    map = map_;
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