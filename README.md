# Simulation de Navigation Robotique avec Lidar et OpenCV

Ce projet implémente une simulation robotique utilisant un **robot mobile équipé d'un Lidar** pour explorer un environnement inconnu. Il utilise OpenCV pour visualiser l'environnement et la carte du robot en temps réel.

## Fonctionnalités
- **Environnement généré aléatoirement** avec des obstacles de tailles variées.
- **Algorithme A*** pour la recherche de chemin.
- **Exploration autonome** avec mise à jour de la carte à partir des données du Lidar.
- **Visualisation en temps réel** :
  - Vue 2D de l'environnement et de la carte du robot.
  - Vue 3D simplifiée utilisant le raycasting pour simuler la perception du robot.

## Dépendances
- [OpenCV](https://opencv.org/) : Pour les affichages graphiques.
- **CMake** : Pour la configuration et la construction du projet.
- **C++11** ou version ultérieure.

## Installation et Compilation
**Cloner le dépôt** :
   ```bash
   git clone https://github.com/Cyclemnt/simulidar.git
   cd simulidar
   mkdir build
   cd build
   cmake ..
   make
   ./main
  ```

## Utilisation
1. Une fois le programme lancé, la simulation démarre en plaçant le robot aléatoirement dans un environnement.
  - Appuyez sur n'importe quelle touche pour commencer.
2. La simulation met à jour en temps réel l'état de l'environnement et la carte du robot.
3. Une fois que toutes les zones accessibles ont été explorées, la simulation s'arrête.
  - Appuyez sur n'importe quelle touche pour fermer les fenêtres.

## Personalisation
Vous pouvez ajuster certains paramètres dans le fichier types.hpp :
- Dimensions de l'environnement (ENV_WIDTH, ENV_HEIGHT).
- Nombre d'obstacles (OBSTACLE_NUM).
- Taille maximale des obstacles (OBSTACLE_MAX_SIZE).
- Pas de temps de la simulation (TIMESTEP).
- Portée du Lidar (LIDAR_MAX_RANGE).
- Nombre de rayons du Lidar (LIDAR_RAY_COUNT).
- Vitesse angulaire du robot (ANG_V).
- Vitesse de déplacement du robot (SPEED).

## Contributions
- FERRIER Simon
- LAMOULLER Clément
- PARIZOT Luan
