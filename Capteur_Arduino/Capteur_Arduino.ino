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
#include <Adafruit_SSD1306.h>  // Library of the OLED screen
#include <Servo.h>             // Library of the servo motor
#include <SPI.h>               // Library for SPI to control Digital Potentiometer


//====================================================
//==================== Declaration ===================
//====================================================

// OLED Screen
#define nombreDePixelsEnLargeur 128
#define nombreDePixelsEnHauteur 64
#define brocheResetOLED -1
#define adresseI2CecranOLED 0x3C  // À définir
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);
// Rotary Encoder
#define pinEncoder_CLK 2  // CLK output
#define pinEncoder_DT 3   // DT Output
#define pinEncoder_SW 4   // Switch connection
volatile int encoderPos = 0;
// Graphite Sensor
#define pinGraphiteSensor A0
// Digital Potentiometer
#define pinPot_CS 10      //pin 10 to control Digital Potentiometer
#define pinPot_SCK 13     //
#define pinPot_SDI 11
#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001
// Flex Sensor
const int flexPin = A2;
// Bluetooth
#define pinBT_TXD 5
#define pinBT_RXD 6
byte serialRX;  // variable to receive data through RX
byte serialTX;  // variable to transfert data through TX
volatile byte RX = 0;
// Motor
#define pinnMoteur 9;



//====================================================
//====================== Setup =======================
//====================================================
void setup() {
  Serial.begin(9600);
  Serial.println("----- Programme Capteur Start -----");

  // OLED Screen
  SetOLED();

  // Rotary Encoder
  pinMode(pinEncoder_CLK, OUTPUT);
  digitalWrite(pinEncoder_CLK, HIGH);
  pinMode(pinEncoder_DT, INPUT);
  digitalWrite(pinEncoder_DT, HIGH);
  pinMode(pinEncoder_SW, INPUT);
  volatile int encoderPos = 0;
  volatile int encoderPosBefore = 0;
  attachInterrupt(0, doEncoder, RISING);

  // Graphite Sensor
  pinMode(pinGraphiteSensor, INPUT);
  // Digital Potentiometer
  pinMode(pinPot_CS, OUTPUT);
  digitalWrite(pinPot_CS, HIGH) ;   //SPI chip disabled
  SPIWrite(MCP_WRITE, i, ssMCPin);                          // A DETERMINER !!!!!!
    //pinMode(pinPot_SCK, );
    //pinMode(pinPot_SDI, ) ;
  // Flex Sensor
  pinMode(flexPin, INPUT);
  // Bluetooth
  setupBluetoothConnection();
  // Motor
  My_Servo.attach(9);  // attaches the servo on pin 9 to the servo object
}



//====================================================
//==================== Main Loop =====================
//====================================================
void loop() {
  // Mesure rotary encoder value to choose menu
  // refer to setup()

  // Mesure valeur en fonction du mode
  ecranOLED.print("Main Menu:");
  ecranOLED.print(">> Fonction");
  ecranOLED.print(">> Capteur")
  ecranOLED.display();


  // Affiche menu en fonction du mode




  // Envoie les données avec le bluetooth
}



//====================================================
//==================== Main Loop =====================
//====================================================


// Function for oled Screen
void SetOLED() {
  if (!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)) {
    Serial.println("Initialisation OLED screen failed");
    while (1)
      ;
  }
  byte tailleDeCaractere = 1;
  boolean bCouleurInverse = false;
  ecranOLED.clearDisplay();                  // Effacage de l'intensité du buffer
  ecranOLED.setTextSize(2);  // Taille des caractères (1:1)
  ecranOLED.setCursor(0, 0);                 // Déplacement du curseur en position (0,0),dans l'angle supérieur gauche
}

void DisplayOLED() {
  if (encoderPos < encoderPos) {
    ecranOLED.print("Main Menu:");
    ecranOLED.print(">> Fonction");
    ecranOLED.print(">> Capteur")
    ecranOLED.display();
  } else if (encoderPos > encoderPos) {
  }
  encoderPosBefore = encoderPos;
}


// Function for Digital potentiometer
void doEncoder() {
  if (digitalRead(pinEncoder_CLK) == HIGH && digitalRead(pinEncoder_DT) == HIGH) {
    encoderPos--;
  } else if (digitalRead(pinEncoder_CLK) == HIGH && digitalRead(pinEncoder_DT) == LOW) {
    encoderPos++;
  }
}

void SPIWrite(uint8_t cmd, uint8_t data, uint8_t ssPin) // SPI write the command and data to the MCP IC connected to the ssPin
{
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); //https://www.arduino.cc/en/Reference/SPISettings
  
  digitalWrite(ssPin, LOW); // SS pin low to select chip
  
  SPI.transfer(cmd);        // Send command code
  SPI.transfer(data);       // Send associated value
  
  digitalWrite(ssPin, HIGH);// SS pin high to de-select chip
  SPI.endTransaction();
}