#include "../include/simulation.hpp"
#include "../include/types.hpp"
#include <opencv2/opencv.hpp>
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()
#include <cmath>

// Constructeur : Initialise l'environnement et le robot
Simulation::Simulation()
    : xRobotStart(0.0), yRobotStart(0.0), orientationRobotStart(0.0) {
    environment = new Environment(10, 10);
    map = new Map();
    robot = new Robot();
    lidar = new Lidar(this);  // Lidar reçoit un pointeur vers Simulation

    robot->setLidar(lidar);
    robot->setMap(map);
}

// Méthode pour initialiser la pose du robot dans l'environnement
void Simulation::initializeRobotPose() {
    int width = environment->getWidth();
    int height = environment->getHeight();
    double robotRadius = robot->getDiameter() / 2.0;

    srand(static_cast<unsigned>(time(0)));

    int x, y;
    bool isValidPosition = false;
    int maxAttempts = 1000;  // Limite de tentatives pour trouver une position
    int attempts = 0;

    while (attempts < maxAttempts && !isValidPosition) {
        attempts++;

        // Génère une position aléatoire
        x = rand() % width;
        y = rand() % height;

        // Vérifie que la position est libre pour le diamètre du robot
        isValidPosition = true;

        // Calculer le nombre de cellules à vérifier autour du centre `(x, y)`
        int cellRadiusX = static_cast<int>(ceil(robotRadius));
        int cellRadiusY = static_cast<int>(ceil(robotRadius));

        // Vérifier toutes les cellules dans le carré autour de la position centrale
        for (int dx = -cellRadiusX; dx <= cellRadiusX && isValidPosition; dx++) {
            for (int dy = -cellRadiusY; dy <= cellRadiusY && isValidPosition; dy++) {
                int checkX = x + dx;
                int checkY = y + dy;

                // Vérifier si les coordonnées sont dans la grille
                if (checkX >= 0 && checkX < width && checkY >= 0 && checkY < height) {
                    // Calculer la distance du centre de la cellule à `(x, y)`
                    double distToCell = sqrt(dx * dx + dy * dy);
                    // Si la distance est inférieure ou égale au rayon du robot, vérifier la cellule
                    if (distToCell <= robotRadius) {
                        if (environment->getRoom()[checkX][checkY] != CellState::Free) {
                            isValidPosition = false;
                        }
                    }
                } else {
                    // Si on est en dehors de la grille, la position est invalide
                    isValidPosition = false;
                }
            }
        }
    }

    // Vérifie si une position valide a été trouvée
    if (isValidPosition) {
        // Place le centre du robot dans la cellule libre trouvée
        xRobotStart = x;
        yRobotStart = y;
        // Orientation aléatoire en radians entre 0 et 2*PI
        //orientationRobotStart = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
    } else {
        // Affiche une erreur si aucune position valide n'est trouvée
        throw std::runtime_error("Erreur : Impossible de positionner le robot dans un espace libre.");
    }
}

// Méthode pour démarrer la simulation
void Simulation::run() {
    // Logique de simulation (boucle principale)
    environment->generateRandomObstacles(4, 2);
    environment->printRoom();
    initializeRobotPose();
    displaySimulation();
}

// Méthode pour afficher la simulation
void Simulation::displaySimulation() const {
    Grid room = environment->getRoom();
    int height = environment->getHeight();
    int width = environment->getWidth();
    // Création de l'image OpenCV (CV_8UC3 pour une image couleur)
    cv::Mat roomCopy(height, width, CV_8UC3);
    
    // Remplissage de CopieRoom en fonction des valeurs de room
    for (int y = 0 ; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cv::Vec3b& pixel = roomCopy.at<cv::Vec3b>(height - 1 - y, x);
            switch (room[x][y]) {
                case CellState::Wall:
                    pixel = cv::Vec3b(255, 0, 0);      // Bleu pour Wall
                    break;
                case CellState::Free:
                    pixel = cv::Vec3b(255, 255, 255);  // Blanc pour les cases libres
                    break;                    
                case CellState::Unknown:
                    pixel = cv::Vec3b(0, 0, 0);        // Noir pour les cases inconnues
                    break;
                default:
                    pixel = cv::Vec3b(247, 0, 248);    // Rose pour les cases non définies 
                    break;
            }
        }
    }
    // Afficher le robot
    cv::Vec3b& pixel = roomCopy.at<cv::Vec3b>(height - 1 - yRobotStart, xRobotStart);
    pixel = cv::Vec3b(0, 166, 255);

    // Afficher l'image
    cv::namedWindow("Affichage de la simulation", cv::WINDOW_GUI_NORMAL);
    cv::imshow("Affichage de la simulation", roomCopy);
    cv::waitKey(0);
}

// Getters
Environment* Simulation::getEnvironment() const {
    return environment;
}
Robot* Simulation::getRobot() const {
    return robot;
}
double Simulation::getXRobotStart() const {
    return xRobotStart;
}
double Simulation::getYRobotStart() const {
    return yRobotStart;
}
double Simulation::getOrientationRobotStart() const {
    return orientationRobotStart;
}

Simulation::~Simulation() {
    delete lidar;
    delete robot;
    delete map;
    delete environment;
}
