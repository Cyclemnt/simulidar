#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "map.hpp"
#include <cmath>

class Robot
{
private:
    double x, y;        // Position relative du robot
    double orientation; // Orientation relative du robot
    double diameter;    // Diamètre du robot (dm)
    Map* map;           // Pointeur vers la carte du robot
public:
    // Constructeur par défaut
    Robot();
    // Constructeurs avec paramètres
    Robot(double diameter_);

    // Fonction pour faire avancer le robot
    void move(double distance);
    // Fonction pour faire tourner le robot
    void rotate(double angle);
    // Algorithme pour explorer efficacement
    void explore();

    // Getters
    double getX() const;
    double getY() const;
    double getOrientation() const;
    double getDiameter() const;

    ~Robot();
};

#endif // _ROBOT_HPP_