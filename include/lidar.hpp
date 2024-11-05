#ifndef LIDAR_HPP
#define LIDAR_HPP

#include <vector>

// Forward declarations
class Robot;
class Environment;

class Lidar
{
private:
    const int range = 30;
    const int rayCount = 360;
    Robot* robot;              // Pointeur vers le robot
    Environment* environment;  // Pointeur vers l'environnement
public:
    // Constructeur qui initialise le Lidar
    Lidar();
    // Méthode pour initialiser le capteur
    void initialize(Robot* robot_, Environment* environment_);
    // Méthode pour lire un rayon particulier
    double read(int rayID) const;
    // Méthode pour lire tous les rayon
    std::vector<double> readAll() const;

    ~Lidar();
};

#endif // LIDAR_HPP