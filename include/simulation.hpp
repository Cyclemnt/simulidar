#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "environment.hpp"
#include "robot.hpp"
#include "lidar.hpp"
#include "map.hpp"

class Simulation {
private:
    Environment* environment;  // Pointeur vers l'environnement dans lequel évolue le robot
    Map* map;                  // Pointeur vers la carte du robot
    Robot* robot;              // Pointeur vers le robot simulé
    Lidar* lidar;              // Pointeur vers le lidar simulé
    double xRobotStart, yRobotStart, orientationRobotStart, maxRange;;  // Coordonnées absolues de départ du robot

public:
    // Constructeur qui initialise l'environnement et le robot
    Simulation();

    // Méthode pour initialiser la pose du robot
    void initializeRobotPose();
    // Méthode pour démarrer la simulation
    void run();

    // Méthode pour afficher la simulation
    void displaySimulation(int scaleFactor) const;

    // Méthode pour afficher la carte relative
    void displayRobotMap(int scaleFactor) const;

    // Getters
    Environment* getEnvironment() const;
    Robot* getRobot() const;
    double getXRobotStart() const;
    double getYRobotStart() const;
    double getOrientationRobotStart() const;

    ~Simulation();
};

#endif // SIMULATION_HPP
