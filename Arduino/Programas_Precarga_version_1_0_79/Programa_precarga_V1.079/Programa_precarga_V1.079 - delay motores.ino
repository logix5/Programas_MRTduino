#include <Arduino.h>
#include <Wire.h>


#include <MrtDuino.h>

#define MAX_PROGRAMS 12
double tiempo_inicio;
unsigned int programa;
unsigned int programa_final;
double currentTime = 0;
double lastTime = 0;
unsigned int mando;

char readValue=0;
IRrecv irrecv1(10);
 MrtIdSetting ir_id_set;
 int ir_id;
 int remote_button;


MrtMotor motor1;
MrtMotor motor2;
MrtMotor motor3;
MrtMotor motor4;
MrtButton button1(1);
MrtButton button2(2);
MrtAnalogInput irSensor3(3);
MrtAnalogInput irSensor4(4);
MrtAnalogInput irSensor5(5);
MrtAnalogInput cdsSensor6(6);
MrtDigitalOutput  led9(9);
MrtDigitalOutput  led10(10);
MrtBuzzer speaker16;


double getLastTime(){
           return currentTime = millis()/1000.0 - lastTime;
          }
          

void setup(){
    Serial.begin(115200);
    irrecv1.enableIRIn();
    mando=0;
    tiempo_inicio = 3;
    programa = 0;
    programa_final=0;
  
}

void programa_1(){
            Serial.println("Programa 1 -- Gimnasta");
            for(;;){
                    motor1.runMotor(1,100);
					delay(100);
                    motor2.runMotor(2,100);
					delay(100);
                    motor3.runMotor(3,100);
					delay(100);
                    motor4.runMotor(4,100);
                    delay(1000*3);
                    motor1.runMotor(1,-50);
					delay(50);
                    motor2.runMotor(2,-50);
					delay(50);
                    motor3.runMotor(3,-50);
					delay(50);
                    motor4.runMotor(4,-50);
                    delay(1000*2);
                    motor1.runMotor(1,75);
					delay(50);
                    motor2.runMotor(2,75);
					delay(50);
                    motor3.runMotor(3,75);
					delay(50);
                    motor4.runMotor(4,75);
                    delay(1000*4);
                    motor1.runMotor(1,-75);
					delay(50);
                    motor2.runMotor(2,-75);
					delay(50);
                    motor3.runMotor(3,-75);
					delay(50);
                    motor4.runMotor(4,-75);
                    delay(1000*3);
                    }

}

void programa_2(){
           
            
             if(irrecv1.mrtRemoteStateCheck(remote_button, 44)){
                motor1.runMotor(1,80);
				 delay(60);
                motor2.runMotor(2,80);
				 delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 62)){
                motor1.runMotor(1,-80);
				 delay(60);
                motor2.runMotor(2,-80);
				 delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 63)){
                motor1.runMotor(1,-80);
				 delay(60);
                motor2.runMotor(2,80);
				 delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 61)){
                motor1.runMotor(1,80);
				delay(60);
                motor2.runMotor(2,-80);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 54)){
                motor1.runMotor(1,0);
				delay(60);
                motor2.runMotor(2,80);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 60)){
                motor1.runMotor(1,80);
				delay(60);
                motor2.runMotor(2,0);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 57)){
                motor1.runMotor(1,-80);
				delay(60);
                motor2.runMotor(2,0);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 51)){
                motor1.runMotor(1,0);
				delay(60);
                motor2.runMotor(2,-80);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 53)){
                motor1.runMotor(1,0);
				delay(60);
                motor2.runMotor(2,0);
				delay(60);
            }

            
    }


void programa_3(){
Serial.println("Programa 3 -- Tren con dos IR");
            for(;;){
          if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(0))){
            motor1.runMotor(1,70);
			delay(50);
            motor2.runMotor(2,70);
			delay(50);
          }
          if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(1))){
            motor1.runMotor(1,0);
			delay(50);
            motor2.runMotor(2,70);
			delay(50);
          }
          if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(0))){
            motor1.runMotor(1,70);
			delay(50);
            motor2.runMotor(2,0);
			delay(50);
          }
          if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(1))){
            motor1.runMotor(1,70);
			delay(50);
            motor2.runMotor(2,0);
			delay(50);
          }
      }
}

void programa_4(){
Serial.println("Programa 4 -- Wally");
            for(;;){
          if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(0))){
            motor1.runMotor(1,80);
			delay(60);
            motor2.runMotor(2,80);
			delay(60);
          }
          if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(1))){
            motor1.runMotor(1,-80);
			delay(60);
            motor2.runMotor(2,-80);
            delay(1000*1);
            motor1.runMotor(1,80);
			delay(60);
            motor2.runMotor(2,-80);
            delay(1000*0.5);
          }
          if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(0))){
            motor1.runMotor(1,-80);
			delay(60);
            motor2.runMotor(2,-80);
            delay(1000*1);
            motor1.runMotor(1,-80);
			delay(60);
            motor2.runMotor(2,80);
            delay(1000*0.5);
          }
          if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(1))){
            motor1.runMotor(1,-80);
			delay(60);
            motor2.runMotor(2,-80);
            delay(1000*2);
            motor1.runMotor(1,80);
			delay(60);
            motor2.runMotor(2,-80);
            delay(1000*0.5);
          }
      
      }
}

void programa_5(){
Serial.println("Programa 5 -- Pato");
            for(;;){
          if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(1))){
            led9.runSensor(1);
            led10.runSensor(0);
            motor1.runMotor(1,80);
			delay(60);
            motor2.runMotor(2,80);
			delay(60);
          }
          if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(0))){
            led9.runSensor(1);
            led10.runSensor(0);
            motor1.runMotor(1,-25);
			delay(60);
            motor2.runMotor(2,80);
			delay(60);
          }
          if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(1))){
            led9.runSensor(1);
            led10.runSensor(0);
            motor1.runMotor(1,80);
			delay(60);
            motor2.runMotor(2,-25);
			delay(60);
          }
          if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(0))){
            led9.runSensor(0);
            led10.runSensor(1);
            motor1.runMotor(1,0);
			delay(60);
            motor2.runMotor(2,0);
			delay(60);
          }      
      }
}

void programa_6(){
Serial.println("Programa 6 -- Sumo");
            for(;;){
          if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(1))){
            motor1.runMotor(1,90);
			delay(50);
            motor2.runMotor(2,90);
			delay(50);
          }
          if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(0))){
            motor1.runMotor(1,-90);
			delay(50);
            motor2.runMotor(2,-90);
            delay(1000*1);
            motor1.runMotor(1,90);
			delay(50);
            motor2.runMotor(2,-90);
            delay(1000*0.5);
          }
          if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(1))){
            motor1.runMotor(1,-90);
			delay(50);
            motor2.runMotor(2,-90);
            delay(1000*1);
            motor1.runMotor(1,-90);
			delay(50);
            motor2.runMotor(2,90);
            delay(1000*0.5);
          }
          if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(0))){
            motor1.runMotor(1,-90);
			delay(50);
            motor2.runMotor(2,-90);
            delay(1000*2);
            motor1.runMotor(1,90);
			delay(50);
            motor2.runMotor(2,-90);
            delay(1000*0.5);
          }
      }
}

void programa_7(){
      Serial.println("Programa 7 -- Peonza ");
      lastTime = millis()/1000.0;
            for(;;){
            if(button1.isPressed(1)){
              led9.runSensor(1);
            if((getLastTime()) < (2)){
              motor1.runMotor(1,25);
            }
            if(((getLastTime()) > (2)) & ((getLastTime()) < (4))){
              motor1.runMotor(1,50);
            }
            if(((getLastTime()) > (4)) & ((getLastTime()) < (6))){
              motor1.runMotor(1,75);
            }
            if((getLastTime()) > (6)){
              motor1.runMotor(1,100);
            }
          }else{
            motor1.runMotor(1,0);
            led9.runSensor(0);
            lastTime = millis()/1000.0;
            }
          }
  }

void programa_8(){
            
            

         if(irSensor3.isDigitalSensed(1)){ 
              if(irrecv1.mrtRemoteStateCheck(remote_button, 44)){
                motor1.runMotor(1,80);
				 delay(60);
                motor2.runMotor(2,80);
				 delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 62)){
                motor1.runMotor(1,-80);
				 delay(60);
                motor2.runMotor(2,-80);
				 delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 63)){
                motor1.runMotor(1,-80);
				 delay(60);
                motor2.runMotor(2,80);
				 delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 61)){
                motor1.runMotor(1,80);
				delay(60);
                motor2.runMotor(2,-80);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 54)){
                motor1.runMotor(1,0);
				delay(60);
                motor2.runMotor(2,80);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 60)){
                motor1.runMotor(1,80);
				delay(60);
                motor2.runMotor(2,0);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 57)){
                motor1.runMotor(1,-80);
				delay(60);
                motor2.runMotor(2,0);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 51)){
                motor1.runMotor(1,0);
				delay(60);
                motor2.runMotor(2,-80);
				delay(60);
            }
            if(irrecv1.mrtRemoteStateCheck(remote_button, 53)){
                motor1.runMotor(1,0);
				delay(60);
                motor2.runMotor(2,0);
				delay(60);
            }
              
          
         } 
    }

void programa_9(){

                   

        if(irrecv1.mrtRemoteStateCheck(remote_button, 61)){
            motor1.runMotor(1,90);
           
          }
          if(irrecv1.mrtRemoteStateCheck(remote_button, 63)){
            motor1.runMotor(1,-90);
            
          }
         if(irrecv1.mrtRemoteStateCheck(remote_button, 53)){
            motor1.runMotor(1,0);
          }
          if(irSensor3.isDigitalSensed(1)){
            led9.runSensor(1);
            speaker16.tone2(262,500);
            speaker16.tone2(294,500);
            speaker16.tone2(330,500);
            speaker16.tone2(349,500);
            delay(1000*5);
            led9.runSensor(0);
          }
          
            
     
      
}

   
 void programa_10(){
      Serial.println("Programa 10 -- Parpadeo de Leds alterno");
            for(;;){
          led9.runSensor(1);
          led10.runSensor(0);
          delay(1000*1);
          led9.runSensor(0);
          led10.runSensor(1);
          delay(1000*1);
          }
}

void programa_11(){
      Serial.println("Programa 11 -- LDR");
            for(;;){
           if(cdsSensor6.isDigitalSensed(1)){
            motor1.runMotor(1,90);
			delay(50);
            motor2.runMotor(2,90);
			delay(50);
            led9.runSensor(1);
            led10.runSensor(1);
          }
          else {
            motor1.runMotor(1,0);
            motor2.runMotor(2,0);
            led9.runSensor(0);
            led10.runSensor(0);
          }
            }
}

void programa_12(){
     
           

            if((button1.isPressed(1)) || ((int)irrecv1.mrtRemoteStateCheck(remote_button, 50))){
              speaker16.initBuzzer(16);
              speaker16.tone2(262,500);
                      }
            if((button2.isPressed(1)) || ((int)irrecv1.mrtRemoteStateCheck(remote_button, 35))){
              speaker16.initBuzzer(16);
              speaker16.tone2(294,500);
            }
            if((irSensor3.isDigitalSensed(1)) || ((int)irrecv1.mrtRemoteStateCheck(remote_button, 52))){
               speaker16.initBuzzer(16);
              speaker16.tone2(330,500);
            }
            if((irSensor4.isDigitalSensed(1)) || ((int)irrecv1.mrtRemoteStateCheck(remote_button, 37))){
               speaker16.initBuzzer(16);
              speaker16.tone2(349,500);
            }
            if((irSensor5.isDigitalSensed(1)) || ((int)irrecv1.mrtRemoteStateCheck(remote_button, 38))){
               speaker16.initBuzzer(16);
              speaker16.tone2(392,500);
            }
            if((cdsSensor6.isDigitalSensed(1)) || ((int)irrecv1.mrtRemoteStateCheck(remote_button, 55))){
               speaker16.initBuzzer(16);
              speaker16.tone2(440,500);
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
           speaker16.initBuzzer(16);
            speaker16.tone2(262,200);
            delay(200);
        }
        if(((programa)==(2))){
           speaker16.initBuzzer(16);
            speaker16.tone2(294,200);
             delay(200);
        }
    
    if(((programa)==(3))){
       speaker16.initBuzzer(16);
            speaker16.tone2(330,200);
             delay(200);
        }
    if(((programa)==(4))){
       speaker16.initBuzzer(16);
            speaker16.tone2(349,200);
             delay(200);
        }
    if(((programa)==(5))){
       speaker16.initBuzzer(16);
            speaker16.tone2(392,200);
             delay(200);
        }
    if(((programa)==(6))){
       speaker16.initBuzzer(16);
            speaker16.tone2(440,200);
             delay(200);
        }
    if(((programa)==(7))){
       speaker16.initBuzzer(16);
            speaker16.tone2(494,200);
             delay(200);
        }
    if(((programa)==(8))){
       speaker16.initBuzzer(16);
            speaker16.tone2(2093,200);
             delay(200);
        }
    if(((programa)==(9))){
       speaker16.initBuzzer(16);
            speaker16.tone2(2349,200);
             delay(200);
        }
    if(((programa)==(10))){
       speaker16.initBuzzer(16);
            speaker16.tone2(2637,200);
             delay(200);
        }
    if(((programa)==(11))){
       speaker16.initBuzzer(16);
            speaker16.tone2(2794,200);
             delay(200);
        }
    if(((programa)==(12))){
       speaker16.initBuzzer(16);
            speaker16.tone2(3136,200);
             delay(200);
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


    if ( (programa)==(2) || (programa)==(8)  || (programa)==(9)  ||  (programa)==(12) )
    {
      mando=1;
    }
        
           
    if(((programa)==(10))){
            programa_10();
        } 
    if(((programa)==(11))){
            programa_11();
        } 
    
        
         lastTime = millis()/1000.0;
    }
   
    currentTime = millis()/1000.0 - lastTime;

    // Para los programas de mando
    if (mando==1){
      
      if (programa==2)
      {
       Serial.println("Programa 2 -- Mando");
       programa_final=2;
       }
 
      if (programa==8)
      {
       Serial.println("Programa 8 -- Mando con llave");
       programa_final=8;
       }
        if (programa==9)
      {
        Serial.println("Programa 9 -- Pistola");
        programa_final=9;
       }
       if (programa==12)
       {
       Serial.println("Programa 12 -- Piano con sensores y teclas F del mando");
       programa_final=12;
       }
       
      for(;;){

       if(((programa_final)==(2))){
            programa_2();
        }
       if(((programa_final)==(8))){
            programa_8();
        } 
       if(((programa_final)==(9))){
            programa_9();
        } 

       if(((programa_final)==(12))){
            programa_12();
        } 
       
         //Si se ponen estas líneas en más partes del código , entonces falla el mando. Esta es la solución para meterlo con MRTduino para MRTScratch
         ir_id = ir_id_set.ReadId(5);
         remote_button = irrecv1.mrtRemoteLoop(ir_id);
        }
    }
   
    
}
