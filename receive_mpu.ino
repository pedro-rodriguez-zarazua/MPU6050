#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (7, 8); 
struct package
{
  double Ax, Ay, Az;
  double Gx,Gy,Gz;
};

byte addresses[][6] = {"0"}; 



typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  
{

  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print(data.Ax);Serial.print(',');
    Serial.print(data.Ay);Serial.print(',');
    Serial.print(data.Az);Serial.print(',');
    Serial.print(data.Gx);Serial.print(',');
    Serial.print(data.Gy);Serial.print(',');
    Serial.println(data.Gz);
  }

}
