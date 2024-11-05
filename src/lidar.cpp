#include "../include/lidar.hpp"
#include "../include/simulation.hpp"  // Définition complète de Simulation

// Constructeur qui initialise le Lidar
Lidar::Lidar(Simulation* simulation_)
    : simulation(simulation_) {
}

// Méthode pour lire un rayon particulier
double Lidar::read(int rayID) const {
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