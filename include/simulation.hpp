#ifndef _SIMULATION_HPP_
#define _SIMULATION_HPP_

#include "environment.hpp"
#include "robot.hpp"
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()

class Simulation {
private:
    Robot* robot;             // Pointeur vers le robot simulé
    Environment* environment; // Pointeur vers l'environnement dans lequel évolue le robot
    double xRobotStart, yRobotStart, orientationRobotStart; // Coordonnées absolues de départ du robot

public:
    // Constructeur qui initialise l'environnement et le robot
    Simulation(Robot* robot_, Environment* environment_);

    // Méthode pour initialiser la pose du robot
    void initializeRobotPose();
    // Méthode pour démarrer la simulation
    void run();

    // Getters
    double getXRobotStart() const;
    double getYRobotStart() const;
    double getOrientationRobotStart() const;
};

#endif // _SIMULATION_HPP_