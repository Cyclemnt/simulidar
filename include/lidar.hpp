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
    /// Ce constructeur initialise un capteur Lidar, qui permet de mesurer des distances en simulant des rayons dans l'environnement.
    /// \param simulation_ Pointeur vers la simulation.
    Lidar(Simulation* simulation_);

    /// \brief Lire un rayon particulier.
    /// Cette méthode calcule la distance entre le Lidar (situé sur le robot) et le premier obstacle rencontré dans la direction d'un rayon spécifique.
    /// \param rayID ID du rayon.
    /// \return La distance mesurée.
    double read(int rayID) const;
    /// \brief Lire tous les rayons.
    /// Cette méthode mesure les distances pour tous les rayons simulés par le Lidar, en parcourant un éventail d'angles autour de sa position.
    /// \return Un tableau des distances mesurées.
    std::vector<double> readAll() const;

    // Getters
    int getRayCount() const;

    ~Lidar();
};

#endif // LIDAR_HPP