#include "functions_codes.h" 
#include <avr/io.h>

#define T_PULSAR 3
#define T_ROJO  10
#define T_VERDE  20
#define MAX_PROGRAMS 13

uint8_t timerOverflowCount=0; 
uint8_t programa=0; 
uint8_t velocidad=0;
uint8_t estado_semaforo=0;
uint8_t tiempo_semaforo=0;


void modo1(void)
{
   debug("Programa 1.El Gimnasta.Mueve los dos motores\n"); 
    while(1){
                dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
                dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
                delay(0, 0, 3, 0);
                dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -5);
                dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -5);
                delay(0, 0, 2, 0);
                dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 7);
                dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 7);
                delay(0, 0, 4, 0);
                dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -7);
                dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -7);
                delay(0, 0, 3, 0);
    }    
 }

void modo2(void)
{
    debug("Programa 2.Mando\n"); 
    while(1){
       
        if(rc(UP_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
        }
    
        if(rc(DOWN_KEY) == TRUE){
        
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            
        }
        
        if(rc(LEFT_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
            
        }
        
        if(rc(RIGHT_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            
        }
        
        if(rc(UP_AND_LEFT_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10); 
        }
    
        if(rc(UP_AND_RIGHT_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
        }

        if(rc(DOWN_AND_LEFT_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
        }

        if(rc(DOWN_AND_RIGHT_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
        }
            
        if(rc(OFF_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
            dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0); 
        }
    }    
 }

void modo3(void)
{
    debug("Programa 3.Tren con dos IR para seguir línea negra. Al ser línea 70 el umbral \n"); 
    while(1){
	    if(ir_Modul(2, 70, NONE) == TRUE && ir_Modul(3, 70, NONE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 8);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 8);
        }
        if(ir_Modul(2, 70, SENSE) == TRUE && ir_Modul(3, 70, NONE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 8);
            dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);  
        }
        if(ir_Modul(2, 70, NONE) == TRUE && ir_Modul(3, 70, SENSE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 8);
            
        }
        if(ir_Modul(2, 70, SENSE) == TRUE && ir_Modul(3, 70, SENSE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 8);
            dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0); 
        }
    }    
 }

void modo4(void)
{
    debug("Programa 4. Wally evitar chocarse. Camnión de bomberos. Al no ser línes 50 el umbral \n"); 
    while(1){
		
		if(ir_Modul(2, 50, NONE) == TRUE && ir_Modul(3, 50, NONE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
        }
		if(ir_Modul(2, 50, SENSE) == TRUE && ir_Modul(3, 50, NONE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 1, 0);
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 0, 500);
        }
		if(ir_Modul(2, 50, NONE) == TRUE && ir_Modul(3, 50, SENSE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 1, 0);
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
            delay(0, 0, 0, 500);
        }
		if(ir_Modul(2, 50, SENSE) == TRUE && ir_Modul(3, 50, SENSE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 1, 0);
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 0, 500);
        }
    }    
 }

void modo5(void)
{
    debug("Programa 5.Pato. Que te siga \n"); 
    while(1){
	   if(ir_Modul(2, 50, SENSE) == TRUE && ir_Modul(3, 50, SENSE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
        }
		if(ir_Modul(2, 50, NONE) == TRUE && ir_Modul(3, 50, NONE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
            dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
         
        }
		if(ir_Modul(2, 50, NONE) == TRUE && ir_Modul(3, 50, SENSE) == TRUE){ 
            
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -2);

        }
		if(ir_Modul(2, 50, SENSE) == TRUE && ir_Modul(3, 50, NONE) == TRUE){ 
            
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -2);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
     
        }
    }    
 }

void modo6(void)
{
    debug("Programa 6.Sumo\n"); 
    while(1){
		
		if(ir_Modul(2, 70, SENSE) == TRUE && ir_Modul(3, 70, SENSE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
        }
		if(ir_Modul(2, 70, SENSE) == TRUE && ir_Modul(3, 70, NONE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 1, 0);
			dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
            delay(0, 0, 0, 500);
        }
		if(ir_Modul(2, 70, NONE) == TRUE && ir_Modul(3, 70, SENSE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 1, 0);
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 0, 500);
        }
		if(ir_Modul(2, 70, NONE) == TRUE && ir_Modul(3, 70, NONE) == TRUE){ 
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 1, 0);
            dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
            dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
            delay(0, 0, 0, 500);
        }
    }    
 }

void modo7(void)
{
    debug("Programa 7.Peonza.Aumenta velocidad con tiempo\n"); 
    velocidad=0;
    while(1){
        
            if((TIFR & (1<<OCF1A)) != 0)
             {
              TCNT1 = 0; 
              TIFR |= (1<<OCF1A) ; //clear timer1 overflow flag    
              velocidad++;  
             }           
             if(touch(1, PRESSED) == TRUE)
			 { 
				 if(velocidad < 2){    
					 dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 2);
					 dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 2);
						 }
				 if ((velocidad >= 2) & (velocidad <4) ){		  
					 dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 4);
					 dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 4);
						 }
				 if ((velocidad >= 4) & (velocidad <6) ){ 
					 dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 6);
					 dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 6);
						 }
				 if ((velocidad >= 6) & (velocidad <7) ){	 
					 dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 8);
					 dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 8);
						 }
				 if (velocidad >= 7){
					 dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
					 dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10); 
						 }
              }
            else
                { 
                    dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
                    dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
                    velocidad=0;
                }
    }    
 }

void modo8(void)
{
    debug("Programa 8.Coche con llave \n"); 
    while(1){
		
		if(ir_Modul(2, 50, SENSE) == TRUE){
		
			if(rc(UP_KEY) == TRUE){
				dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
				dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
			}
		
			if(rc(DOWN_KEY) == TRUE){
			
				dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
				dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
				
			}
			
			if(rc(LEFT_KEY) == TRUE){
				dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
				dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
				
			}
			
			if(rc(RIGHT_KEY) == TRUE){
				dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
				dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
				
			}
			
			if(rc(UP_AND_LEFT_KEY) == TRUE){
				dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
				dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10); 
			}
		
			if(rc(UP_AND_RIGHT_KEY) == TRUE){
				dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
				dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
			}

			if(rc(DOWN_AND_LEFT_KEY) == TRUE){
				dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
				dc_motor(RIGHT_MOTOR_1, BACKWARD_DIRECTION, -10);
			}

			if(rc(DOWN_AND_RIGHT_KEY) == TRUE){
				dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION, -10);
				dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
			}
				
			if(rc(OFF_KEY) == TRUE){
				dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
				dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0); 
			}
	   
	   }
    }    
 }

void modo9(void)
{
    debug("Programa 9.Diana \n"); 
    while(1){
        if(rc(LEFT_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1,FORWARD_DIRECTION,8);
        }
        
        if(rc(RIGHT_KEY) == TRUE){
            dc_motor(LEFT_MOTOR_1, BACKWARD_DIRECTION,-8);
        }
           
        if(rc(OFF_KEY) == TRUE){
       
            dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
            dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
        }
		
		if(ir_Modul(2, 50, SENSE) == TRUE){ 
        
            digitalWrite(1, HIGH);
            digitalWrite(2, HIGH);
            tone(6, 800, 500);
            tone(6, 1300, 500);
            tone(6, 1800, 500);
            delay(0, 0, 5, 0);
            digitalWrite(1, LOW);
            digitalWrite(2, LOW);
        }
	
    }    
 }

void modo10(void)
{
    debug("Programa 10.Parapadeo cada seg de los leds \n"); 
    while(1){
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        delay(0, 0, 1, 0);
        digitalWrite(1, LOW);
        digitalWrite(2, LOW);
        delay(0, 0, 1, 0);
		}    
 }

void modo11(void)
{
    debug("Programa 11.Si no hay luz activamos motores y leds \n"); 
    while(1){
	    if(cds(5, 0, DARK) == TRUE)
		{ 
			dc_motor(LEFT_MOTOR_1, FORWARD_DIRECTION, 10);
			dc_motor(RIGHT_MOTOR_1, FORWARD_DIRECTION, 10);
			digitalWrite(1, HIGH);
			digitalWrite(2, HIGH);
        }
        else
		{
			dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
			dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
			digitalWrite(1, LOW);
			digitalWrite(2, LOW);
		}
       
    }    
 }

void modo12(void)
{
    debug("Programa 12.Barrera y luces. Al pulsar sube\n"); 
    while(1){
       if(touch(1, PRESSED) == TRUE)
	   { 
       
            servo(3, -90);
            digitalWrite(1, HIGH);
            digitalWrite(2, LOW);
            delay(0, 0, 2, 0);
            servo(3, 0);
		}    
	else
		{ 
	     digitalWrite(1, LOW);
         digitalWrite(2, HIGH);
		} 
	}	
 }
 
 void modo13(void)
{
    debug("Programa 13.Semáforo con botón de peatón.Led 1 Verde, Led 2 Rojo\n"); 
	estado_semaforo=0;
	tiempo_semaforo =0;
	digitalWrite(1, LOW);
	digitalWrite(2, HIGH);
    while(1){
		
		if((TIFR & (1<<OCF1A)) != 0)
             {
              TCNT1 = 0; 
              TIFR |= (1<<OCF1A) ; //clear timer1 overflow flag 
			  tiempo_semaforo++;			  
             }  

		if (estado_semaforo ==0)
		 {
			if( tiempo_semaforo >= T_ROJO)
				{
				 tiempo_semaforo =0;
				 estado_semaforo=1;
				 digitalWrite(1, HIGH);
				 digitalWrite(2, LOW);
				}
		 }	
		 else
		 {
			if( tiempo_semaforo >= T_VERDE)
				{
				 tiempo_semaforo =0;
				 estado_semaforo=0;
				 digitalWrite(1, LOW);
				 digitalWrite(2, HIGH);
				}
		 }	
	 
		if(touch(1, PRESSED) == TRUE)
		  { 
		   if (estado_semaforo==1)
				{  
				  estado_semaforo=0;
				  tiempo_semaforo=0;
				  digitalWrite(1, LOW);
				  digitalWrite(2, HIGH);
				  
				}
		  }    
	
	}	
 }
   

int main(void){ 
    mcu_initialization();
    TCCR1B = (1<<CS10) | (1<<CS12); //set the pre-scalar as 1024
    OCR1A = 15625;      //1seg delay
    TCNT1 = 0;
   
 while(1){
    
    if((TIFR & (1<<OCF1A)) != 0)
      {
         TCNT1 = 0; 
         TIFR |= (1<<OCF1A) ; //clear timer1 overflow flag    
         
         timerOverflowCount++;      
         //Cada 60 veces es aproximadamente 1 seg * Tiempo de pulsar
         if (timerOverflowCount>=T_PULSAR)
         {         
            timerOverflowCount=0;
            if (programa==0)
                debug("No se ha seleccionado ningun programa\n");
            else
            {
                switch (programa)
                 {
                   case 1:
                           modo1();
                           break;
                   case 2:
                           modo2();
                           break;
                   case 3:
                           modo3();
                           break; 
                   case 4:
                           modo4();
                           break; 
                   case 5:
                           modo5();
                           break; 
                   case 6:
                           modo6();
                           break; 
                   case 7:
                           modo7();
                           break; 
                   case 8:
                           modo8();
                           break; 
                   case 9:
                           modo9();
                           break; 
                   case 10:
                           modo10();
                           break; 
                   case 11:
                           modo11();
                           break; 
                   case 12:
                           modo12();
                           break;      
				   case 13:
                           modo13();
                           break;   						   
                 } 
              
             }  
         }  
      }
     
      if(touch(5, PRESSED) == TRUE){
          
        programa += 1;
        timerOverflowCount=0;
        
        if (programa>MAX_PROGRAMS)
            programa=1;
        tone(6,1046,300);
        delay(0, 0, 0, 300);
      } 
     
    }
}