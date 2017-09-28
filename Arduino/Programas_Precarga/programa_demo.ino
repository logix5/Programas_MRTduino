#include <Arduino.h>
#include <Wire.h>
#include <MrtDuino.h> //incluimos la libreria de MRT

#define MAX_PROGRAMS 12
double tiempo_inicio;
double programa;
double currentTime = 0;
double lastTime = 0;
decode_results results1;
int ir_id;
bool isIRreleased=true;
long irLastTime=0;

MrtIdSetting ir_id_set;
IRrecv irrecv1(10);
MrtButton button1(1);
MrtButton button2(2);
MrtAnalogInput irSensor3(3);
MrtAnalogInput irSensor4(4);
MrtAnalogInput irSensor5(5);
MrtAnalogInput cdsSensor6(6);
MrtDigitalOutput  led9(9);
MrtDigitalOutput  led10(10);
MrtBuzzer speaker16(16);
MrtMotor motor17(17);
MrtMotor motor18(18);

double getLastTime(){
					 return currentTime = millis()/1000.0 - lastTime;
					}


void setup(){
    Serial.begin(9600);
    SoftPWMBegin();
    tiempo_inicio = 3;
    programa = 0;
	ir_id=ir_id_set.ReadId();
    irrecv1.enableIRIn();
    
}

void programa_1(){
            Serial.println("Programa 1 -- Gimnasta");
            for(;;){
                    motor17.runMotor(100);
                    motor17.runMotor(100);
					motor18.runMotor(100);
                    motor18.runMotor(100);
                    delay(1000*3);
                    motor17.runMotor(-50);
                    motor17.runMotor(-50);
					motor18.runMotor(-50);
                    motor18.runMotor(-50);
                    delay(1000*2);
                    motor17.runMotor(75);
                    motor17.runMotor(75);
					motor18.runMotor(75);
                    motor18.runMotor(75);
                    delay(1000*4);
                    motor17.runMotor(-75);
                    motor17.runMotor(-75);
					motor18.runMotor(-75);
                    motor18.runMotor(-75);
                    delay(1000*3);
                    }

}

void programa_2(){
            Serial.println("Programa 2 -- Mando");
            for(;;){
				if((int)irrecv1.IR_KEY_VALUE==44){
					motor17.runMotor(100);
					motor18.runMotor(100);
					delay(1000*0.4);
				}
				if((int)irrecv1.IR_KEY_VALUE==62){
					motor17.runMotor(-100);
					motor18.runMotor(-100);
					delay(1000*0.4);
				}
				if((int)irrecv1.IR_KEY_VALUE==61){
					motor17.runMotor(100);
					motor18.runMotor(-100);
					delay(1000*0.4);
				}
				if((int)irrecv1.IR_KEY_VALUE==63){
					motor17.runMotor(-100);
					motor18.runMotor(100);
					delay(1000*0.4);
				}
				if((int)irrecv1.IR_KEY_VALUE==54){
					motor17.runMotor(50);
					motor18.runMotor(100);
					delay(1000*0.4);
				}
				if((int)irrecv1.IR_KEY_VALUE==60){
					motor17.runMotor(100);
					motor18.runMotor(50);
					delay(1000*0.4);
				}
				if((int)irrecv1.IR_KEY_VALUE==57){
					motor17.runMotor(-100);
					motor18.runMotor(-50);
					delay(1000*0.4);
				}
				if((int)irrecv1.IR_KEY_VALUE==51){
					motor17.runMotor(-50);
					motor18.runMotor(-100);
					delay(1000*0.4);
				}
				if(isIRreleased){
					motor17.runMotor(0);
					motor18.runMotor(0);
				}
				
				if(irrecv1.decode(&results1)){
					 isIRreleased=false;
					 irLastTime=millis();
					 ir_id=ir_id_set.ReadId(5);
					 irrecv1.setButtonValues(results1.value,ir_id);
					 irrecv1.resume();
				}
				else{
					 isIRreleased=true;
					irrecv1.IR_KEY_VALUE=0;
				}
			}

}

void programa_3(){
Serial.println("Programa 3 -- Tren con dos IR");
            for(;;){
					if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(0))){
						motor17.runMotor(80);
						motor18.runMotor(80);
					}
					if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(1))){
						motor17.runMotor(0);
						motor18.runMotor(80);
					}
					if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(0))){
						motor17.runMotor(80);
						motor18.runMotor(0);
					}
					if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(1))){
						motor17.runMotor(80);
						motor18.runMotor(0);
					}
      }
}

void programa_4(){
Serial.println("Programa 4 -- Wally");
            for(;;){
					if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(0))){
						motor17.runMotor(100);
						motor18.runMotor(100);
					}
					if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(1))){
						motor17.runMotor(-100);
						motor18.runMotor(-100);
						delay(1000*1);
						motor17.runMotor(100);
						motor18.runMotor(-100);
						delay(1000*0.5);
					}
					if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(0))){
						motor17.runMotor(-100);
						motor18.runMotor(-100);
						delay(1000*1);
						motor17.runMotor(-100);
						motor18.runMotor(100);
						delay(1000*0.5);
					}
					if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(1))){
						motor17.runMotor(-100);
						motor18.runMotor(-100);
						delay(1000*2);
						motor17.runMotor(100);
						motor18.runMotor(-100);
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
						motor17.runMotor(100);
						motor18.runMotor(100);
					}
					if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(0))){
					    led9.runSensor(1);
						led10.runSensor(0);
						motor17.runMotor(-25);
						motor18.runMotor(100);
					}
					if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(1))){
					    led9.runSensor(1);
						led10.runSensor(0);
						motor17.runMotor(100);
						motor18.runMotor(-25);
					}
					if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(0))){
					    led9.runSensor(0);
						led10.runSensor(1);
						motor17.runMotor(0);
						motor18.runMotor(0);
					}      
      }
}

void programa_6(){
Serial.println("Programa 6 -- Sumo");
            for(;;){
					if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(1))){
						motor17.runMotor(100);
						motor18.runMotor(100);
					}
					if((irSensor3.isDigitalSensed(1)) & (irSensor4.isDigitalSensed(0))){
						motor17.runMotor(-100);
						motor18.runMotor(-100);
						delay(1000*1);
						motor17.runMotor(100);
						motor18.runMotor(-100);
						delay(1000*0.5);
					}
					if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(1))){
						motor17.runMotor(-100);
						motor18.runMotor(-100);
						delay(1000*1);
						motor17.runMotor(-100);
						motor18.runMotor(100);
						delay(1000*0.5);
					}
					if((irSensor3.isDigitalSensed(0)) & (irSensor4.isDigitalSensed(0))){
						motor17.runMotor(-100);
						motor18.runMotor(-100);
						delay(1000*2);
						motor17.runMotor(100);
						motor18.runMotor(-100);
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
							motor17.runMotor(25);
						}
						if(((getLastTime()) > (2)) & ((getLastTime()) < (4))){
							motor17.runMotor(50);
						}
						if(((getLastTime()) > (4)) & ((getLastTime()) < (6))){
							motor17.runMotor(75);
						}
						if((getLastTime()) > (6)){
							motor17.runMotor(100);
						}
					}else{
						motor17.runMotor(0);
						motor18.runMotor(0);
						led9.runSensor(0);
						lastTime = millis()/1000.0;
						}
					}
	}

void programa_8(){
Serial.println("Programa 8 -- Mando con llave");
            for(;;){
				  if(irSensor3.isDigitalSensed(1)){
					if((int)irrecv1.IR_KEY_VALUE==44){
						motor17.runMotor(100);
						motor18.runMotor(100);
						delay(1000*0.4);
					}
					if((int)irrecv1.IR_KEY_VALUE==62){
						motor17.runMotor(-100);
						motor18.runMotor(-100);
						delay(1000*0.4);
					}
					if((int)irrecv1.IR_KEY_VALUE==61){
						motor17.runMotor(100);
						motor18.runMotor(-100);
						delay(1000*0.4);
					}
					if((int)irrecv1.IR_KEY_VALUE==63){
						motor17.runMotor(-100);
						motor18.runMotor(100);
						delay(1000*0.4);
					}
					if((int)irrecv1.IR_KEY_VALUE==54){
						motor17.runMotor(50);
						motor18.runMotor(100);
						delay(1000*0.4);
					}
					if((int)irrecv1.IR_KEY_VALUE==60){
						motor17.runMotor(100);
						motor18.runMotor(50);
						delay(1000*0.4);
					}
					if((int)irrecv1.IR_KEY_VALUE==57){
						motor17.runMotor(-100);
						motor18.runMotor(-50);
						delay(1000*0.4);
					}
					if((int)irrecv1.IR_KEY_VALUE==51){
						motor17.runMotor(-50);
						motor18.runMotor(-100);
						delay(1000*0.4);
					}
					if(isIRreleased){
						motor17.runMotor(0);
						motor18.runMotor(0);
					}
				}
						
				if(irrecv1.decode(&results1)){
					 isIRreleased=false;
					 irLastTime=millis();
					 ir_id=ir_id_set.ReadId(5);
					 irrecv1.setButtonValues(results1.value,ir_id);
					 irrecv1.resume();
				}
				else{
					 isIRreleased=true;
					irrecv1.IR_KEY_VALUE=0;
				}
      }
}


void programa_9(){
Serial.println("Programa 9 -- Pistola");
            for(;;){
					if((int)irrecv1.IR_KEY_VALUE==61){
						motor17.runMotor(100);
						delay(1000*0.4);
					}
					if((int)irrecv1.IR_KEY_VALUE==63){
						motor17.runMotor(-100);
						delay(1000*0.4);
					}
					if(isIRreleased){
						motor17.runMotor(0);
						motor18.runMotor(0);
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
					
					if(irrecv1.decode(&results1)){
						 isIRreleased=false;
						 irLastTime=millis();
						 ir_id=ir_id_set.ReadId(5);
						 irrecv1.setButtonValues(results1.value,ir_id);
						 irrecv1.resume();
					}
					else{
						 isIRreleased=true;
						irrecv1.IR_KEY_VALUE=0;
					}
    
      
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
						motor17.runMotor(100);
						motor18.runMotor(100);
						led9.runSensor(1);
						led10.runSensor(1);
					}
					else {
						motor17.runMotor(0);
						motor18.runMotor(0);
						led9.runSensor(0);
						led10.runSensor(0);
					}
            }
}

void programa_12(){
			Serial.println("Programa 12 -- Piano con sensores y teclas F del mando");
            for(;;){
						if((button1.isPressed(1)) | ((int)irrecv1.IR_KEY_VALUE==50)){
							speaker16.tone2(262,500);
											}
						if((button2.isPressed(1)) | ((int)irrecv1.IR_KEY_VALUE==35)){
							speaker16.tone2(294,500);
						}
						if((irSensor3.isDigitalSensed(1)) | ((int)irrecv1.IR_KEY_VALUE==52)){
							speaker16.tone2(330,500);
						}
						if((irSensor4.isDigitalSensed(1)) | ((int)irrecv1.IR_KEY_VALUE==37)){
							speaker16.tone2(349,500);
						}
						if((irSensor5.isDigitalSensed(1)) | ((int)irrecv1.IR_KEY_VALUE==38)){
							speaker16.tone2(392,500);
						}
						if((cdsSensor6.isDigitalSensed(1)) | ((int)irrecv1.IR_KEY_VALUE==55)){
							speaker16.tone2(440,500);
						}
						
						if(irrecv1.decode(&results1)){
							 isIRreleased=false;
							 irLastTime=millis();
							 ir_id=ir_id_set.ReadId(5);
							 irrecv1.setButtonValues(results1.value,ir_id);
							 irrecv1.resume();
						}
						else{
							 isIRreleased=true;
							irrecv1.IR_KEY_VALUE=0;
						}
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
            speaker16.tone2(262,200);
            delay(200);
        }
        if(((programa)==(2))){
            speaker16.tone2(294,200);
             delay(200);
        }
    
    if(((programa)==(3))){
            speaker16.tone2(330,200);
             delay(200);
        }
    if(((programa)==(4))){
            speaker16.tone2(349,200);
             delay(200);
        }
    if(((programa)==(5))){
            speaker16.tone2(392,200);
             delay(200);
        }
    if(((programa)==(6))){
            speaker16.tone2(440,200);
             delay(200);
        }
    if(((programa)==(7))){
            speaker16.tone2(494,200);
             delay(200);
        }
    if(((programa)==(8))){
            speaker16.tone2(2093,200);
             delay(200);
        }
    if(((programa)==(9))){
            speaker16.tone2(2349,200);
             delay(200);
        }
    if(((programa)==(10))){
            speaker16.tone2(2637,200);
             delay(200);
        }
    if(((programa)==(11))){
            speaker16.tone2(2794,200);
             delay(200);
        }
    if(((programa)==(12))){
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
