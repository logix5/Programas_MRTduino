#include <Arduino.h>
#include <Wire.h>
#include <MrtDuino.h> //incluimos la libreria de MRT

#define MAX_PROGRAMS 12
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
                    motor17.runMotor(100);
                    motor17.runMotor(100);
                    delay(1000*3);
                    motor17.runMotor(-50);
                    motor17.runMotor(-50);
                    delay(1000*2);
                    motor17.runMotor(75);
                    motor17.runMotor(75);
                    delay(1000*4);
                    motor17.runMotor(-75);
                    motor17.runMotor(-75);
                    delay(1000*3);
                    }

}

void programa_2(){
             Serial.println("Programa 2");
            for(;;){
                   
                    }

}

void programa_3(){
Serial.println("Programa 3");
            for(;;){
      
      
      }
}

void programa_4(){
Serial.println("Programa 4");
            for(;;){
      
      
      }
}


void programa_5(){
Serial.println("Programa 5");
            for(;;){
      
      
      }
}

void programa_6(){
Serial.println("Programa 6");
            for(;;){
      
      
      }
}

void programa_7(){
Serial.println("Programa 7");
            for(;;){
      
      
      }
}

void programa_8(){
Serial.println("Programa 8");
            for(;;){
      
      
      }
}


void programa_9(){
Serial.println("Programa 9");
            for(;;){
      
      
      }
}

void programa_10(){
Serial.println("Programa 10");
            for(;;){
      
      
      }
}

void programa_11(){
Serial.println("Programa 11");
            for(;;){
      
      
      }
}

void programa_12(){
Serial.println("Programa 12");
            for(;;){
      
      
      }
}


void loop(){
    
  //Si se pulsa el botón, se selecciona el tono a cada programa
  //Despues de la primera escala musicallo ideal es subir a otra más alta para diferenciar 
  //las mismas notas 
  
    if(ir_id_set.isStartPressed()){
        programa += 1;
    if (programa>MAX_PROGRAMS)
      programa=1;
    
        if(((programa)==(1))){
            speaker16.tone2(262,500);
            delay(300);
        }
        if(((programa)==(2))){
            speaker16.tone2(294,500);
             delay(300);
        }
    
    if(((programa)==(3))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(4))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(5))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(6))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(7))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(8))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(9))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(10))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(11))){
            speaker16.tone2(294,500);
             delay(300);
        }
    if(((programa)==(12))){
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
     if(((programa)==(3))){
            programa_3();
        } 
    if(((programa)==(4))){
            programa_4();
        } 
    if(((programa)==(5))){
            programa_5();
        } 
    if(((programa)==(6))){
            programa_6();
        } 
    if(((programa)==(7))){
            programa_7();
        } 
    if(((programa)==(8))){
            programa_8();
        } 
    if(((programa)==(9))){
            programa_9();
        } 
    if(((programa)==(10))){
            programa_10();
        } 
    if(((programa)==(11))){
            programa_11();
        } 
    if(((programa)==(12))){
            programa_12();
        } 
        
         lastTime = millis()/1000.0;
    }
   
    currentTime = millis()/1000.0 - lastTime;
    
    char readValue=0;
    if(Serial.available()){
         readValue=Serial.read();
    }
    
    
}
