#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <turtlesim/SetPen.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_srvs/Empty.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

// Constantes
const float pi = 3.14159265;
const float SCALE_LINEARX = 1.0;   // Facteur d'échelle pour la vitesse linéaire en X
const float SCALE_LINEARY = 1.0;   // Facteur d'échelle pour la vitesse linéaire en Y
const float SCALE_ANGULAR = 2.0;   // Facteur d'échelle pour la vitesse angulaire

// Variables globales
geometry_msgs::Vector3 imu_accel;  // Stocke l'accélération reçue du capteur IMU
ros::Publisher twist_pub;          // Déclare un éditeur ROS pour publier des commandes de mouvement

// Callback pour recevoir les données de l'IMU envoyées par Arduino
void imuCallback(const geometry_msgs::Vector3::ConstPtr& msg) {
  imu_accel = *msg;  // Mise à jour de la variable globale avec les nouvelles données de l'IMU

  // Conversion de l'accélération en vitesse pour la tortue
  geometry_msgs::Twist twist_msg;
  twist_msg.linear.x = imu_accel.x * SCALE_LINEARX;   // Déplacement linéaire basé sur l'accélération en X
  twist_msg.linear.y = imu_accel.y * SCALE_LINEARY;   // Déplacement linéaire basé sur l'accélération en Y
  twist_msg.angular.z = imu_accel.z * SCALE_ANGULAR;  // Rotation basée sur l'accélération en Z

  // Publication de la commande de mouvement
  twist_pub.publish(twist_msg);
}

int main(int argc, char** argv) {
  // Initialisation du nœud ROS
  ros::init(argc, argv, "imu_turtle_control");
  ros::NodeHandle nh;

  // Abonnement au topic "imu_accel" pour recevoir les données de l'IMU
  ros::Subscriber imu_sub = nh.subscribe("imu_accel", 10, imuCallback);

  // Création du publisher pour envoyer des commandes de mouvement à la tortue
  twist_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);

  // Client pour réinitialiser la simulation
  ros::ServiceClient reset_client = nh.serviceClient<std_srvs::Empty>("reset");
  std_srvs::Empty reset_srv;
  reset_client.waitForExistence();  // Attente de la disponibilité du service
  reset_client.call(reset_srv);     // Appel du service de réinitialisation

  // Client pour modifier la couleur du crayon de la tortue
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("turtle1/set_pen");
  pen_client.waitForExistence();  // Attente de la disponibilité du service

  // Configuration du crayon (couleur et épaisseur)
  turtlesim::SetPen pen;
  pen.request.r = 255;      // Rouge
  pen.request.g = 255;      // Vert
  pen.request.b = 255;      // Bleu (Blanc en combinant les trois)
  pen.request.width = 5;    // Épaisseur du crayon
  pen.request.off = 0;      // Activer le crayon

  pen_client.call(pen);     // Envoi de la configuration au service

  // Maintien du nœud en exécution pour traiter les messages entrants
  ros::spin();

  return 0;
}
