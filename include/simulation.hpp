#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "environment.hpp"
#include "robot.hpp"
#include "lidar.hpp"
#include "map.hpp"

/// \brief Chef d'orchestre de la simulation.
class Simulation {
private:
    Environment* environment;  // Pointeur vers l'environnement dans lequel évolue le robot
    Map* map;                  // Pointeur vers la carte du robot
    Robot* robot;              // Pointeur vers le robot simulé
    Lidar* lidar;              // Pointeur vers le lidar simulé
    double xRobotStart, yRobotStart, orientationRobotStart;  // Coordonnées absolues de départ du robot
    int timeStep;              // Temps entre chaque état de simulation

public:
    // Constructeur qui initialise l'environnement et le robot
    Simulation();

    /// \brief Démarrer la simulation.
    void run();
    /// \brief Initialiser la pose du robot
    void initializeRobotPose();
    /// \brief Afficher la simulation
    /// \param scaleFactor Facteur d'agrandissement de la matrice à afficher (px).
    /// \param plan Carte à afficher.
    void displaySimulation(int scaleFactor, Grid plan) const;
    /// \brief Afficher en 3D la vue du robot avec le raycasting 
    /// \param plan Carte à afficher.
    /// \param WindowWidth Largeur de fenêtre.
    /// \param WindowHeight Hauteur de fenêtre.
    /// \param wallheight Hauteur des murs.
    /// \param fov Champ de vision (°).
    void displayRaycasting(Grid plan, int WindowWidth, int WindowHeight, int wallheight, int fov) const;
    /// \brief Afficher les trois fenêtres
    void displayAll();

    // Getters
    Environment* getEnvironment() const;
    Robot* getRobot() const;
    double getXRobotStart() const;
    double getYRobotStart() const;
    double getOrientationRobotStart() const;


    ~Simulation();
};

#endif // SIMULATION_HPP
