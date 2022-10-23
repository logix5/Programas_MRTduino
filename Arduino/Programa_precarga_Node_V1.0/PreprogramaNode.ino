#include "WiFi.h"

#include<AsyncTCP.h>

#include<ESPAsyncWebServer.h>

#include<AsyncElegantOTA.h>

#include<MRT_Friends_esp32_IRremote.h>

#include "MRT_esp32_Motor.h"


int Programa = 0;
float tiempo = 0;
const char wifi_ssid[]="Otto_Wifi";
const char wifi_pass[]="otto1234";

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

void TurnLeft(unsigned int speed) {
  setDcMotor(MOTOR_L1,1,speed);
  setDcMotor(MOTOR_R1,0,speed);
}

void Stop() {
  setDcMotor(MOTOR_L1,0,0);
  setDcMotor(MOTOR_R1,0,0);
}

void programa2() {
  Serial.println("Programa 2 -- Mando");
  while (1 == 1) {
    remote_button = irrecv1.mrtRemoteLoop();
    if ((irrecv1.mrtRemoteStateCheck(remote_button,44))) {
      Forward(255);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,62))) {
      Backward(255);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,63))) {
      TurnLeft(255);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,61))) {
      TurnRight(255);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,53))) {
      Stop();
    }
  }
}

void programa1() {
  Serial.println("Programa 1 -- Movimiento motores -- Gimnasta");
  while (1 == 1) {
    setDcMotor(MOTOR_L1,0,255);
    setDcMotor(MOTOR_R1,0,255);
    delay(1*1000);
    setDcMotor(MOTOR_L1,1,255);
    setDcMotor(MOTOR_R1,1,255);
    delay(1*1000);
    setDcMotor(MOTOR_L1,0,200);
    setDcMotor(MOTOR_R1,0,200);
    delay(1*1000);
    setDcMotor(MOTOR_L1,1,200);
    setDcMotor(MOTOR_R1,1,200);
    delay(1*1000);
  }
}

void programa3() {
  Serial.println("Programa 3 -- Tren");
  while (1 == 1) {
    if (!(digitalRead(35) & !digitalRead(36))) {
      Forward(255);
    }
    if (digitalRead(35) & !digitalRead(36)) {
      TurnRight(255);
    }
    if (!digitalRead(35) & digitalRead(36)) {
      TurnLeft(255);
    }
    if (digitalRead(35) & digitalRead(36)) {
      TurnRight(255);
    }
  }
}

void programa4() {
  Serial.println("Programa 4 -- Wally");
  while (1 == 1) {
    if (!(digitalRead(35) & !digitalRead(36))) {
      Forward(200);
    }
    if (digitalRead(35) & !digitalRead(36)) {
      Backward(200);
      delay(1*1000);
      TurnRight(200);
      delay(500);
    }
    if (!digitalRead(35) & digitalRead(36)) {
      Backward(200);
      delay(1*1000);
      TurnLeft(200);
      delay(500);
    }
    if (digitalRead(35) & digitalRead(36)) {
      Backward(200);
      delay(1*1000);
      TurnRight(200);
      delay(500);
    }
  }
}

void programa5() {
  Serial.println("Programa 5 -- Pato");
  while (1 == 1) {
    if (!(digitalRead(35) & !digitalRead(36))) {
      digitalWrite(23, LOW);
      digitalWrite(25, HIGH);
      Stop();
    }
    if (digitalRead(35) & !digitalRead(36)) {
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);
      TurnLeft(255);
    }
    if (!digitalRead(35) & digitalRead(36)) {
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);
      TurnRight(255);
    }
    if (digitalRead(35) & digitalRead(36)) {
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);
      Forward(255);
    }
  }
}

void programa8() {
  Serial.println("Programa 8 -- Mando con llave infrarrojo");
  while (1 == 1) {
    if (digitalRead(35)) {
      remote_button = irrecv1.mrtRemoteLoop();
      if ((irrecv1.mrtRemoteStateCheck(remote_button,44))) {
        Forward(255);
      }
      if ((irrecv1.mrtRemoteStateCheck(remote_button,62))) {
        Backward(255);
      }
      if ((irrecv1.mrtRemoteStateCheck(remote_button,63))) {
        TurnLeft(255);
      }
      if ((irrecv1.mrtRemoteStateCheck(remote_button,61))) {
        TurnRight(255);
      }
      if ((irrecv1.mrtRemoteStateCheck(remote_button,53))) {
        Stop();
      }
    }
  }
}

void programa7() {
  Serial.println("Programa 7 -- Peonza");
  while (1 == 1) {
    if (digitalRead(33)) {
      digitalWrite(23, HIGH);
      Forward(255);
    } else {
      digitalWrite(23, LOW);
      Stop();
    }
  }
}

void programa9() {
  Serial.println("Programa 9 --Diana");
  while (1 == 1) {
    remote_button = irrecv1.mrtRemoteLoop();
    if ((irrecv1.mrtRemoteStateCheck(remote_button,63))) {
      setDcMotor(MOTOR_L1,0,250);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,61))) {
      setDcMotor(MOTOR_L1,1,250);
    }
    if ((irrecv1.mrtRemoteStateCheck(remote_button,53))) {
      setDcMotor(MOTOR_L1,0,0);
    }
    if (digitalRead(35)) {
      digitalWrite(23, HIGH);
      ledcWriteTone(4,493);
       delay(125);
      ledcWriteTone(4,261);
       delay(125);
      ledcWriteTone(4,440);
       delay(125);
      ledcWriteTone(4,293);
       delay(125);
      ledcWriteTone(4,0);
      delay(5*1000);
      digitalWrite(23, LOW);
    }
  }
}

void programa6() {
  Serial.println("Programa 6 -- Boxeador");
  while (1 == 1) {
    if (!(digitalRead(35) & !digitalRead(36))) {
      Backward(255);
      delay(1*1000);
      TurnRight(255);
      delay(500);
    }
    if (digitalRead(35) & !digitalRead(36)) {
      Backward(255);
      delay(1*1000);
      TurnRight(255);
      delay(500);
    }
    if (!digitalRead(35) & digitalRead(36)) {
      Backward(255);
      delay(1*1000);
      TurnLeft(255);
      delay(500);
    }
    if (digitalRead(35) & digitalRead(36)) {
      Forward(255);
    }
  }
}

void programa10() {
  Serial.println("Programa 10 -- Parpadeo Led");
  while (1 == 1) {
    digitalWrite(23, HIGH);
    digitalWrite(25, LOW);
    delay(1*1000);
    digitalWrite(23, LOW);
    digitalWrite(25, HIGH);
    delay(1*1000);
  }
}

void programa11() {
  Serial.println("Programa 11 -- Banco");
  while (1 == 1) {
    if (!digitalRead(39)) {
      digitalWrite(23, HIGH);
      digitalWrite(25, HIGH);
      Forward(255);
    } else {
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
      Stop();
    }
  }
}

void programa12() {
  Serial.println("Programa 12 -- Piano");
  while (1 == 1) {
    if (digitalRead(33) & digitalRead(34)) {
      ledcWriteTone(4,261);
       delay(500);
    } else {
      if (digitalRead(35) & digitalRead(36)) {
        ledcWriteTone(4,293);
         delay(500);
      } else {
        if (digitalRead(33)) {
          ledcWriteTone(4,329);
           delay(500);
        }
        if (digitalRead(34)) {
          ledcWriteTone(4,349);
           delay(500);
        }
        if (digitalRead(35)) {
          ledcWriteTone(4,392);
           delay(500);
        }
        if (digitalRead(36)) {
          ledcWriteTone(4,440);
           delay(500);
        }
        if (!digitalRead(39)) {
          ledcWriteTone(4,493);
           delay(500);
        }
      }
    }
    ledcWriteTone(4,0);
  }
}


void setup() {
  Serial.begin(115200);

  server.on("/move",HTTP_GET,serveinicio);
  pinMode(0,INPUT_PULLUP);
  ledcSetup(4,5000,8);
ledcAttachPin(32,4);

    Programa = 0;
  tiempo = millis()/1000;
  Serial.println("Arrancando programa");
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
  AsyncElegantOTA.begin(&server); //Start ElegantOTA
  server.begin();
  irrecv1.enableIRIn();
  recommon_flag = 1;

  DcMotor_init();
  pinMode(35,INPUT);
  pinMode(36,INPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(33,INPUT);
  pinMode(39,INPUT);
  pinMode(34,INPUT);
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
