#include "../include/lidar.hpp"
#include "../include/simulation.hpp"  // Définition complète de Simulation
#include <cmath>
#include <iostream>

// Constructeur qui initialise le Lidar
Lidar::Lidar(Simulation* simulation_)
    : simulation(simulation_) {
}

// Méthode pour lire un rayon particulier
double Lidar::read(int rayID) const {
    // Algorithme DDA ==========================
    // https://lodev.org/cgtutor/raycasting.html

    // Récupérer la carte de l'environnement
    Grid room = simulation->getEnvironment()->getRoom();
    int roomSizeX = simulation->getEnvironment()->getWidth();
    int roomSizeY = simulation->getEnvironment()->getHeight();

    // Récupérer la pose absolue du robot
    double rayStartX = simulation->getXRobotStart() + simulation->getRobot()->getX();
    double rayStartY = simulation->getYRobotStart() + simulation->getRobot()->getY();
    double orientation = simulation->getOrientationRobotStart() + simulation->getRobot()->getOrientation();
    
    // Angle du rayon en fonction de rayID
    double rayAngle = orientation + (rayID - 180) * (M_PI / 180.0);
    
    // Vecteur directeur du rayon
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    // Longueur du rayon pour un déplacement unitaire en x ou y
    double rayUnitStepSizeX = sqrt(1 + (rayDirY / rayDirX) * (rayDirY / rayDirX));
    double rayUnitStepSizeY = sqrt(1 + (rayDirX / rayDirY) * (rayDirX / rayDirY));

    // Case à vérifier
    double mapCheckX = int(rayStartX + 0.5);
    double mapCheckY = int(rayStartY + 0.5);

    // Longueur accumulée
    double rayLengthX = 0.0;
    double rayLengthY = 0.0;

    // Pas sur chaque composante
    double stepX = 0.0;
    double stepY = 0.0;

    // Définir la direction et la distance à l'intersection de la première ligne/colonne
    if (rayDirX < 0) {
        stepX = -1;
        rayLengthX = (0.5 - mapCheckX + rayStartX) * rayUnitStepSizeX;
    } else {
        stepX = 1;
        rayLengthX = (0.5 + mapCheckX - rayStartX) * rayUnitStepSizeX;
    }
    if (rayDirY < 0) {
        stepY = -1;
        rayLengthY = (0.5 - mapCheckY + rayStartY) * rayUnitStepSizeY;
    } else {
        stepY = 1;
        rayLengthY = (0.5 + mapCheckY - rayStartY) * rayUnitStepSizeY;
    }
    
    bool tileFound = false;
    float distance = 0.0;
    while (!tileFound && distance < maxRange)
    {
        // Walk
        if (rayLengthX < rayLengthY)
        {
            mapCheckX += stepX;
            distance = rayLengthX;
            rayLengthX += rayUnitStepSizeX;
        }
        else
        {
            mapCheckY += stepY;
            distance = rayLengthY;
            rayLengthY += rayUnitStepSizeY;
        }
        
        if (mapCheckX >= 0 && mapCheckX < roomSizeX && mapCheckY >= 0 && mapCheckY < roomSizeY)
        {
            if (room[mapCheckX][mapCheckY] == CellState::Wall)
            {
                tileFound = true;
            }
        }
    }
    
    double intersectionX = 0.0;
    double intersectionY = 0.0;
    if (tileFound)
    {
        intersectionX = rayStartX + rayDirX * distance;
        intersectionY = rayStartY + rayDirY * distance;
        return distance;
    }
    else
    {
        return -1.0;
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