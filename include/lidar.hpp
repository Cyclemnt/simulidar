#ifndef LIDAR_HPP
#define LIDAR_HPP

#include "simulation.hpp"
#include <iostream>
#include <vector>

class Lidar
{
private:
    //Simulation* sim;
    const int range = 30;
    const int rayCount = 360;
public:
    // Constructeur qui initialise le Lidar
    Lidar();

    // Méthode pour lire un rayon particulier
    double read(int rayID) const;
    // Méthode pour lire tous les rayon
    std::vector<double> readAll() const;

    ~Lidar();
};

#endif // LIDAR_HPP