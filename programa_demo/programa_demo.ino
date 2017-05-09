#include <Arduino.h>
#include <Wire.h>
#include <MrtDuino.h>

double tiempo_inicio;
double programa;

MrtIdSetting ir_id_set;
MrtBuzzer speaker16(16);

double currentTime = 0;
double lastTime = 0;

MrtDigitalOutput  led9(9);
MrtMotor motor17(17);



void setup(){
    Serial.begin(9600);
    SoftPWMBegin();
    tiempo_inicio = 5;
    programa = 0;
    
}

void programa_1(){
            Serial.println("Programa 1");
            for(;;){
                    led9.runSensor(1);
                    delay(1000*1);
                    led9.runSensor(0);
                    delay(1000*1);
                    }

}

void programa_2(){
             Serial.println("Programa 2");
            for(;;){
                    motor17.runMotor(100);
                    motor17.runMotor(100);
                    delay(1000*1);
                    motor17.runMotor(-50);
                    motor17.runMotor(-50);
                    delay(1000*2);
                    motor17.runMotor(75);
                    motor17.runMotor(75);
                    delay(1000*3);
                    }

}

void loop(){
    
    if(ir_id_set.isStartPressed()){
        programa += 1;
        if(((programa)==(1))){
            speaker16.tone2(262,500);
            delay(300);
        }
        if(((programa)==(2))){
            speaker16.tone2(294,500);
             delay(300);
        }
        lastTime = millis()/1000.0;
    }
    
    if((currentTime) > (tiempo_inicio)){

      if(((programa)==(0))){
          Serial.println("No se pulso tecla, volvemos a esperar tecla");
      }
        if(((programa)==(1))){
          programa_1();
        }
        if(((programa)==(2))){
            programa_2();
        }
         lastTime = millis()/1000.0;
    }
   
    currentTime = millis()/1000.0 - lastTime;
    
    char readValue=0;
    if(Serial.available()){
         readValue=Serial.read();
    }
    
    
}

