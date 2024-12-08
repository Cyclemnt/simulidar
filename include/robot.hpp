#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "map.hpp"
#include "lidar.hpp"

/// \brief Représente le robot.
class Robot
{
private:
    Map* map;           // Pointeur vers la carte du robot
    Lidar* lidar;       // Pointeur vers le lidar
    double x, y;        // Position relative du robot
    double orientation; // Orientation relative du robot
    std::pair<int, int> targetPos; // Position cible sur la carte du robot
    double timeStep;    // Temps entre chaque état de simulation
public:
    // Constructeur par défaut
    Robot();

    /// \brief Avancer le robot.
    /// \param distance Distance du déplacement.
    void move(double distance);
    /// \brief Tourner le robot.
    /// \param angle Angle de la rotation.
    void rotate(double angle);
    /// \brief Mettre à jour la carte.
    /// \param lidarMeasures Tableau des mesures Lidar.
    void updateMap(std::vector<double> lidarMeasures);
    /// \brief Exécuter l'instruction (s'orienter et avancer).
    /// \param targetPos_ Position de la case adjacente suivante.
    /// \return Instruction terminée.
    bool executeInstruction(std::pair<int, int> targetPos_);

    // Setters
    void setLidar(Lidar* lidar_);
    void setMap(Map* map_);
    void setTimeStep(int timeStemp_);

    // Getters
    double getX() const;
    double getY() const;
    double getOrientation() const;

    ~Robot();
};

#endif // ROBOT_HPP