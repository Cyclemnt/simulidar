#ifndef MAP_HPP
#define MAP_HPP

#include "types.hpp"

using Types::CellState;
using Types::Grid;
using Types::Direction;

class Map
{
private:
    Grid robotMap;      // Occupancy grid
    int leftExtension, bottomExtension;  // Quantité de cases ajoutées à gauche et en bas de la position initiale
    //double resolution;  // Résolution de la carte
public:
    // Constructeur qui initialise le carte du robot
    Map();

    // Méthode pour agrandir la carte
    void adjustMapBounds(int amount, Direction dir);
    // Méthode pour tracer un chemin de cases libres terminé par un obstacle
    void castRayAndMarkObstacle(double startX, double startY, double rayAngle, double distance);
    // Méthode pour déterminer la prochaine case à explorer 
    std::pair<int, int> findNearestInterestPoint(double startX, double startY) const;
    // Méthode pour trouver un chemin 
    std::vector<std::pair<int, int>> findPath(int startX, int startY, int goalX, int goalY) const;
    // Méthode pour afficher la carte dans le terminal
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