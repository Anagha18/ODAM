/**
 * LIDARLite I2C Example
 * Author: Garmin
 * Modified by: Shawn Hymel (SparkFun Electronics)
 * Date: June 29, 2017
 * 
 * Read distance from LIDAR-Lite v3 over I2C
 * 
 * See the Operation Manual for wiring diagrams and more information:
 * http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf
 */
#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>

Servo servoup;
Servo servodown;
LIDARLite lidarLite;
int cal_cnt = 0;

void setup()
{
  Serial.begin(9600); // Initialize serial connection to display distance readings
  servoup.attach(2);
  servodown.attach(3);
  servoup.write(0);
  servodown.write(0);
  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations
}

void loop()
{
  int dist;
  servoup.write(180);
  calculation(cal_cnt);
  delay(500);
  servodown.write(180);
  calculation(cal_cnt);
  delay(500);
  servoup.write(0);
  calculation(cal_cnt);
  delay(500);
  servodown.write(0);
  calculation(cal_cnt);
  delay(500);  
}

void calculation(int cal_cnt)
{
    int dist=0;
    if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }

  // Increment reading counter
  cal_cnt++;
  cal_cnt = cal_cnt % 100;
  Serial.print(dist);
  Serial.println(" cm");
}
