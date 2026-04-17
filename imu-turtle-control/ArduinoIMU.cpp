// Adresse I2C du module IMU (vérifiée avec scanner)
#define IMU_ADDRESS 0x69

// Registres de l'accéléromètre
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F

#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Vector3.h>
#include <Wire.h>

ros::NodeHandle nh;

// Déclaration du message ROS pour envoyer les accélérations
geometry_msgs::Vector3 accel_msg;
ros::Publisher accel_pub("imu_accel", &accel_msg);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(accel_pub);

  initIMU();
}

void loop() {
  float ax, ay, az;
  ax = getAcceleration(ACCEL_XOUT_H);
  ay = getAcceleration(ACCEL_YOUT_H);
  az = getAcceleration(ACCEL_ZOUT_H);
  
  accel_msg.x = ax;
  accel_msg.y = ay;
  accel_msg.z = az;
  
  // Publication des données sur le topic ROS
  accel_pub.publish(&accel_msg);

  // ROS Spin
  nh.spinOnce();

  // Petite pause pour éviter une surcharge du bus
  delay(100);
}

// Initialisation du capteur IMU
void initIMU() {
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(0x6B);  // Registre d'alimentation (Power Management 1)
  Wire.write(0x00);  // Réveil du capteur
  Wire.endTransmission();
}

// Lire une valeur d'accélération et la convertir en "g"
float getAcceleration(uint8_t reg) {
  int16_t rawData = readIMU(reg);
  return rawData / 16384.0;  // Conversion pour ±2g
}

// Fonction de lecture d'un registre 16 bits
int16_t readIMU(uint8_t reg) {
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(IMU_ADDRESS, 2);
  return (Wire.read() << 8) | Wire.read();  // MSB + LSB
}
