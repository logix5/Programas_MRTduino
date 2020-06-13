#include "functions_codes.h" 
#include <avr/io.h>

#define T_PULSAR 3
#define MAX_PROGRAMS 12

uint8_t timerOverflowCount=0; 
uint8_t programa=0; 
uint8_t velocidad=0;

void modo1(void)
{
   debug("Programa 1.El Gimnasta\n"); 
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
        
        
        
        
        
        
        
        
        
        
        
        
        
    
        if(rc(OFF_KEY) == TRUE){
       
            dc_motor(LEFT_MOTOR_1, STOP_DIRECTION, 0);
            dc_motor(RIGHT_MOTOR_1, STOP_DIRECTION, 0);
            
        }
    }    
 }

void modo3(void)
{
    debug("Programa 3. \n"); 
   // while(1){
       
   // }    
 }

void modo4(void)
{
    debug("Programa 4. \n"); 
   // while(1){
       
   // }    
 }

void modo5(void)
{
    debug("Programa 5. \n"); 
   // while(1){
       
   // }    
 }

void modo6(void)
{
    debug("Programa 6. \n"); 
   // while(1){
       
   // }    
 }

void modo7(void)
{
    debug("Programa 7.Peonza \n"); 
    velocidad=0;
    while(1){
        
            if((TIFR & (1<<OCF1A)) != 0)
             {
              TCNT1 = 0; 
              TIFR |= (1<<OCF1A) ; //clear timer1 overflow flag    
              velocidad++;  
             }           
             if(touch(1, PRESSED) == TRUE){ 
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
    debug("Programa 8. \n"); 
   // while(1){
       
   // }    
 }

void modo9(void)
{
    debug("Programa 9. \n"); 
   // while(1){
       
   // }    
 }

void modo10(void)
{
    debug("Programa 10. \n"); 
   // while(1){
       
   // }    
 }

void modo11(void)
{
    debug("Programa 11. \n"); 
   // while(1){
       
   // }    
 }

void modo12(void)
{
    debug("Programa 12. \n"); 
   // while(1){
       
   // }    
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