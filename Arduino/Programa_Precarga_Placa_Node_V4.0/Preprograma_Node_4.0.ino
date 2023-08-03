#include "WiFi.h"

#include<AsyncTCP.h>

#include<ESPAsyncWebServer.h>

#include<AsyncElegantOTA.h>

#include<MRT_Friends_esp32_IRremote.h>

#include "MRT_esp32_Motor.h"

#include <PlayRtttl.hpp>


const unsigned int Umbral_IR_MCoche = 200;
const unsigned int Umbral_IR_Piano = 200;
const unsigned int Umbral_IR_Diana = 200;
const unsigned int Umbral_IR_Boxeador = 200;
const unsigned int Umbral_IR_Tren = 200;
const unsigned int Umbral_IR_Wally = 50;
const unsigned int Umbral_IR_Pato = 300;
unsigned int melodia = 1;
int Programa = 0;
float tiempo = 0;
unsigned int LecturaIRIzq = 0;
unsigned int LecturaIrDrcho = 0;
const char wifi_ssid[]="Logix5_AP";
const char wifi_pass[]="node1234";

AsyncWebServer server(80);

IRrecv irrecv1(27);
int remote_button;
int recommon_flag;


void serveinicio(AsyncWebServerRequest *request) {
request->send(200,"text/html",pinicio());
  String dir=request->arg("dir");
  Serial.println(dir);
  if (dir == "F") {
    Forward(255);
  }
  if (dir == "B") {
    Backward(255);
  }
  if (dir == "R") {
    TurnRight(255);
  }
  if (dir == "L") {
    TurnLeft(255);
  }
  if (dir == "S") {
    Stop();
  }

}

String pinicio(){
String cadena=(String) R"=====(
<!DOCTYPE HTML>
 <html>
<head><title>inicio</title></head>
<body>
  <h1  style="  text-align : center ; color : #000000 ; ">  Control Remoto de Coche por Wifi . Gesti&oacute;n de los motores</h1>

</body>
</html>
)=====";
 return cadena;
}

double random_int(int a,int b) {
  if (a > b) {
    int c = a;
    a = b;
    b = c;
  }
  return (double) random(a,b+1);
}

void Forward(unsigned int speed) {
  setDcMotor(MOTOR_L1,0,speed);
  setDcMotor(MOTOR_R1,0,speed);
}

void TurnRight(unsigned int speed) {
  setDcMotor(MOTOR_L1,0,speed);
  setDcMotor(MOTOR_R1,1,speed);
}

void Backward(unsigned int speed) {
  setDcMotor(MOTOR_L1,1,speed);
  setDcMotor(MOTOR_R1,1,speed);
}

void Stop() {
  setDcMotor(MOTOR_L1,0,0);
  setDcMotor(MOTOR_R1,0,0);
}

void TurnLeft(unsigned int speed) {
  setDcMotor(MOTOR_L1,1,speed);
  setDcMotor(MOTOR_R1,0,speed);
}

void programa1() {
  Serial.println("Programa 1 -- Movimiento motor -- Gimnasta");
  while (1 == 1) {
    // Con este valor va bien, si es verdad que con los dos portapilas directos va más deprisa
    setDcMotor(MOTOR_L1,0,225);
    delay(2*1000);
    setDcMotor(MOTOR_L1,0,0);
    delay(100);
    setDcMotor(MOTOR_L1,1,225);
    delay(2*1000);
    setDcMotor(MOTOR_L1,0,0);
    delay(100);
    // Con este valor las pilas si van justas no se moverá
    setDcMotor(MOTOR_L1,0,200);
    delay(2*1000);
    setDcMotor(MOTOR_L1,0,0);
    delay(100);
    setDcMotor(MOTOR_L1,1,200);
    delay(2*1000);
    setDcMotor(MOTOR_L1,0,0);
    delay(100);
  }
}

void programa2() {
  Serial.println("Programa 2 -- Mando");
  while (1 == 1) {
    remote_button = irrecv1.mrtRemoteLoop();
    if ((irrecv1.mrtRemoteStateCheck(remote_button,44))) {
      Forward(240);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,62))) {
      Backward(240);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,63))) {
      TurnLeft(240);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,61))) {
      TurnRight(240);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,53))) {
      Stop();
    }
  }
}

void programa3() {
  Serial.println("Programa 3 -- Tren");
  while (1 == 1) {
    LecturaIRIzq = analogRead(35);
    LecturaIrDrcho = analogRead(36);
    if (LecturaIRIzq < Umbral_IR_Tren & LecturaIrDrcho < Umbral_IR_Tren) {
      Forward(200);
    }
    if (LecturaIRIzq > Umbral_IR_Tren & LecturaIrDrcho < Umbral_IR_Tren) {
      TurnRight(200);
    }
    if (LecturaIRIzq < Umbral_IR_Tren & LecturaIrDrcho > Umbral_IR_Tren) {
      TurnLeft(200);
    }
    if (LecturaIRIzq > Umbral_IR_Tren & LecturaIrDrcho > Umbral_IR_Tren) {
      TurnRight(200);
    }
  }
}

void programa4() {
  Serial.println("Programa 4 -- Wally");
  Forward(200);
  while (1 == 1) {
    LecturaIRIzq = analogRead(35);
    LecturaIrDrcho = analogRead(36);
    if (LecturaIRIzq > Umbral_IR_Wally) {
      Stop();
      delay(50);
      Backward(200);
      delay(1*1000);
      TurnRight(200);
      delay(1*1000);
      Forward(200);
    }
    if (LecturaIrDrcho > Umbral_IR_Wally) {
      Stop();
      delay(50);
      Backward(200);
      delay(1*1000);
      TurnLeft(200);
      delay(1*1000);
      Forward(200);
    }
  }
}

void programa5() {
  Serial.println("Programa 5 -- Pato");
  while (1 == 1) {
    LecturaIRIzq = analogRead(35);
    LecturaIrDrcho = analogRead(36);
    if (LecturaIRIzq > Umbral_IR_Pato) {
      setDcMotor(MOTOR_R1,0,240);
    } else {
      setDcMotor(MOTOR_R1,0,0);
    }
    if (LecturaIrDrcho > Umbral_IR_Pato) {
      setDcMotor(MOTOR_L1,0,240);
    } else {
      setDcMotor(MOTOR_L1,0,0);
    }
  }
}

void programa7() {
  Serial.println("Programa 7 -- Peonza");
  while (1 == 1) {
    if ((!digitalRead(33))) {
      digitalWrite(23, HIGH);
      Forward(255);
    } else {
      digitalWrite(23, LOW);
      Stop();
    }
  }
}

void programa12() {
  Serial.println("Programa 12 -- Guitarra");
  while (1 == 1) {
    if ((!digitalRead(33)) & (!digitalRead(34))) {
      ledcWriteTone(4,493);
       delay(500);
    } else {
      if (analogRead(35) > Umbral_IR_Piano & analogRead(36) > Umbral_IR_Piano) {
        ledcWriteTone(4,440);
         delay(500);
      } else {
        if ((!digitalRead(33))) {
          ledcWriteTone(4,329);
           delay(500);
        }
        if ((!digitalRead(34))) {
          ledcWriteTone(4,349);
           delay(500);
        }
        if (analogRead(35) > 400) {
          ledcWriteTone(4,261);
           delay(500);
        }
        if (analogRead(36) > 400) {
          ledcWriteTone(4,293);
           delay(500);
        }
        if (analogRead(39) < 400) {
          ledcWriteTone(4,392);
           delay(500);
        }
        if (!digitalRead(0)) {
          playRtttlBlocking(32,(char*)StarWars);
        }
      }
    }
    ledcWriteTone(4,0);
  }
}

void programa6() {
  Serial.println("Programa 6 -- Sumo");
  while (1 == 1) {
    LecturaIRIzq = analogRead(35);
    LecturaIrDrcho = analogRead(36);
    if (LecturaIRIzq < Umbral_IR_Boxeador & LecturaIrDrcho < Umbral_IR_Boxeador) {
      Stop();
      delay(100);
      Backward(180);
      delay(500);
      TurnRight(180);
      delay(500);
    }
    if (LecturaIRIzq > Umbral_IR_Boxeador & LecturaIrDrcho < Umbral_IR_Boxeador) {
      Stop();
      delay(100);
      Backward(180);
      delay(500);
      TurnRight(180);
      delay(500);
    }
    if (LecturaIRIzq < Umbral_IR_Boxeador & LecturaIrDrcho > Umbral_IR_Boxeador) {
      Stop();
      delay(100);
      Backward(180);
      delay(500);
      TurnLeft(180);
      delay(500);
    }
    if (LecturaIRIzq > Umbral_IR_Boxeador & LecturaIrDrcho > Umbral_IR_Boxeador) {
      Forward(180);
    }
  }
}

void programa8() {
  Serial.println("Programa 8 -- Mando con llave infrarrojo");
  while (1 == 1) {
    remote_button = irrecv1.mrtRemoteLoop();
    if (analogRead(35) > Umbral_IR_MCoche) {
      if ((irrecv1.mrtRemoteStateCheck(remote_button,44))) {
        Forward(240);
      }
      if ((irrecv1.mrtRemoteStateCheck(remote_button,62))) {
        Backward(240);
      }
      if ((irrecv1.mrtRemoteStateCheck(remote_button,63))) {
        TurnLeft(240);
      }
      if ((irrecv1.mrtRemoteStateCheck(remote_button,61))) {
        TurnRight(240);
      }
      if ((irrecv1.mrtRemoteStateCheck(remote_button,53))) {
        Stop();
      }
    }
  }
}

void programa9() {
  Serial.println("Programa 9 --Diana");
  setDcMotor(MOTOR_L1,0,200);
  while (1 == 1) {
    if (analogRead(35) > Umbral_IR_Diana) {
      setDcMotor(MOTOR_L1,0,0);
      digitalWrite(23, HIGH);
      melodia = random_int(1, 6);
      switch (melodia) {
      case 1:
        playRtttlBlocking(32,(char*)Muppets);
        break;
       case 2:
        playRtttlBlocking(32,(char*)Indiana);
        break;
       case 3:
        playRtttlBlocking(32,(char*)A_Team);
        break;
       case 4:
        playRtttlBlocking(32,(char*)Looney);
        break;
       case 5:
        playRtttlBlocking(32,(char*)Gadget);
        break;
       default :
        playRtttlBlocking(32,(char*)_20thCenFox);
       }
      ledcWriteTone(4,0);
      digitalWrite(23, LOW);
      setDcMotor(MOTOR_L1,0,200);
    }
  }
}

void programa10() {
  Serial.println("Programa 10 -- Parpadeo Led");
  while (1 == 1) {
    digitalWrite(23, HIGH);
    digitalWrite(25, LOW);
    delay(1000);
    digitalWrite(23, LOW);
    digitalWrite(25, HIGH);
    delay(1000);
  }
}

void programa11() {
  Serial.println("Programa 11 -- Banco");
  while (1 == 1) {
    if (analogRead(39) < 400) {
      digitalWrite(23, HIGH);
      digitalWrite(25, HIGH);
      Forward(225);
    } else {
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
      Stop();
    }
  }
}


void setup() {
  Serial.begin(115200);

  Serial.begin(115200);
delay(2000);
WiFi.mode(WIFI_AP);
Serial.println("Conectando como modo punto de acceso");
while (!WiFi.softAP(wifi_ssid,wifi_pass)){
  Serial.print(".");
  delay(500);
  }
Serial.println("ESP MAC Address:  ");
Serial.println(WiFi.macAddress());
Serial.println();
Serial.print("Iniciado Access point:  ");
Serial.println(wifi_ssid);
Serial.print("with this IP address: ");
Serial.println(WiFi.softAPIP());

  server.on("/move",HTTP_GET,serveinicio);
  pinMode(0,INPUT_PULLUP);
  ledcSetup(4,5000,8);
ledcAttachPin(32,4);

    Programa = 0;
  tiempo = millis()/1000;
  Serial.println("Arrancando programa");
  AsyncElegantOTA.begin(&server); //Start ElegantOTA
  server.begin();
  irrecv1.enableIRIn();
  recommon_flag = 1;

  DcMotor_init();
  analogReadResolution(10);

  pinMode(33,INPUT);
  pinMode(23, OUTPUT);
  pinMode(34,INPUT);
  pinMode(25, OUTPUT);
}

void loop() {
    if (!digitalRead(0)) {
      Programa = Programa + 1;
      Serial.print("Boton pulsado. Programa:  ");
      Serial.println(Programa);
      switch (Programa) {
      case 1:
        ledcWriteTone(4,261);
         delay(500);
        break;
       case 2:
        ledcWriteTone(4,293);
         delay(500);
        break;
       case 3:
        ledcWriteTone(4,329);
         delay(500);
        break;
       case 4:
        ledcWriteTone(4,349);
         delay(500);
        break;
       case 5:
        ledcWriteTone(4,392);
         delay(500);
        break;
       case 6:
        ledcWriteTone(4,440);
         delay(500);
        break;
       case 7:
        ledcWriteTone(4,493);
         delay(500);
        break;
       case 8:
        ledcWriteTone(4,523 );
         delay(500);
        break;
       case 9:
        ledcWriteTone(4, 587 );
         delay(500);
        break;
       case 10:
        ledcWriteTone(4, 659 );
         delay(500);
        break;
       case 11:
        ledcWriteTone(4, 698 );
         delay(500);
        break;
       case 12:
        ledcWriteTone(4, 784 );
         delay(500);
        break;
       default :
        Programa = 0;
       }
      ledcWriteTone(4,0);
      tiempo = millis()/1000;
    }
    if (millis()/1000 > tiempo + 3) {
      switch (Programa) {
      case 1:
        programa1();
        break;
       case 2:
        programa2();
        break;
       case 3:
        programa3();
        break;
       case 4:
        programa4();
        break;
       case 5:
        programa5();
        break;
       case 6:
        programa6();
        break;
       case 7:
        programa7();
        break;
       case 8:
        programa8();
        break;
       case 9:
        programa9();
        break;
       case 10:
        programa10();
        break;
       case 11:
        programa11();
        break;
       case 12:
        programa12();
        break;
       default :
        Serial.println("No se pulso ninguna tecla");
       }
      tiempo = millis()/1000;
    }

}
