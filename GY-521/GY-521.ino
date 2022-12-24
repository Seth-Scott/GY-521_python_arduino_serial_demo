// This code is based on the work of dtansek, which can be found here:

// AUTHOR:
// https://create.arduino.cc/projecthub/dtansek

// LINK TO ORIGINAL CODE: 
// https://create.arduino.cc/projecthub/Nicholas_N/how-to-use-the-accelerometer-gyroscope-gy-521-6dfc19

#include <Wire.h>
#include <math.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ;
double pitch, roll;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  }

//convert the accel data to pitch/roll
void getAngle(int Vx,int Vy,int Vz) {
  double x = Vx;
  double y = Vy;
  double z = Vz;

  pitch = atan(x/sqrt((y*y) + (z*z)));
  roll = atan(y/sqrt((x*x) + (z*z)));
  //convert radians into degrees
  pitch = pitch * (180.0/3.14);
  roll = roll * (180.0/3.14) ;
}

void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);

  int AcXoff,AcYoff,AcZoff;
  int temp,toff;
  double t,tx,tf;

  //Acceleration data correction
  AcXoff = 0;
  AcYoff = 0;
  AcZoff = 0;

  //read accel data
  AcX=(Wire.read()<<8|Wire.read()) + AcXoff;
  AcY=(Wire.read()<<8|Wire.read()) + AcYoff;
  AcZ=(Wire.read()<<8|Wire.read()) + AcYoff;

  //get pitch/roll
  getAngle(AcX,AcY,AcZ);

  //send the data out the serial port
  Serial.print("(");
  Serial.print(roll);
  Serial.print(", ");
  Serial.print(pitch);
  Serial.print(")");
  Serial.println(" ");
  delay(333);
}

