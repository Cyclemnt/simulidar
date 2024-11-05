#include "../include/lidar.hpp"

// Constructeur qui initialise le Lidar
Lidar::Lidar() {
    //sim = Simulation::getSim();
    //std::cout << sim->getXRobotStart() << std::endl;
}

// Méthode pour lire un rayon particulier
double Lidar::read(int rayID) const {
    // Comment avoir connaissance de la position du robot et d'environment ?
    // Idée : avoir un pointeur de l'objet simulation ("sim") en attribut de Lidar pour avoir accès aux pointeurs robot et environment
    // Problème : comment donner un pointeur de sim à Lidar ? Sachant que Simulation instancie Robot qui instancie Lidar.
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