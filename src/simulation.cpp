#include "../include/simulation.hpp"
#include "../include/types.hpp"
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()

// Constructeur : Initialise l'environnement et le robot
Simulation::Simulation()
    : xRobotStart(0.0), yRobotStart(0.0), orientationRobotStart(0.0) {
    environment = new Environment(8, 10);
    environment->generateRandomObstacles(4, 2);

    map = new Map();
    robot = new Robot();
    lidar = new Lidar(this);  // Lidar reçoit un pointeur vers Simulation

    robot->setLidar(lidar);
    robot->setMap(map);
}

// Méthode pour initialiser la pose du robot dans l'environnement
void Simulation::initializeRobotPose() {
    srand(time(0));
    // Tant qu'une position valide n'est pas trouvée
    do {
        xRobotStart = rand() % environment->getWidth(); // Position aléatoire en x
        yRobotStart = rand() % environment->getHeight(); // Position aléatoire en y
    } while (!environment->isCellFree(xRobotStart, yRobotStart, robot->getDiameter()));
    // Orientation aléatoire entre + et - pi
    //orientationRobotStart = rand() % 2 * M_PI - M_PI;
}

// Méthode pour démarrer la simulation
void Simulation::run() {
    // Logique de simulation (boucle principale)
    initializeRobotPose();
    displaySimulation();
    double test = lidar->read(180);
    std::cout << test << std::endl;
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
    // Agrandissement pour visualisation
    cv::resize(roomCopy, roomCopy, cv::Size(width * 50, height * 50), 0, 0, cv::INTER_NEAREST);
    // Affichage du robot 
    circle(roomCopy, cv::Point(xRobotStart, yRobotStart), 50 * (robot->getDiameter()) / 2, (0, 166, 255) , -1, 256, 0);

    // Afficher l'image
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
