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
    /// \brief Ce constructeur initialise les principaux éléments de la simulation : le point de départ et l'orientation du robot, ainsi que le pas de temps utilisé pour le déroulement de la simulation.
    Simulation();

    /// \brief Démarrer la simulation.
    /// Cette méthode lance la simulation et gère la logique principale du déplacement et de l'exploration du robot.
    void run();
    /// \brief Initialiser la pose du robot.
    /// Cette méthode positionne le robot dans une cellule libre aléatoire de l'environnement.
    void initializeRobotPose();
    /// \brief Afficher la simulation
    /// Cette méthode affiche l'état d'une grille donnée (environnement ou carte du robot) avec une échelle définie.
    /// \param scaleFactor Facteur d'agrandissement de la matrice à afficher (px).
    /// \param plan Carte à afficher.
    void displaySimulation(int scaleFactor, Grid plan) const;
    /// \brief Afficher en 3D la vue du robot avec le raycasting.
    /// Cette méthode affiche une vue en 3D simulée basée sur les relevés du Lidar.
    /// \param plan Carte à afficher.
    /// \param WindowWidth Largeur de fenêtre.
    /// \param WindowHeight Hauteur de fenêtre.
    /// \param wallheight Hauteur des murs.
    /// \param fov Champ de vision (°).
    void displayRaycasting(Grid plan, int WindowWidth, int WindowHeight, int wallheight, int fov) const;
    /// \brief Afficher les trois fenêtres
    /// Cette méthode affiche les trois vues principales de la simulation : l'environnement complet, la carte locale du robot et La vue simulée en 3D via le raycasting.
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
