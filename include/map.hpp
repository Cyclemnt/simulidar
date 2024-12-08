#ifndef MAP_HPP
#define MAP_HPP

#include "types.hpp"

using Types::Grid;
using Types::Direction;

/// \brief Représente la carte du robot.
class Map
{
private:
    Grid robotMap;      // Occupancy grid
    int leftExtension, bottomExtension;  // Quantité de cases ajoutées à gauche et en bas de la position initiale
public:
    // Constructeur qui initialise le carte du robot
    Map();

    /// \brief Agrandir la carte.
    /// \param amount Quantité d'agrandissement.
    /// \param dir Direction de l'agrandissement.
    void adjustMapBounds(int amount, Direction dir);
    /// \brief Tracer un chemin de cases libres terminé par un obstacle.
    /// \param startX Coordonnée x du départ.
    /// \param startY Coordonnée y du départ.
    /// \param rayAngle Angle du rayon.
    /// \param distance Distance mesurée.
    void castRayAndMarkObstacle(double startX, double startY, double rayAngle, double distance);
    /// \brief Déterminer la prochaine case à explorer.
    /// \param startX Coordonnée x du départ.
    /// \param startY Coordonnée y du départ.
    /// \return La position de la case à explorer.
    std::pair<int, int> findNearestInterestPoint(double startX, double startY) const;
    /// \brief Trouver le chemin le plus court entre "start" et "goal".
    /// \param start Position de départ.
    /// \param goal Position du but.
    /// \return Le chemin jusqu'au but.
    std::vector<std::pair<int, int>> aStar(std::pair<int, int> start, std::pair<int, int> goal) const;
    /// \brief Affiche la carte dans le terminal.
    void printMap() const;
    
    //Getter
    Grid getRobotMap() const;
    int getWidth() const; 
    int getHeight() const;
    int getLeftExtension() const; 
    int getBottomExtension() const; 

    ~Map();
};

#endif // MAP_HPP