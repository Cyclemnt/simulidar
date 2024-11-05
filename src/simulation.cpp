#include "../include/simulation.hpp"
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()

// Constructeur : Initialise l'environnement et le robot
Simulation::Simulation()
    : xRobotStart(0.0), yRobotStart(0.0), orientationRobotStart(0.0) {
    environment = new Environment(8, 10);
    environment->generateRandomObstacles(4, 2);

    map = new Map();
    robot = new Robot();
    lidar = new Lidar(this);  // Lidar reçoit un pointeur vers Simulation

    robot->setLidar(lidar);
    robot->setMap(map);
}

// Méthode pour initialiser la pose du robot dans l'environnement
void Simulation::initializeRobotPose() {
    srand(time(0));
    // Tant qu'une position valide n'est pas trouvée
    do {
        xRobotStart = rand() % environment->getWidth(); // Position aléatoire en x
        yRobotStart = rand() % environment->getHeight(); // Position aléatoire en y
    } while (!environment->isCellFree(xRobotStart, yRobotStart, robot->getDiameter()));
    // Orientation aléatoire entre + et - pi
    //orientationRobotStart = rand() % 2 * M_PI - M_PI;
}

// Méthode pour démarrer la simulation
void Simulation::run() {
    // Logique de simulation (boucle principale par exemple)
    initializeRobotPose();
    environment->printGrid();
}

// Getters
Environment* Simulation::getEnvironment() const {
    return environment;
}
Robot* Simulation::getRobot() const {
    return robot;
}
double Simulation::getXRobotStart() const {
    return xRobotStart;
}
double Simulation::getYRobotStart() const {
    return yRobotStart;
}
double Simulation::getOrientationRobotStart() const {
    return orientationRobotStart;
}

Simulation::~Simulation() {
    delete lidar;
    delete robot;
    delete map;
    delete environment;
}