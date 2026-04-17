# Robotics Solutions - Laboratory Work

Consolidated repository containing all source code solutions for the laboratory work (TP2 and TP3) in Software Architecture for Robotics.
TP2 --> ros-pub-sub-communication.
TP3 --> imu-turtle-control.

## Project Structure

```
solutions/
├── ros-pub-sub-communication/   # TP2 - ROS Publisher/Subscriber Communication
│   ├── PublisherNode.py         # ROS Publisher Node in Python
│   ├── SubscriberNode.cpp       # ROS Subscriber Node in C++
│   ├── Controltortuga.cpp       # Turtle Controller for Turtlesim
│   └── CMakeLists.txt           # CMake configuration for compilation
│
├── imu-turtle-control/          # TP3 - Turtle Control with IMU 9 DOF
│   ├── ControlTurtle.cpp        # Turtle Controller Node using IMU data
│   ├── ArduinoIMU.cpp           # Arduino Code for IMU sensor reading
│   ├── I2C_Scanner.cpp          # I2C Scanner for device detection
│   └── CMakeLists.txt           # CMake configuration for compilation
│
└── README.md                    # This file

```

## ros-pub-sub-communication - ROS Publisher/Subscriber Communication

### Objectives:
- Create a catkin workspace and package
- Implement a Publisher/Subscriber architecture using ROS
- Inter-node communication between Python and C++
- Control Turtlesim simulation

### Files:
- **PublisherNode.py**: Publishes messages to the `/chatter` topic
- **SubscriberNode.cpp**: Subscribes to the `/chatter` topic and receives messages
- **Controltortuga.cpp**: Controls the Turtlesim turtle towards specific objectives
- **CMakeLists.txt**: Compilation configuration for C++ executables

### Execution:
```bash
# Start ROS core
roscore

# Run Publisher (in another terminal)
rosrun ros_pub_sub publisher_node

# Run Subscriber (in another terminal)
rosrun ros_pub_sub SubscriberNode

# Run Turtlesim
rosrun turtlesim turtlesim_node

# Run turtle controller
rosrun ros_pub_sub TurtleController
```

## imu-turtle-control - Turtle Control with IMU 9 DOF

### Objectives:
- Connect a 9 DOF IMU sensor to Arduino Mega 2560
- I2C communication between Arduino and IMU
- ROS integration using ROSserial
- Control Turtlesim with accelerometer data

### Files:
- **ArduinoIMU.cpp**: Reads ICM-20600 accelerometer data and publishes to ROS
- **I2C_Scanner.cpp**: Scans the I2C bus to detect IMU devices
- **ControlTurtle.cpp**: ROS node that receives IMU data and controls the turtle
- **CMakeLists.txt**: Compilation configuration for Ubuntu/ROS

### Execution:
```bash
# 1. Upload Arduino code (using Arduino IDE)
# Upload ArduinoIMU.cpp to Arduino Mega 2560

# 2. On Raspberry Pi with ROS
roscore

# 3. Connect Arduino with ROSserial (in another terminal)
rosrun rosserial_python serial_node.py /dev/ttyACM0

# 4. Verify IMU data is being published
rostopic echo /imu_accel

# 5. Launch Turtlesim simulation
rosrun turtlesim turtlesim_node

# 6. Run the turtle control node
rosrun imu_turtle_control TurtleControlNode
```

## Requirements

- ROS (Noetic or similar)
- Catkin
- Arduino IDE (for TP3)
- Dependencies:
  - roscpp
  - rospy
  - std_msgs
  - geometry_msgs
  - turtlesim
  - rosserial (for TP3)

## Notes

- TP2 files contain basic Publisher/Subscriber examples for ROS communication
- Source code is annotated in French (following the original PDF solutions)
- TP3 requires specific hardware (Arduino Mega 2560 + 9 DOF IMU Grove 101020585)
- CMakeLists.txt files specify how to compile the C++ executables

## Authors

Team - Software Architecture for Robotics
- Aliana Fouda Jules
- Amer Zaoula
- Maximiliano Florez
- Myrella Alves
- Oussama Makni

Supervisor: Rafael Accacio Nogueira

---
Generated from the PDF solution documents for TP2 and TP3.
