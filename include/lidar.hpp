#ifndef LIDAR_HPP
#define LIDAR_HPP

#include <vector>
#include "types.hpp"

// Forward declaration
class Simulation;

/// \brief Représente le Lidar simulé.
class Lidar
{
private:
    const int maxRange = LIDAR_MAX_RANGE;   // Portée d'un rayon
    const int rayCount = LIDAR_RAY_COUNT;  // Nombre de rayons
    Simulation* simulation;    // Pointeur vers Simulation
public:
    /// \brief Constructeur avec paramètres.
    /// \param simulation_ Pointeur vers la simulation.
    Lidar(Simulation* simulation_);

    /// \brief Lire un rayon particulier.
    /// \param rayID ID du rayon.
    /// \return La distance mesurée.
    double read(int rayID) const;
    /// \brief Lire tous les rayons.
    /// \return Un tableau des distances mesurées.
    std::vector<double> readAll() const;

    // Getters
    int getRayCount() const;

    ~Lidar();
};

#endif // LIDAR_HPP