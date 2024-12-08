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


---

# Démarche de réflexion

## Problème à résoudre
L'objectif de ce projet est de simuler un robot autonome capable d'explorer son environnement et de reconstruire une carte en temps réel. Le robot, équipé d'un capteur de distance de type Lidar et d'un système de localisation idéal, doit détecter et cartographier les obstacles présents dans l’environnement.

## Démarche adoptée

### Étape 1 : Analyse des besoins
Pour atteindre ces objectifs, nous avons identifié les éléments nécessaires :  
1. Un modèle d'environnement contenant des obstacles de tailles et positions aléatoires.  
2. Un capteur Lidar simulé capable de détecter les obstacles tout autour du robot.  
3. Un mécanisme de mise à jour de la carte, permettant au robot de marquer les zones explorées et non explorées.  
4. Un algorithme de navigation robuste pour planifier les déplacements du robot.  
5. Un moyen de visualisation en temps réel.  

### Étape 2 : Modélisation du problème
L'environnement est représenté comme une grille d'occupation 2D, où chaque cellule correspond à une portion de l'espace. Les obstacles sont définis comme des zones bloquées dans cette grille. Le robot utilise un Lidar simulé pour mesurer une distance jusqu'à un éventuel obstacle. Les déplacements sont modélisés comme des transitions d'un point (x, y) à un autre sur la grille. La navigation utilise une version simplifiée de l’algorithme A* pour trouver le chemin optimal.

---

## Explication de la solution

### Lidar simulé
Le Lidar simule un capteur de distance à 360 degrés qui permet au robot de détecter les obstacles dans son environnement en projetant des rayons (raycasting). Chaque rayon mesure la distance jusqu'à l'obstacle le plus proche dans sa direction, en utilisant un algorithme basé sur la méthode DDA (Digital Differential Analyzer).

#### Fonctionnement du Lidar

1. **Position initiale et orientation** :  
   Le capteur récupère la position absolue du robot dans l'environnement et son orientation actuelle. Chaque rayon est défini par un ID, ce qui détermine son angle relatif par rapport à l'orientation du robot.

2. **Calcul de l'angle du rayon** :  
   L'angle d'un rayon est calculé en ajoutant l'angle d'orientation du robot à un décalage basé sur l'ID du rayon. Les rayons sont répartis uniformément sur un cercle complet.

3. **Définition de la direction** :  
   La direction du rayon est définie par deux composantes calculées à partir des fonctions cosinus et sinus de l'angle du rayon.

4. **Pas de progression** :  
   Le rayon progresse dans la grille de l'environnement en calculant les distances à la prochaine ligne verticale ou horizontale de la grille.

5. **Avancée du rayon avec DDA** :  
   Le rayon avance dans la grille case par case. Pour chaque nouvelle case traversée, le programme vérifie si elle contient un obstacle.

6. **Détection d'obstacle ou dépassement de portée** :  
   Si une case contenant un obstacle est détectée, le Lidar retourne la distance accumulée. Si aucun obstacle n'est trouvé dans la portée maximale, la fonction retourne une valeur indiquant l'absence d'obstacle.

### Cartographie

La mise à jour de la carte se fait à chaque balayage des rayons du LiDAR. Les cellules traversées par un rayon sont marquées comme libres, et la cellule où un obstacle est détecté est marquée comme un mur. Si le rayon dépasse les limites de la carte, celle-ci est étendue dynamiquement.

### Choix de la destination

Le robot choisit sa prochaine cible en cherchant la cellule inconnue la plus proche, adjacente à une cellule libre. La distance est calculée selon la distance de Manhattan, soit la somme des différences absolues des coordonnées x et y entre deux points. La cellule la plus proche devient la prochaine destination.

### Algorithme A*
L'algorithme A* trouve le chemin optimal entre un point de départ et un objectif en utilisant une combinaison de coût réel et d'une estimation du coût restant (heuristique). L'heuristique utilisée ici est la distance de Manhattan, qui est la somme des distances absolues en x et en y entre le point actuel et l'objectif.

1. Le coût réel est initialisé à zéro pour le point de départ et à l'infini pour tous les autres points.  
2. Le coût total est la somme du coût réel et de la distance estimée.  
3. Les voisins du point actuel sont explorés un par un, et leurs coûts sont mis à jour si une meilleure route est trouvée.  
4. Lorsque l'objectif est atteint, le chemin est reconstruit en remontant la chaîne des parents depuis l'objectif jusqu'au départ.

## Déplacement du robot

La fonction `Robot::executeInstruction` guide le robot vers une cible en ajustant d'abord son orientation, puis en avançant en ligne droite. Si l'orientation actuelle diffère de celle requise pour atteindre la cible, le robot tourne. Une fois aligné, il avance à une vitesse constante. La fonction vérifie si le robot a atteint sa cible en comparant ses coordonnées actuelles à celles de la cible.

## Orchestration des fonctions

La fonction `Simulation::run` orchestre tout le processus d'exploration.  

1. **Lecture des capteurs** : Le robot lit les données du LiDAR pour détecter les obstacles.  
2. **Mise à jour de la carte** : La carte interne est mise à jour avec les nouvelles données.  
3. **Calcul de la cible et du chemin** : La prochaine cible est choisie, et un chemin est calculé vers cette cible avec l'algorithme A*.  
4. **Déplacement** : Le robot exécute les étapes du chemin, mettant à jour sa carte au fur et à mesure.  
5. **Fin de la simulation** : Si aucune cible n'est accessible, l'exploration est terminée.

## Résultats

### Visualisations
Les résultats incluent deux types de visualisations pour mieux comprendre le comportement du robot :  
1. **Vue 2D de l’environnement et de la carte du robot** :  
<p align="center">
  <img src="images/environment_view.png" alt="Vue de l'environnement"/>
</p>
   Cette vue montre la position du robot, les obstacles et les zones explorées.  

2. **Vue 3D simulée (Raycasting)** :  
<p align="center">
  <img src="images/raycasting_view.png" alt="Vue 3D Raycasting"/>
</p>
   Cette vue simule la perception du robot en projetant les lectures du Lidar sur un plan 3D. 

### Performance
Le robot explore entièrement les zones accessibles dans des environnements complexes. Les performances dépendent de la densité des obstacles et de la portée du Lidar.

## Conclusion

Ce projet montre comment un robot autonome peut explorer un environnement inconnu en combinant planification de chemin, mise à jour de carte en temps réel et perception par capteur. Les résultats démontrent l'efficacité de cette approche dans des scénarios variés.