#ifndef _SIMULATION_HPP_
#define _SIMULATION_HPP_

#include "environment.hpp"
#include "robot.hpp"
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()

class Simulation {
private:
    static Simulation* sim;   // Pointeur statique vers l'unique simulation
    //Lidar* lidar;
    Robot* robot;             // Pointeur vers le robot simulé
    Environment* environment; // Pointeur vers l'environnement dans lequel évolue le robot
    double xRobotStart, yRobotStart, orientationRobotStart; // Coordonnées absolues de départ du robot

public:
    // Constructeur qui initialise l'environnement et le robot
    Simulation(Environment* environment_, Robot* robot_);

    // Méthode pour initialiser toute la simulation
    void initializeSimulation();
    // Méthode pour initialiser la pose du robot
    void initializeRobotPose();
    // Méthode pour démarrer la simulation
    void run();

    // Getters
    static Simulation* getSim();
    Robot* getRobot() const;
    Environment* getEnvironment() const;
    double getXRobotStart() const;
    double getYRobotStart() const;
    double getOrientationRobotStart() const;

    ~Simulation();
};

#endif // _SIMULATION_HPP_