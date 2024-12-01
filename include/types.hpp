#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

// PARAMèTRES DE LA SIMULATION
// Environnement
#define ENV_WIDTH 20        // Largeur de l'environnement (u)
#define ENV_HEIGHT 20       // Hauteur de l'environnement (u)
#define OBSTACLE_NUM 30     // Nombre d'obstacles
#define OBSTACLE_MAX_SIZE 3 // Taille maximale des obstacles (u)
// Simulation
#define TIMESTEP 30         // Temps entre chaque état de la simulation (ms)
// Lidar
#define LIDAR_MAX_RANGE 30  // Portée du Lidar (u)
#define LIDAR_RAY_COUNT 360 // Nombre de rayons du Lidar
// Robot
#define ANG_V M_PI          // Vitesse angulaire du robot (rad/s)
#define SPEED 2             // vitesse de mouvement du robot (u/s)
// (u) unité de distance

namespace Types {
    enum class CellState {
        Wall = 1,
        Free = 0,
        Unknown = -1
    };

    using Grid = std::vector<std::vector<CellState>>;

    enum class Direction { N, S, E, W };
}

#endif // TYPES_HPP
