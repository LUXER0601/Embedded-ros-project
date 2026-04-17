#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String

def publisher_node():
    # Initialiser le noeud ROS avec le nom "talker"
    rospy.init_node('talker', anonymous=True)
    
    # Créer un publisher qui publie sur le topic "chatter"
    # avec le type de message String et une queue size de 10
    pub = rospy.Publisher('chatter', String, queue_size=10)
    
    # Définir la fréquence de publication à 10 Hz
    rate = rospy.Rate(10)
    
    # Compteur pour les messages
    count = 0
    
    # Tant que le noeud ROS est actif
    while not rospy.is_shutdown():
        # Créer un message avec un texte et un numéro
        hello_str = "hello world %s" % rospy.get_time()
        
        # Afficher le message dans la console
        rospy.loginfo(hello_str)
        
        # Publier le message sur le topic "chatter"
        pub.publish(hello_str)
        
        # Attendre selon la fréquence définie (0.1 secondes pour 10 Hz)
        rate.sleep()
        
        count += 1

if __name__ == '__main__':
    try:
        publisher_node()
    except rospy.ROSInterruptException:
        pass
