#include <iostream>
#include "../include/simulation.hpp"
#include "../include/map.hpp"

int main() {

    Environment* environment = new Environment(8, 10);
    //environment->drawLineDDA(2, 4, 3, 5);
    //environment->drawLineDDA(5, 1, 5, 2);
    environment->generateRandomObstacles(4, 2);
    environment->printGrid();

    Robot* robot = new Robot();

    Simulation sim(robot, environment);

    Map* map = new Map();
    map->printMap();
    delete map;


    /*
    // Création du robot et de l'environnement
    Robot* robot = new Robot(0, 0, M_PI/4, 1);  // Position relative initiale
    Environment* environment = new Environment(100, 100);  // Longueur et largeur de 100 unités

    // Création de la simulation
    Simulation simulation(robot, environment);

    std::cout << "Odométrie à t0 : {"<< robot->getX() << ", " << robot->getY() << "}" << std::endl;
    
    // Initialisation de la position du robot et lancement de la simulation
    simulation.initializeRobotPose();
    simulation.run();

    std::cout << "Position absolue initiale : {" << simulation.getXRobotStart() << ", " << simulation.getYRobotStart() << "}" << std::endl;
    std::cout << "Position absolue à t1 : {" << simulation.getXRobot() << ", " << simulation.getYRobot() << "}" << std::endl;

    std::cout << "Odométrie à t1 : {"<< robot->getX() << ", " << robot->getY() << "}" << std::endl;
    */
    // Libération de la mémoire
    delete robot;
    delete environment;

    return 0;
}