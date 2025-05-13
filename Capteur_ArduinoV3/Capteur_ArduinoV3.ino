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
#include <SoftwareSerial.h>    // Library for HC-05 bluetooth module
#include <string.h>

//====================================================
//==================== Declaration ===================
//====================================================

// _____ OLED Screen _____
#define nombreDePixelsEnLargeur 128
#define nombreDePixelsEnHauteur 64
#define brocheResetOLED -1
#define adresseI2CecranOLED 0x3C  // À définir
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);
// _____ Rotary Encoder _____
#define pinEncoder_CLK 2  // CLK output
#define pinEncoder_DT 3   // DT Output
#define pinEncoder_SW 4   // Switch connection
volatile int encoderPos = 0;
volatile int encoderPosBefore = 0;
volatile int encoderButton = 0;
volatile int encoderButtonBefore = 0;
volatile int MenuPos = -1;
volatile int MenuPosBefore = -1;
int buttonState;
int lastButtonState = HIGH;
long lastDebounceTime = 0;
long debounceDelay = 150;
// _____ Digital Potentiometer _____
// #define pinPot_CS 10      //pin 10 to control Digital Potentiometer
const byte pinPot_CS = 10;
#define pinPot_SCK 13     //
#define pinPot_SDI 11
const int  maxPositions = 256;
const long rAB = 52700;
const byte rWiper = 125; 
const byte pot0 = 0x11;
const byte pot0Shutdown = 0x21;
volatile float R_pot = 0 ;
// _____ Flex Sensor _____
const int pinFlexSensor = A2;                 // Pin connected to voltage divider output
const float VCC = 5.0;                  // Voltage at Ardunio 5V line
const float R_DIV = 39000.0;            // Resistor used to create a voltage divider
const float flatResistance = 35994.36;   // Resistance when flat (460.0)
const float bendResistance = 100000.0;    // Resistance at 90 deg bending (1000.0)
// _____ Graphite Sensor _____
const int pinGraphiteSensor = A0;
volatile float R_graphite = 0 ;
const float R1 = 100000;      // Resistance in [ohm]
const float R3 = 100000;      // Resistance in [ohm]
const float R5 = 10000;       // Resistance in [ohm]
const float R6 = 1000;        // Resistance in [ohm]
const float C1 = 0.0000001;   // Capa in [F]
const float C2 = 0.0000001;   // Capa in [F]
const float C4 = 0.000001;   // Capa in [F]
// _____ Bluetooth _____
#define pinBT_TXD 5
#define pinBT_RXD 6
// SoftwareSerial MyBT(pinBT_RXD, pinBT_TXD) ;
volatile char *DataReceived = 'z';
volatile float DataToSend = 0.0 ;
// _____ Motor _____
Servo My_Servo ;                        // Create an object My_servo to communicate with the Servo-motor
#define pinMoteur 9;
// _____ Other Parameters _____
#define baudrate 9600



//====================================================
//====================== Setup =======================
//====================================================
void setup() {
  Serial.begin(baudrate);
  Serial.println("----- Programme Capteur Start -----");
  // --- Rotary Encoder ---
  pinMode(pinEncoder_CLK, INPUT);
  digitalWrite(pinEncoder_CLK, HIGH);
  pinMode(pinEncoder_DT, INPUT);
  digitalWrite(pinEncoder_DT, HIGH);
  pinMode(pinEncoder_SW, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinEncoder_CLK), doEncoder, RISING);
  // --- Bluetooth ---
  //InitBluetooth();
  // attachInterrupt(digitalPinToInterrupt(pinBT_RXD), ReceiveDataBluetooth, RISING);
  // --- Digital Potentiometer ---
  Set_DigitalPotentiometer();
  setPotWiper(pot0, 128);
  // _____ Flex Sensor _____
  pinMode(pinFlexSensor, INPUT);
  // _____ Graphite Sensor _____
  pinMode(pinGraphiteSensor, INPUT);
  // --- OLED Screen ---
  Set_OLED();

}



//====================================================
//==================== Main Loop =====================
//====================================================
void loop() {
  doEncoderButton();

  DisplayOLED();

  //Sensor_Mesurement(MenuPosBefore);

  // SendDataBluetooth(DataToSend);


}

//====================================================
//==================== Functions =====================
//====================================================

//==================== Function for oled Screen ====================
void Set_OLED() {
  if (!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)) {
    Serial.println("Initialisation OLED screen NO");
  }
  ecranOLED.clearDisplay();         // Effacage de l'intégralité du buffer
  ecranOLED.setTextSize(2);         // Taille des caractères (1:1)
  ecranOLED.setCursor(0, 0);        // Déplacement du curseur en position (0,0),dans l'angle supérieur gauche
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  ecranOLED.println("Main Menu:") ;
  ecranOLED.println(">Fonction") ;
  ecranOLED.println(">Capteur") ;
  ecranOLED.display();
}
void InitOLED(){
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(2);
  ecranOLED.setCursor(0, 0);
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
}
// OLED_CouleurInverse(bool Inverser): Si vrai alors inverse la couleur: texte en noir en fond en blanc
void OLED_CouleurInverse(bool Inverser) {
  if (Inverser == true) {
    ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);       // (Couleur du texte, Couleur du fond)
  }
  else {
    ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  }
}
  // 1er indice indique le niveau du menu, 2nd indice indique le choix
void OLED_Menu0_0(int Val) {
  InitOLED();
  ecranOLED.println("Main Menu:");
  switch (Val){
    case 0 :
      OLED_CouleurInverse(true) ;
      ecranOLED.println(">Fonction") ;
      OLED_CouleurInverse(false) ;
      ecranOLED.println(">Capteur") ;
      MenuPos = 0;
      break;
    case 1 :
      ecranOLED.println(">Fonction") ;
      OLED_CouleurInverse(true) ;
      ecranOLED.println(">Capteur") ;
      OLED_CouleurInverse(false) ;
      MenuPos = 1;
      break;
    default :
      ecranOLED.println(">Fonction") ;
      ecranOLED.println(">Capteur") ;
      MenuPos = -1;
      break;
  }
  ecranOLED.display();
}
// Menu de Niveau 1, choix 0 du Niveau 0.
void OLED_Menu1_0(int Val) {
  InitOLED();
  ecranOLED.println("Fonction:");
  switch (Val){
    case 0 :
      OLED_CouleurInverse(true) ;
      ecranOLED.println(">Fonction1") ;
      OLED_CouleurInverse(false) ;
      ecranOLED.println(">Fonction2") ;
      ecranOLED.println("<<Exit") ;
      MenuPos = 100;
      break;
    case 1 :
      ecranOLED.println(">Fonction1") ;
      OLED_CouleurInverse(true) ;
      ecranOLED.println(">Fonction2") ;
      OLED_CouleurInverse(false) ;
      ecranOLED.println("<<Exit") ;
      MenuPos = 101;
      break;
    case 2 :
      ecranOLED.println(">Fonction1") ;
      ecranOLED.println(">Fonction2") ;
      OLED_CouleurInverse(true) ;
      ecranOLED.println("<<Exit") ;
      OLED_CouleurInverse(false) ;
      MenuPos = 102;
      break;
    default :
      ecranOLED.println(">Fonction1") ;
      ecranOLED.println(">Fonction2") ;
      ecranOLED.println("<<Exit") ;
  }
  ecranOLED.display();
}
// Menu de Niveau 1, choix 1 du Niveau 0.
void OLED_Menu1_1(int Val) {
  InitOLED();
  ecranOLED.println("Capteur:");
  switch (Val){
    case 0 :
      OLED_CouleurInverse(true) ;
      ecranOLED.println(">Capteur1") ;
      OLED_CouleurInverse(false) ;
      ecranOLED.println(">Capteur2") ;
      ecranOLED.println("<<Exit") ;
      MenuPos = 110;
      break;
    case 1 :
      ecranOLED.println(">Capteur1") ;
      OLED_CouleurInverse(true) ;
      ecranOLED.println(">Capteur2") ;
      OLED_CouleurInverse(false) ;
      ecranOLED.println("<<Exit") ;
      MenuPos = 111;
      break;
    case 2 :
      ecranOLED.println(">Capteur1") ;
      ecranOLED.println(">Capteur2") ;
      OLED_CouleurInverse(true) ;
      ecranOLED.println("<<Exit") ;
      OLED_CouleurInverse(false) ;
      MenuPos = 112;
      break;
    default :
      ecranOLED.println(">Capteur1") ;
      ecranOLED.println(">Capteur2") ;
      ecranOLED.println("<<Exit") ;
      break;
  }
  ecranOLED.display();
}
void ExitMenu(){
  Serial.println("Exit");
  encoderButton = 0 ;
  encoderButtonBefore = encoderButton;
  encoderPos = 0 ;
  MenuPos = -1 ;
  MenuPosBefore = -1;
}
// DisplayOLED(): Fonction d'affichage de l'écran OLED 
void DisplayOLED() {


  if ( (encoderPosBefore != encoderPos) || (encoderButtonBefore != encoderButton) ) {
    if (encoderButtonBefore != encoderButton) {
      MenuPosBefore = MenuPos ;
      encoderButtonBefore = encoderButton;
    }

    switch (encoderButton) {
      case 0 :
        OLED_Menu0_0(abs(encoderPos % 2));     // encoder modulo nb de choix - 1
        break;
      case 1 :
        if (MenuPosBefore == 0) {               // Menu Fonction
          OLED_Menu1_0(abs(encoderPos % 3));
        }
        else if (MenuPosBefore == 1) {          // Menu Capteur
          OLED_Menu1_1(abs(encoderPos % 3));
        }
        break;
      case 2 :
        switch (MenuPosBefore) {
          case 100 :                            // Fonction 1
            InitOLED();
            OLED_CouleurInverse(true) ;
            ecranOLED.println(">Fonction1") ;
            OLED_CouleurInverse(false) ;
            ecranOLED.display();
            MenuPosBefore = 100 ;
            break;
          case 101 :                            // Fonction 2
            InitOLED();
            OLED_CouleurInverse(true) ;
            Serial.println("Fonction 2");
            OLED_CouleurInverse(false) ;
            ecranOLED.display();
            MenuPosBefore = 101 ;
            break;
          case 102 :
            ExitMenu();
            break;
          case 110 :                             // Capteur1: Flex Sensor
            InitOLED();
            OLED_CouleurInverse(true) ;
            ecranOLED.println("FlexSensor") ;
            OLED_CouleurInverse(false) ;
            ecranOLED.display();
            MenuPosBefore = 110 ;
            // SendDataBluetooth_Instruction("Flex");
            break;
          case 111 :                             // Capteur2: Graphite Sensor
            InitOLED();
            OLED_CouleurInverse(true) ;
            ecranOLED.println("Graphite") ;
            OLED_CouleurInverse(false) ;
            ecranOLED.display();
            MenuPosBefore = 111 ;
            // SendDataBluetooth_Instruction("Graphite");
            break;
          case 112 :
            ExitMenu();
            break;
        }
        break;
      case 3:
        break;
      default:
        InitOLED();
        ecranOLED.println("Main Menu:") ;
        ecranOLED.println(">Fonction") ;
        ecranOLED.println(">Capteur") ;
        ecranOLED.display();
        encoderButton = 0 ;
        encoderButtonBefore = encoderButton;
        encoderPos = 0;
        MenuPos = -1 ;
        MenuPosBefore = -1;
    }
    encoderPosBefore = encoderPos;
  }
}

//==================== Function for Rotary encoder ====================
void doEncoder() {
  if (digitalRead(pinEncoder_CLK) == HIGH && digitalRead(pinEncoder_DT) == HIGH) {
    encoderPos-- ;
  }
  else if (digitalRead(pinEncoder_CLK) == HIGH && digitalRead(pinEncoder_DT) == LOW) {
    encoderPos++ ;
  }
  Serial.print("encoderPos=");
  Serial.print(encoderPos);
  Serial.print(" ; encoderButtonBefore=");
  Serial.print(encoderButtonBefore);
  Serial.print(" ; encoderButton=");
  Serial.print(encoderButton);
  Serial.print(" ; MenuPos=");
  Serial.println(MenuPos);
}
void doEncoderButton() {
  int valeur = digitalRead(pinEncoder_SW) ;
  //Serial.println(valeur);
  if (valeur != lastButtonState){
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime)> debounceDelay){
    if ( (valeur == LOW) && (valeur != buttonState) ){
      encoderButton++ ;
    }
    buttonState = valeur ;
  }
  lastButtonState = valeur ;
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

//==================== Function for Sensors ====================
        //========== flex Sensor ==========
float Flex_Mesure(){
  //Calculation of the flex sensor's resistance
  int ADC_flex = analogRead(pinFlexSensor);
  float V_flex = (ADC_flex * VCC) / 1023.0;
  float R_flex = R_DIV * ( (VCC / V_flex) - 1.0);
  long angle  = map(R_flex, flatResistance, bendResistance, 0, 90);
  Serial.print("R_flex = ");
  Serial.println(R_flex);
  return R_flex ;
}
        //========== Graphite Sensor ==========
float Graphite_Mesure(){
  int mesure = analogRead(pinGraphiteSensor);
  float V_ADC = mesure * VCC / 1023.0 ;
  float R_graph = (1+R3/R_pot)*R1*(VCC/V_ADC)-(R1+R5) ;
  Serial.print("R_graph = ");
  Serial.println(R_graph);
  return R_graph;
}
        //========== Capteur Global Function ==========
void Sensor_Mesurement(int PositionMenu){
  if (PositionMenu == 110){
    DataToSend = Flex_Mesure();
  }
  else if (PositionMenu == 111){
    DataToSend = Graphite_Mesure();
  }
}
//==================== Digital Potentiometer ====================
void Set_DigitalPotentiometer(){
  pinMode(pinPot_CS, OUTPUT);
  digitalWrite(pinPot_CS, LOW);
  SPI.begin();
}
void setPotWiper(int addr, int pos){
  pos = constrain(pos, 0, 255);            // limit wiper setting to range of 0 to 255
  digitalWrite(pinPot_CS, LOW);                // select chip
  SPI.transfer(addr);                      // configure target pot with wiper position
  SPI.transfer(pos);
  digitalWrite(pinPot_CS, HIGH);               // de-select chip

  // print pot resistance between wiper and B terminal
  R_pot = ((rAB * pos) / maxPositions ) + rWiper ;
}


//==================== Function for Bluetooth ====================
// void InitBluetooth(){
//   pinMode(pinBT_RXD, INPUT);
//   pinMode(pinBT_TXD, OUTPUT);
//   MyBT.begin(baudrate);
// }
// void ReceiveDataBluetooth(){
//   while (MyBT.available()) {
//     DataReceived = MyBT.read();
//   }
// }
// void SendDataBluetooth(float data){
//   MyBT.println(data);
// }
// void SendDataBluetooth_Instruction(char *message){
//   MyBT.println(message);
// }



