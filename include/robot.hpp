#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "map.hpp"
#include "lidar.hpp"

class Robot
{
private:
    Map* map;           // Pointeur vers la carte du robot
    Lidar* lidar;       // Pointeur vers le lidar
    double x, y;        // Position relative du robot
    double orientation; // Orientation relative du robot
    double diameter;    // Diamètre du robot (dm)
    int timeStep;       // Temps entre chaque calcul d'état
public:
    // Constructeur par défaut
    Robot();
    // Constructeurs avec paramètres
    Robot(double diameter_);

    // Fonction pour faire avancer le robot
    void move(double distance);
    // Fonction pour faire tourner le robot
    void rotate(double angle);
    // Fonction pour mettre à jour sa carte
    void updateMap(std::vector<double> lidarMeasures);
    // Algorithme pour convertir un chemin en instructions
    std::vector<std::pair<Direction, int>> convertPathToInstructions(const std::vector<std::pair<int, int>>& path) const;
    // Méthode pour suivre la liste d'instructions
    void followInstructions(std::vector<std::pair<Direction, int>>);

    // Setters
    void setLidar(Lidar* lidar_);
    void setMap(Map* map_);
    void setTimeStep(int timeStemp_);

    // Getters
    double getX() const;
    double getY() const;
    double getOrientation() const;
    double getDiameter() const;

    ~Robot();
};

#endif // ROBOT_HPP