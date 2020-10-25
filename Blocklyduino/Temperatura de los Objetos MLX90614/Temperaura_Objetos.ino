/*******************************************
***    ARDUINO CODE -- MRTDUINO BOARD    ***
***       Logix5 -- www.logix5.com       ***
********************************************/
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
long temps60 = 0 ;

void setup()
{
  Serial.begin(115200);

  Serial1.begin(9600);

  mlx.begin();  
  delay((long)3*1000);
  pinMode(21,INPUT);
    Serial1.print("t3.txt=");
  Serial1.write(0x22);
  Serial1.print(String(mlx.readAmbientTempC()));
  Serial1.write(0x22);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

}


void loop()
{
  
    if (digitalRead(21)) {
      Serial.println("Botón presionado");
      Serial1.print("t1.txt=");
      Serial1.write(0x22);
      Serial1.print(String(mlx.readObjectTempC(),1));
      Serial1.write(0x22);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      delay((long)5*1000);
      Serial1.print("t1.txt=");
      Serial1.write(0x22);
      Serial1.print("--.-");
      Serial1.write(0x22);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);

    }
    if ((millis()-temps60)>=30*1000) {
      temps60=millis();
      Serial.println("Medimos temperatura ambiente");
      Serial1.print("t3.txt=");
      Serial1.write(0x22);
      Serial1.print(String(mlx.readAmbientTempC()));
      Serial1.write(0x22);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }

}
