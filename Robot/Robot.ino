#include <NewPing.h>
#include <AFMotor.h>

AF_DCMotor motor1(1, 0);
AF_DCMotor motor2(2, 0);

#define trigPin A0
#define echoPin A1

String segundos = "";

void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Joda de motor!");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
void moverDerecha() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}
void moverIzquierda() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}
void avanzar() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
void retroceder() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}
void detener() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
void printDistancia() {
  long duracion, distancia ;

  digitalWrite(trigPin, LOW);   // Nos aseguramos de que el trigger está desactivado
  delayMicroseconds(2);     // Para estar seguros de que el trigger esta LOW
  digitalWrite(trigPin, HIGH);  // Activamos el pulso de salida
  delayMicroseconds(10);    // Esperamos 10µs. El pulso sigue active este tiempo
  digitalWrite(trigPin, LOW); // Cortamos el pulso y a esperar el echo

  duracion = pulseIn(echoPin, HIGH) ;
  distancia = duracion / 2 / 29.1  ;

  Serial.println(String(distancia) + " cm.");
}
int getDistancia() {
  long duracion, distancia ;

  digitalWrite(trigPin, LOW);   // Nos aseguramos de que el trigger está desactivado
  delayMicroseconds(2);     // Para estar seguros de que el trigger esta LOW
  digitalWrite(trigPin, HIGH);  // Activamos el pulso de salida
  delayMicroseconds(10);    // Esperamos 10µs. El pulso sigue active este tiempo
  digitalWrite(trigPin, LOW); // Cortamos el pulso y a esperar el echo

  duracion = pulseIn(echoPin, HIGH) ;
  distancia = duracion / 2 / 29.1  ;

  return (int)distancia;
}
int getSegundos(String accion) {
  segundos = "";
  for (int i = 0; i < accion.length(); i++) {
    if (accion.charAt(i) > 47 && accion.charAt(i) < 58) {
      segundos += accion.charAt(i);
    }
  }
  return segundos.toInt() * 1000;
}
boolean tieneDistancia(String accion) {
  for (int i = 0; i < accion.length(); i++) {
    if (accion.charAt(i) > 47 && accion.charAt(i) < 58) {
      return true;
    }
  }
  return false;
}
String getAccion(String accion) {
  String acc = "";
  for (int i = 0; i < accion.length(); i++) {
    if (accion.charAt(i) != ' ') {
      acc += accion.charAt(i);
    }
    else {
      return acc;
    }
  }
}
void loop()
{
  if (Serial.available()) {
    String accion = Serial.readStringUntil('\n');
    int seg = getSegundos(accion);
    accion = getAccion(accion);

    if (accion.equals("avanzar")) {
      avanzar();
      if (seg == 0) {
        delay(1000);
      }
      else {
        delay(seg);
      }
    }
    else if (accion.equals("atras")) {
      retroceder();
      if (seg == 0) {
        delay(1000);
      }
      else {
        delay(seg);
      }
    }
    if (accion.equals("izquierda")) {
      moverIzquierda();
      if (seg == 0) {
        delay(1000);
      }
      else {
        delay(seg);
      }
    }
    if (accion.equals("derecha")) {
      moverDerecha();
      if (seg == 0) {
        delay(1000);
      }
      else {
        delay(seg);
      }
    }
    else if (accion.equals("distancia")) {
      printDistancia();
    }
    detener();
  }
}
