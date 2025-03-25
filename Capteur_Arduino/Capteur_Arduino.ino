/*
==============================================
=============== Projet Capteur ===============
==============================================
Authors: Yoann LAI KOUN SING, Viet Hoang PHAM, Ly Hai HOANG
Last update: 17/03/2025
*/
/*  À piloter: 
Capteur graphène 
Potentiomètre digital: pour régler sensibilité de la mesure
OLED: pour afficher les différents menus (sensibilité et capteur choisi flexSensor ou Capteur graphite)
Encodeur rotatoire: pour choisir entre les différents menus (capteur Graphite, FlexSensor, Test)
                    (penser au debouncing)
Bluetooth: pour envoyer les valeurs lu du capteur choisi
Motor: pour bouger le capteur
Flex Sensor
*/



// Libraries 
#include <Adafruit_SSD1306.h>         // Library of the OLED screen
#include <Servo.h>                    // Library of the servo motor




// OLED Screen
#define nombreDePixelEnLargeur 128
#define nombreDePixelsEnHauteur 64
#define brocheResetOLED         -1
#define adresseI2CecranOLED     0x3C    // À définir
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);

// Rotary Encoder
#define encoder_CLK  2    // CLK output
#define encoder_DT 3      // DT Output
#define encoder_SW 4      // Switch connection 
volatile int encoderPos = 0 ;

// Graphite Sensor
#define GraphiteSensor A0

// Digital Potentiometer
#define Potentiometer_CS 10
#define Potentiometer_SCK 13
#define Potentiometer_SDI 11

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
  // Mesure rotary encoder value to choose menu


  // Mesure valeur en fonction du mode
  


  // Affiche menu en focntion du mode
  if 


  // Envoie les données avec le bluetooth
  









}
