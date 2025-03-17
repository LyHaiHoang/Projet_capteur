/*
==============================================
=============== Projet Capteur ===============
==============================================
Authors: Yoann LAI KOUN SING, Viet Hoang PHAM, Ly Hai HOANG
LLast update: 17/03/2025

*/




// Libraries 
#include <Adafruit_SSD1306.h>         // Library of the OLED screen
#include <Servo.h>                    // Library of the servo motor


//  À piloter: Capteur graphène avec Potentiomètre digital, OLED, Bluetooth, Motor
//             Flex Sensor, Encodeur rotatoire(penser au debouncing)

// OLED Screen
#define nombreDePixelEnLargeur 128
#define nombreDePixelsEnHauteur 64
#define brocheResetOLED         -1
#define adresseI2CecranOLED     0x3C    // À définir
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);

// Rotary Encoder
#define encoder0PinA  2
#define encoder0PinB  4

// Graphite Sensor


// Digital Potentiometer


// Flex Sensor


// Bluetooth
byte serialRX     // variable to receive data through RX
byte serialTX     // variable to transfert data through TX
volatile byte RX = 0;


// Motor
Servo My_Servo


// Debouncing




void setup() {
  Serial.begin (9600);
  Serial.println("----- Programme Capteur Start -----");

  // OLED Screen
  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)){
    while(1);
  }
  byte tailleDeCaractere=1;
  boolean bCouleurInverse = false;
  ecranOLED.clearDisplay();                   // Effacage de l'intensité du buffer
  ecranOLED.setTextSize(tailleDeCaractere);   // Taille des caractères (1:1)
  ecranOLED.setCursor(0,0);                   // Déplacement du curseur en position (0,0),dans l'angle supérieur gauche 
  // Choose pin mode
  
  // Rotary Encoder

  // Graphite Sensor

  // Digital Potentiometer

  // Flex Sensor

  // Bluetooth

  // Motor
  My_Servo.attach(9);       // attaches the servo on pin 9 to the servo object   




}

void loop() {
  // put your main code here, to run repeatedly:

}
