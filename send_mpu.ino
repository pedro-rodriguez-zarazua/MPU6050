#include <SPI.h>  
#include "RF24.h"
#include "I2Cdev.h"
#include "MPU6050.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

MPU6050 sensor;
int ax, ay, az;
int gx, gy, gz;


struct package
{
  double Ax, Ay, Az;
  double Gx,Gy,Gz;

};


typedef struct package Package;
Package data;


void setup()
{
  Serial.begin(115200);
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
  // Leer las aceleraciones y velocidades angulares
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);
  
 
  
  myRadio.write(&data, sizeof(data)); 
  data.Ax = (ax+32768)/(65535.0);
  data.Ay = (ay+32768)/(65535.0);
  data.Az = (az+32768)/(65535.0);
  data.Gx = (gx+32768)/(2*32768.0);
  data.Gy = (gy+32768)/(2*32768.0);
  data.Gz = (gz+32768)/(2*32768.0);
  Serial.print(data.Ax);Serial.print(',');
  Serial.print(data.Ay);Serial.print(',');
  Serial.print(data.Az);Serial.print(',');
  Serial.print(data.Gx);Serial.print(',');
  Serial.print(data.Gy);Serial.print(',');
  Serial.println(data.Gz);
  
  delay(1);

}
