#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <turtlesim/SetPen.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Empty.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

// Définir pi comme une constante flottante
const float pi = 3.14159265;

// Définir la position actuelle de la tortue et la position cible comme variables globales
turtlesim::Pose currentpose;
turtlesim::Pose goalpose;

const float distance_tolerance = 0.1;
const float kp_linear = 1.5;
const float kp_angular = 4.0;

// Fonction pour construire et publier des messages Twist
void setturtlevelocities(ros::Publisher twist_pub, float linear, float angular)
{
  std::cout << "Définir la vitesse de la tortue à x = " << linear
            << " rotz = " << angular << '\n';

  geometry_msgs::Twist twist;
  twist.linear.x = linear;
  twist.angular.z = angular;

  twist_pub.publish(twist);
}

// Callback pour mettre à jour la position actuelle de la tortue
void getturtleposecallback(const turtlesim::Pose& pose)
{
  std::cout << "Position actuelle de la tortue :\n" << pose << '\n';
  currentpose = pose;
}

// Callback pour mettre à jour la position cible de la tortue
void getturtlegoalcallback(const turtlesim::Pose& goal)
{
  std::cout << "Objectif de la tortue :\n" << goal << '\n';
  goalpose = goal;
}

// Contrôleur de la tortue
void turtlecontroler(ros::Publisher twist_pub)
{
  float turtle_x = currentpose.x;
  float turtle_y = currentpose.y;
  float turtle_theta = currentpose.theta;
  float goal_x = goalpose.x;
  float goal_y = goalpose.y;

  float distance = sqrt(pow(goal_x - turtle_x, 2) + pow(goal_y - turtle_y, 2));
  float desired_angle = atan2(goal_y - turtle_y, goal_x - turtle_x);
  float angle_error = desired_angle - turtle_theta;

  while (angle_error > pi) angle_error -= 2 * pi;
  while (angle_error < -pi) angle_error += 2 * pi;

  float forward_velocity = 0.0;
  float angular_velocity = 0.0;

  float max_linear_speed = 2.0;
  float max_angular_speed = 2.5;

  if (distance > distance_tolerance) {
    forward_velocity = std::min(kp_linear * distance, max_linear_speed);
    angular_velocity = std::min(std::max(kp_angular * angle_error, -max_angular_speed), max_angular_speed);

    if (fabs(angle_error) < 0.05) { // Éviter les oscillations
      angular_velocity = 0.0;
    }
  } else {
    forward_velocity = 0.0;
    angular_velocity = 0.0;
  }

  setturtlevelocities(twist_pub, forward_velocity, angular_velocity);
}

int main(int argc, char** argv)
{
  // Définir une position initiale en dehors de la zone visible
  goalpose.x = -5;
  goalpose.y = -5;

  // Initialiser ROS
  ros::init(argc, argv, "auto_draw");
  ros::NodeHandle nh;

  // Définir la fréquence de mise à jour : 10 Hz
  ros::Rate r(10);

  // Souscription au topic de la position de la tortue
  ros::Subscriber pose_sub = nh.subscribe("turtle1/pose", 1, getturtleposecallback);

  // Souscription au topic de l'objectif de la tortue
  ros::Subscriber goal_sub = nh.subscribe("turtledriver/goal", 1, getturtlegoalcallback);

  // Création d'un Publisher sur le topic de commande de vitesse
  ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

  // Client pour réinitialiser la simulation
  ros::ServiceClient resetclient = nh.serviceClient<std_srvs::Empty>("reset");
  std_srvs::Empty resetservice;
  resetclient.waitForExistence();
  resetclient.call(resetservice);

  // Client pour modifier la couleur du stylo
  ros::ServiceClient penclient = nh.serviceClient<turtlesim::SetPen>("turtle1/set_pen");
  penclient.waitForExistence();

  // Initialiser la couleur du stylo
  turtlesim::SetPen pen;
  pen.request.r = 255;
  pen.request.g = 255;
  pen.request.b = 255;
  pen.request.width = 5;
  pen.request.off = 0;

  while (ros::ok())
  {
    // Modifier la couleur du stylo aléatoirement
    pen.request.r = rand() % 256;
    pen.request.g = rand() % 256;
    pen.request.b = rand() % 256;
    penclient.call(pen);

    // Appeler le contrôleur de la tortue
    turtlecontroler(twist_pub);

    // Envoyer et recevoir des messages ROS
    ros::spinOnce();

    // Attendre selon la fréquence définie
    r.sleep();
  }

  return 0;
}
