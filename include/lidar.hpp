#ifndef LIDAR_HPP
#define LIDAR_HPP

#include <vector>

// Forward declaration
class Simulation;

class Lidar
{
private:
    const int maxRange = 30;   // Portée d'un rayon
    const int rayCount = 360;  // Nombre de rayons
    Simulation* simulation;    // Pointeur vers Simulation
public:
    // Constructeur qui initialise le Lidar
    Lidar(Simulation* simulation_);
    // Méthode pour lire un rayon particulier
    double read(int rayID) const;
    // Méthode pour lire tous les rayon
    std::vector<double> readAll() const;

    // Getters
    int getRayCount() const;

    ~Lidar();
};

#endif // LIDAR_HPP