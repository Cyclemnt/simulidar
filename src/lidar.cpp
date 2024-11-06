#include "../include/lidar.hpp"
#include "../include/simulation.hpp"  // Définition complète de Simulation

// Constructeur qui initialise le Lidar
Lidar::Lidar(Simulation* simulation_)
    : simulation(simulation_) {
}

// Méthode pour lire un rayon particulier
double Lidar::read(int rayID) const {
    // Récupérer la pose absolue du robot
    double x1 = simulation->getXRobotStart() + simulation->getRobot()->getX();
    double y1 = simulation->getYRobotStart() + simulation->getRobot()->getY();
    double orientation = simulation->getOrientationRobotStart() + simulation->getRobot()->getOrientation();
    // Ajouter l'ID du rayon
    orientation += (rayID - 180) * M_PI / 180;
    // Récupérer la grille de l'environnement
    Grid room = simulation->getEnvironment()->getRoom();
    // Calculer le point visible le plus loin
    double x2 = x1 + range * cos(orientation);
    double y2 = y1 + range * sin(orientation);

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

    // Parcourir la grille en traçant la ligne
    int index = 0;
    do {
        index++;
        x += xIncrement;
        y += yIncrement;
    } while (room[std::round(x)][std::round(y)] != CellState::Wall && abs(x - x1) < abs(x2) && abs(y - y1) < abs(y2));
    // Retourner la distance ou -1 si out of range
    if (abs(x - x1) >= abs(x2) || abs(y - y1) >= abs(y2)) {
        return -1.0;
    } else {
        return sqrt(abs(x - x1) * abs(x - x1) + abs(y - y1) * abs(y - y1));
    }
}

// Méthode pour lire tous les rayon
std::vector<double> Lidar::readAll() const {
    std::vector<double> readings;
    for (int id = 0; id < rayCount; id++)
    {
        readings.push_back(read(id));
    }
    return readings;
}

Lidar::~Lidar() {}