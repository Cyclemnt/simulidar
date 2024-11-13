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
    // Algorithme pour explorer efficacement
    std::vector<std::pair<Direction, int>> convertPathToInstructions(const std::vector<std::pair<int, int>>& path) const;

    // Setters
    void setLidar(Lidar* lidar_);
    void setMap(Map* map_);

    // Getters
    double getX() const;
    double getY() const;
    double getOrientation() const;
    double getDiameter() const;

    ~Robot();
};

#endif // ROBOT_HPP