#include "../include/lidar.hpp"
#include "../include/robot.hpp"         // Full definition of Robot
#include "../include/environment.hpp"   // Full definition of Environment

// Constructeur qui initialise le Lidar
Lidar::Lidar()
    : robot(nullptr), environment(nullptr) {
}

// Méthode pour initialiser le capteur
void Lidar::initialize(Robot* robot_, Environment* environment_) {
    robot = robot_;
    environment = environment_;
}

// Méthode pour lire un rayon particulier
double Lidar::read(int rayID) const {
    if (!robot || !environment) {
        std::cerr << "Lidar non initialisé avec le robot et l'environnement" << std::endl;
        return -1;
    }
    // Access robot and environment here as needed.
    return 0.0; // Replace with actual computation.
}

// Méthode pour lire tous les rayon
std::vector<double> Lidar::readAll() const {
    std::vector<double> readings;
    for (int id = 0; id < rayCount; id++)
    {
        readings.push_back(read(id));
    }
    return readings;
}

Lidar::~Lidar() {}