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
    /// \brief Constructeur qui initialise la carte du robot à une cellule libre.
    Map();

    /// \brief Agrandir la carte.
    /// Cette méthode permet d'agrandir la carte avec cellules à l'état inconnu (CellState::Unknown), dans une direction spécifique.
    /// \param amount Quantité d'agrandissement.
    /// \param dir Direction de l'agrandissement.
    void adjustMapBounds(int amount, Direction dir);
    /// \brief Tracer un chemin de cases libres terminé par un obstacle.
    /// Cette méthode simule un rayon émis depuis une position donnée pour mettre à jour l'état des cellules.
    /// \param startX Coordonnée x du départ.
    /// \param startY Coordonnée y du départ.
    /// \param rayAngle Angle du rayon.
    /// \param distance Distance mesurée.
    void castRayAndMarkObstacle(double startX, double startY, double rayAngle, double distance);
    /// \brief Déterminer la prochaine case à explorer.
    /// Cette méthode retourne les coordonnées de la cellule CellState::Unknown la plus proche d'une cellule CellState::Free.
    /// \param startX Coordonnée x du départ.
    /// \param startY Coordonnée y du départ.
    /// \return La position de la case à explorer.
    std::pair<int, int> findNearestInterestPoint(double startX, double startY) const;
    /// \brief Trouver le chemin le plus court entre "start" et "goal".
    /// Cette méthode implémente l'algorithme A* pour calculer le chemin le plus court entre deux points.
    /// \param start Position de départ.
    /// \param goal Position du but.
    /// \return Le chemin jusqu'au but.
    std::vector<std::pair<int, int>> aStar(std::pair<int, int> start, std::pair<int, int> goal) const;
    /// \brief Affiche la carte dans le terminal.
    /// Cette méthode affiche une représentation visuelle de la carte actuelle dans le terminal.
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