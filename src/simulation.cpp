#include "../include/simulation.hpp"

// Constructeur : Initialise l'environnement et le robot
Simulation::Simulation(Robot* robot_, Environment* environment_)
    : robot(robot_), environment(environment_), xRobotStart(0.0), yRobotStart(0.0), orientationRobotStart(0.0) {
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