# Simulation de Navigation Robotique avec LiDAR

Ce projet implémente une simulation robotique utilisant un **robot mobile équipé d'un LiDAR** pour explorer un environnement inconnu. Il utilise OpenCV pour visualiser l'environnement et la carte du robot en temps réel.

## Membres du groupe
- FERRIER Simon
- LAMOULLER Clément
- PARIZOT Luan

## Objectif du projet
Le but est de simuler un robot mobile explorant un environnement inconnu en utilisant un LiDAR pour construire une carte. Le robot doit éviter les obstacles, explorer toutes les zones accessibles et naviguer efficacement.

## Diagramme UML du projet
<p align="center">
  <img src="images/simulidar_uml.svg" alt="Diagramme UML"/>
</p>

## Fonctionnalités
- **Environnement généré aléatoirement** avec des obstacles de tailles variées.
- **Robot initialisé aléatoirement** sans conaissance de sa position.
- **Algorithme de [raycasting](https://lodev.org/cgtutor/raycasting.html)** pour les mesures LiDAR.
- **Exploration autonome** avec mise à jour de la carte à partir des données du LiDAR.
    - Algorithme [A*](https://en.wikipedia.org/wiki/A*_search_algorithm) pour la recherche de chemin.
- **Visualisation en temps réel** :
  - Vue 2D de l'environnement et de la carte du robot.
  - Vue 3D simplifiée utilisant le raycasting pour simuler la perception du robot.

## Dépendances
- **[OpenCV](https://opencv.org/)** : Pour les affichages graphiques.
- **CMake** : Pour la configuration et la construction du projet.
- **C++11** ou version ultérieure.

## Installation et Compilation
**Cloner le dépôt** :
   ```bash
   git clone https://github.com/Cyclemnt/simulidar.git
  ```
**Compiler** :
   ```bash
   cd simulidar
   mkdir build
   cd build
   cmake ..
   make
   ./main
  ```

## Utilisation
1. Une fois le programme lancé, la simulation démarre en plaçant le robot aléatoirement dans un environnement.  
   Appuyez sur n'importe quelle touche pour commencer.
2. La simulation met à jour en temps réel l'état de l'environnement et la carte du robot.
3. Une fois que toutes les zones accessibles ont été explorées, la simulation s'arrête.  
   Appuyez sur n'importe quelle touche pour fermer les fenêtres.

## Personalisation
Modifiez les paramètres dans types.hpp pour personnaliser la simulation :

- **ENV_WIDTH**, **ENV_HEIGHT** : Dimensions de l’environnement.
- **OBSTACLE_NUM**, **OBSTACLE_MAX_SIZE** : Nombre et taille des obstacles.
- **TIMESTEP** : Pas de temps entre les mises à jour.
- **LIDAR_MAX_RANGE**, **LIDAR_RAY_COUNT** : Portée et précision du Lidar.
- **SPEED**, **ANG_V** : Vitesse du robot.

## Exemple visuel
<p align="center">
  <img src="images/demo_simulidar.gif" alt="Demo"/>
</p>
