#include "../include/simulation.hpp"
#include <opencv2/opencv.hpp>
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()
#include <stdexcept>

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
    environment->generateRandomObstacles(8, 2);
    environment->printRoom();
    initializeRobotPose();
    //xRobotStart = 4;
    //yRobotStart = 1;
    //map->printMap();
    std::cout << xRobotStart << ", " << yRobotStart << std::endl;
    std::vector<double> test = lidar->readAll();
    robot->updateMap(test);
    std::cout << std::endl;
    map->printMap();
    std::cout << map->findNearestInterestPoint(0, 0).first << ", " << map->findNearestInterestPoint(0, 0).second << std::endl;
    displaySimulation(50, environment->getRoom());
    displaySimulation(50, map->getRobotMap());
    displayRaycasting(map->getRobotMap(),800,600,200,70);

}

// Méthode pour afficher la simulation
void Simulation::displaySimulation(int scaleFactor, Grid plan) const {
    int height = 0;
    int width = 0;
    double positionRobotX = 0;
    double positionRobotY = 0;
    std::string WindowName = "";
    if (plan == environment->getRoom()) {
        height = environment->getHeight();
        width = environment->getWidth();
        WindowName = "EnvironmentDisplay";
        positionRobotX = xRobotStart + robot->getX() + 0.5;
        positionRobotY = height - yRobotStart + robot->getY() - 0.5;

    }
    else if (plan == map->getRobotMap()) {
        height = map->getHeight();
        width = map->getWidth();
        WindowName = "RobotMapDisplay";
        positionRobotX = map->getLeftExtension() + robot->getX() + 0.5;
        positionRobotY = height - map->getBottomExtension() + robot->getY() - 0.5;
    }
    else {
        throw std::runtime_error("error");
    }
    // Création de l'image OpenCV (CV_8UC3 pour une image couleur)
    cv::Mat roomImage(height * scaleFactor, width * scaleFactor, CV_8UC3);
     // Dessin de la salle agrandie
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            cv::Rect cell(x * scaleFactor, (height - 1 - y) * scaleFactor, scaleFactor, scaleFactor);
            switch (plan[x][y]) {
                case CellState::Wall:
                    cv::rectangle(roomImage, cell, cv::Scalar(255, 0, 0), cv::FILLED); // Murs en bleu
                    break;
                case CellState::Free:
                    cv::rectangle(roomImage, cell, cv::Scalar(255,255,255), cv::FILLED); // Sol en blanc
                    break;                    
                case CellState::Unknown:
                    cv::rectangle(roomImage, cell, cv::Scalar(0,0,0), cv::FILLED); // Case inconnues en noir
                    break;
                default:
                    cv::rectangle(roomImage, cell, cv::Scalar(247,0,248), cv::FILLED); // Cases non définies en rose
                    break;
            }
        }
    }
    // Afficher le robot
    cv::Point robotImage(positionRobotX * scaleFactor, positionRobotY * scaleFactor);
    cv::circle(roomImage, robotImage, robot->getDiameter() * scaleFactor / 2, cv::Scalar(0, 166, 255), cv::FILLED); // Point orange pour le robot
    
    // Afficher l'image
    cv::namedWindow(WindowName, cv::WINDOW_GUI_NORMAL);
    cv::imshow(WindowName, roomImage);
    cv::waitKey(0);
}

//Affichage en 3D avec le raycasting
void Simulation::displayRaycasting(Grid plan, int WindowWidth, int WindowHeight, int wallheight,int fov) const {
cv::Mat raycasting = cv::Mat::zeros(WindowHeight,WindowWidth,CV_8UC3);
std::vector<double> readings = lidar->readAll();
for (int i=-fov/2;i<=fov/2;i++){
double correcteddistance=readings[i+180]*cos(i*M_PI/180);
double projectionwallheight= wallheight/correcteddistance;
double band_startY =(WindowHeight- projectionwallheight) / 2.0;
double band_x = (i+(fov/2))*(WindowWidth )/fov;
cv::rectangle(raycasting, cv::Point(WindowWidth-band_x,band_startY),cv::Point(WindowWidth-(band_x +(WindowWidth/fov)),band_startY+projectionwallheight),cv::Scalar(255*(1-correcteddistance/30),0,0),cv::FILLED);
}
cv::imshow("Lidar Raycasting",raycasting);
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
