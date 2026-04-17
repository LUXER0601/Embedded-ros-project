#include <ros/ros.h>
#include <std_msgs/String.h>

// Callback function appelée chaque fois qu'un message est reçu
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  // Afficher le message reçu dans la console
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  // Initialiser le noeud ROS avec le nom "listener"
  ros::init(argc, argv, "listener");
  
  // Créer un NodeHandle ROS
  ros::NodeHandle n;

  // Créer un subscriber qui écoute le topic "chatter"
  // Chaque fois qu'un message est reçu, la fonction chatterCallback est appelée
  // queue_size = 10 définit la taille du buffer des messages
  ros::Subscriber sub = n.subscribe("chatter", 10, chatterCallback);

  // Garder le programme actif et traiter les messages ROS
  ros::spin();

  return 0;
}
