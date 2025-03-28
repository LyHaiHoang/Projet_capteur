/*
==============================================
=============== Projet Capteur ===============
==============================================
Authors: Yoann LAI KOUN SING, Viet Hoang PHAM, Ly Hai HOANG
Last update: 17/03/2025
*/
/*  À piloter: 
- Capteur graphène 
- Potentiomètre digital: pour régler sensibilité de la mesure
- OLED: pour afficher les différents menus (sensibilité et capteur choisi flexSensor ou Capteur graphite)
- Encodeur rotatoire: pour choisir entre les différents menus (capteur Graphite, FlexSensor, Test)
                    (penser au debouncing)
- Bluetooth: pour envoyer les valeurs lu du capteur choisi
- Motor: pour bouger le capteur
- Flex Sensor
*/

//====================================================
//==================== Libraries =====================
//====================================================
#include <Adafruit_SSD1306.h>         // Library of the OLED screen
#include <Servo.h>                    // Library of the servo motor



//====================================================
//==================== Declaration ===================
//====================================================

// OLED Screen
#define nombreDePixelsEnLargeur 128
#define nombreDePixelsEnHauteur 64
#define brocheResetOLED         -1
#define adresseI2CecranOLED     0x3C    // À définir
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);
// Rotary Encoder
#define pinEncoder_CLK  2    // CLK output
#define pinEncoder_DT 3      // DT Output
#define pinEncoder_SW 4      // Switch connection 
volatile int encoderPos = 0 ;
// Graphite Sensor
#define GraphiteSensor A0
// Digital Potentiometer
#define pinPot_CS 10
#define pinPot_SCK 13
#define pinPot_SDI 11
// Flex Sensor
const int flexPin = A2 ;
// Bluetooth
#define pinBT_TXD 5
#define pinBT_RXD 6
byte serialRX     // variable to receive data through RX
byte serialTX     // variable to transfert data through TX
volatile byte RX = 0;
// Motor
#define pinnMoteur 9 ;



//====================================================
//====================== Setup =======================
//====================================================
void setup() {
  Serial.begin (9600);
  Serial.println("----- Programme Capteur Start -----");

  // OLED Screen
  SetOLED() ;

  // Rotary Encoder
  pinMode(pinEncoder_CLK, OUTPUT) ;
  digitalWrite(pinEncoder_CLK, HIGH);
  pinMode(pinEncoder_DT, INPUT) ;
  digitalWrite(pinEncoder_DT, HIGH);
  pinMode(pinEncoder_SW, INPUT) ;
  volatile int encoderPos = 0 ;
  volatile int encoderPosBefore = 0 ;
  attachInterrupt(0, doEncoder, RISING) ;

  // Graphite Sensor
  pinMode(,) ;
  pinMode(,) ;
  // Digital Potentiometer
  pinMode(,) ;
  pinMode(,) ;
  // Flex Sensor
  pinMode(flexPin, INPUT) ;
  // Bluetooth
  setupBluetoothConnection();
  // Motor
  My_Servo.attach(9);       // attaches the servo on pin 9 to the servo object   




}



//====================================================
//==================== Main Loop =====================
//====================================================
void loop() {
  // Mesure rotary encoder value to choose menu
  // refer to setup()

  // Mesure valeur en fonction du mode
  DisplayOLED() ;


  // Affiche menu en fonction du mode
  
  


  // Envoie les données avec le bluetooth
  

}



//====================================================
//==================== Main Loop =====================
//====================================================

void doEncoder() {
  if (digitalRead(pinEncoder_CLK)==HIGH && digitalRead(pinEncoder_DT)==HIGH) {
    encoderPos-- ;
  } 
  else if (digitalRead(pinEncoder_CLK)==HIGH && digitalRead(pinEncoder_DT)==LOW) {
    encoderPos++ ;
  }
}


void SetOLED() {
  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)){
    Serial.println("Initialisation OLED screen failed");
    while(1);
  }
  byte tailleDeCaractere = 1 ;
  boolean bCouleurInverse = false ;
  ecranOLED.clearDisplay();                   // Effacage de l'intensité du buffer
  ecranOLED.setTextSize(tailleDeCaractere);   // Taille des caractères (1:1)
  ecranOLED.setCursor(0,0);                   // Déplacement du curseur en position (0,0),dans l'angle supérieur gauche 
}

void 

void DisplayOLED(){
  if (encoderPos < encoderPos) {
    ecranOLED.setCursor(10,0) ;
    ecranOLED.print("Man Menu:") ;
    ecranOLED.setCursor(0,9) ;
    ecranOLED.print("> Fonction") ;
    ecranOLED.print("> Capteur")
    ecranOLED.display() ;
  } 
  else if (encoderPos > encoderPos) {

  }
  encoderPosBefore = encoderPos ;
  
}

