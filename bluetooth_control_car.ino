//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "SoftwareSerial.h"
// #include <ESP32Servo.h>

SoftwareSerial myserial(7, 8);

int MOTOR_A1 = 3;   // MOTOR_A1 connected to digital pin 7
int MOTOR_A2 = 5;   // MOTOR_A2 connected to digital pin 6
int MOTOR_B1 = 6;   // MOTOR _B1 connected to digital pin 5
int MOTOR_B2 = 11;  // MOTOR_B2 connected to digital pin 4

// int RIGHT = 23;  // RIGHT sensor connected to analog pin A0
// int LEFT = 15;   // LEFT sensor connected to analog pin A1

// #define pwmpin 12
// #define MOTOR_A1 3
// #define MOTOR_A2 5

const int trigPin = 2;
const int echoPin = 4;
long duration;
int distance;

int buzzer = 10;
int light = 9;


char btdata;



void setup() {
  Serial.begin(9600);
  myserial.begin(9600);  //Bluetooth device name

  pinMode(buzzer, OUTPUT);
  pinMode(light, OUTPUT);

  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input

  // pinMode(pwmpin, OUTPUT);    // initialize MOTOR_A1 pin as an output
  pinMode(MOTOR_A1, OUTPUT);  // initialize MOTOR_A1 pin as an output
  pinMode(MOTOR_A2, OUTPUT);  // initialize MOTOR_A2 pin as an output
  pinMode(MOTOR_B1, OUTPUT);  // initialize MOTOR_B1 pin as an output
  pinMode(MOTOR_B2, OUTPUT);  // initialize MOTOR_B2 pin as an output


  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.println(distance);

  if (myserial.available()) {
    // BTdata = SerialBT.read();
    btdata = myserial.read();
    Serial.println(btdata);
  }

  if (distance >= 20) {

    if (btdata == "F") {

      // MOVE FORWARD  //
      //run right motors clockwise
      analogWrite(MOTOR_A1, 0);
      analogWrite(MOTOR_A2, 100);
      //run left motors clockwise
      analogWrite(MOTOR_B1, 100);
      analogWrite(MOTOR_B2, 0);
      Serial.println("FORWARD");
    }

    if (btdata == "B") {
      // MOVE BACKWARD  //
      //run right motors clockwise
      analogWrite(MOTOR_A1, 100);
      analogWrite(MOTOR_A2, 0);
      //run left motors anti-clockwise
      analogWrite(MOTOR_B1, 0);
      analogWrite(MOTOR_B2, 100);
      Serial.println("BACKWARD");
    }

    if (btdata == "R") {

      //MOVE-LEFT//
      //run right motors anti-clockwise
      analogWrite(MOTOR_A1, 150);
      analogWrite(MOTOR_A2, 0);
      //run left motors clockwise
      analogWrite(MOTOR_B1, 150);
      analogWrite(MOTOR_B2, 0);
      Serial.println("LEFT");
    }

    if (btdata == "L") {

      //MOVE RIGHT//
      //run right motors clockwise
      analogWrite(MOTOR_A1, 0);
      analogWrite(MOTOR_A2, 150);
      //run left motors anti-clockwise
      analogWrite(MOTOR_B1, 0);
      analogWrite(MOTOR_B2, 150);
      Serial.println("RIGHT");
    }

    if (btdata == "S") {

      //STOP//
      //stop right motors
      digitalWrite(MOTOR_A1, LOW);
      digitalWrite(MOTOR_A2, LOW);
      //stop left motors
      digitalWrite(MOTOR_B1, LOW);
      digitalWrite(MOTOR_B2, LOW);
    }


    // flag = 0;
  }

  if (distance < 20) {
    digitalWrite(MOTOR_A1, LOW);
    digitalWrite(MOTOR_A2, LOW);
    //stop left motors
    digitalWrite(MOTOR_B1, LOW);
    digitalWrite(MOTOR_B2, LOW);
    delay(500);
    analogWrite(MOTOR_A1, 100);
    analogWrite(MOTOR_A2, 0);
    //run left motors anti-clockwise
    analogWrite(MOTOR_B1, 0);
    analogWrite(MOTOR_B2, 100);
  }

  if (btdata == "M") {
    digitalWrite(light, LOW);
  }

  if (btdata == "m") {
    digitalWrite(light, HIGH);
  }

  if (btdata == "N") {
    digitalWrite(buzzer, HIGH);
  }

  if (btdata == "n") {
    digitalWrite(buzzer, LOW);
  }


  delay(20);
}
