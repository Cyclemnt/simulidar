#include "../include/simulation.hpp"

// Constructeur : Initialise l'environnement et le robot
Simulation::Simulation()
    : xRobotStart(0.0), yRobotStart(0.0), orientationRobotStart(0.0) {
    Environment* environment = new Environment(8, 10);
    //environment->drawLineDDA(2, 4, 3, 5);
    //environment->drawLineDDA(5, 1, 5, 2);
    environment->generateRandomObstacles(4, 2);
    environment->printGrid();

    Robot* robot = new Robot();

    robot->getLidar()->initialize(robot, environment);  // Initialiser le Lidar après création du robot
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
    robot->move(5.0);  // Exemple de déplacement
}

// Getters
double Simulation::getXRobotStart() const {
    return xRobotStart;
}
double Simulation::getYRobotStart() const {
    return yRobotStart;
}
double Simulation::getOrientationRobotStart() const {
    return orientationRobotStart;
}