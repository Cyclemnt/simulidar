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
    std::pair<int, int> targetPos; // Position cible sur la carte du robot
    double timeStep;    // Temps entre chaque état de simulation
public:
    // Constructeur par défaut
    Robot();

    // Fonction pour faire avancer le robot
    void move(double distance);
    // Fonction pour faire tourner le robot
    void rotate(double angle);
    // Fonction pour mettre à jour sa carte
    void updateMap(std::vector<double> lidarMeasures);
    // Méthode pour exécuter l'instruction (s'orienter et avancer)
    bool executeInstruction(std::pair<int, int> targetPos_);

    // Setters
    void setLidar(Lidar* lidar_);
    void setMap(Map* map_);
    void setTimeStep(int timeStemp_);

    // Getters
    double getX() const;
    double getY() const;
    double getOrientation() const;

    ~Robot();
};

#endif // ROBOT_HPP