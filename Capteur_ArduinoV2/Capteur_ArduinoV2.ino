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
volatile int encoderPosBefore = 0;
volatile int encoderButton = 0;
volatile int encoderButtonBefore = 0;
volatile int MenuPos = -1;
int buttonState;
int lastButtonState = HIGH;
long lastDebounceTime = 0;
long debounceDelay = 200;

#define baudrate 9600

char TEST[6] = ">TOTO";

//====================================================
//====================== Setup =======================
//====================================================
void setup() {
  Serial.begin(baudrate);
  Serial.println("----- Programme Capteur Start -----");

  // OLED Screen
  SetUpOLED();

  // Rotary Encoder
  pinMode(pinEncoder_CLK, INPUT);
  digitalWrite(pinEncoder_CLK, HIGH);
  pinMode(pinEncoder_DT, INPUT);
  digitalWrite(pinEncoder_DT, HIGH);
  pinMode(pinEncoder_SW, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinEncoder_CLK), doEncoder, RISING);

  OLED_CouleurInverse(true) ;
  ecranOLED.println(TEST) ;
  OLED_CouleurInverse(false) ;
  ecranOLED.println(TEST) ;
  ecranOLED.display();

}



//====================================================
//==================== Main Loop =====================
//====================================================
void loop() {
  doEncoderButton();
  DisplayOLED();
}



//====================================================
//==================== Functions =====================
//====================================================

// Function for oled Screen
void SetUpOLED() {
  if (!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)) {
    Serial.println("Initialisation OLED screen OK");
  }
  ecranOLED.clearDisplay();         // Effacage de l'intégralité du buffer
  ecranOLED.setTextSize(2);         // Taille des caractères (1:1)
  ecranOLED.setCursor(0, 0);        // Déplacement du curseur en position (0,0),dans l'angle supérieur gauche
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  // ecranOLED.println("Main Menu:") ;
  // ecranOLED.println(">Fonction") ;
  // ecranOLED.println(">Capteur") ;
  ecranOLED.display();
}

void InitOLED(){
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(2);
  ecranOLED.setCursor(0, 0);
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

bool encoderButtonChanged(){
  bool Resultat = false;
  if (encoderButton != encoderButtonBefore) {
    Resultat = true;
  }
  else{
    Resultat = false;
  }
  return Resultat;
}

//OLEDAffichageChoixMenu(): Affiche du text en gérant la sélection
// TabNiveau = {Niveau du Menu actuel, choix n du niveau n-1}
void OLEDAffichageChoixMenu(char Texte, int TabNiveau[2], int Indice, int Valeur){
  if (Indice == Valeur) {
    OLED_CouleurInverse(true) ;
    ecranOLED.println(Texte) ;
    OLED_CouleurInverse(false) ;
    MenuPos = 100*TabNiveau[0] + 10*TabNiveau[1] + 1*Indice ;   // centaine: niveau du menu  ;  dizaine: le choix dans le menu précédent  ;  unité: indique le choix dans menu actuel
    //encoderButtonBefore = encoderButton;
    //encoderPos = 0;

  }
  else {
    ecranOLED.println(Texte) ;
  }
}

  // 1er indice indique le niveau du menu, 2nd indice indique le choix
void OLED_Menu0_0(int Val) {
  int Tab0_0[2] = {0, 0} ;
  char Titre[9+1] = "Main Menu";
  char Fonction[9+1] = ">Fonction" ;
  char Capteur[8+1] = ">Capteur" ;
  InitOLED();
  ecranOLED.println(Titre);
  OLEDAffichageChoixMenu(Fonction, Tab0_0, 0, Val);
  OLEDAffichageChoixMenu(Capteur, Tab0_0, 1, Val);
  ecranOLED.display();
}

// Menu de Niveau 1, choix 0 du Niveau 0.
void OLED_Menu1_0(int Val) {
  int Tab1_0[2] = {1, 0} ;
  char Titre[10+1] = ">Fonction:";
  char Choix1[10+1] = ">Fonction1" ;
  char Choix2[10+1] = ">Fonction2" ;
  char Choix3[6+1] = "<Exit" ;
  InitOLED();
  ecranOLED.println(Titre);
  OLEDAffichageChoixMenu(Choix1, Tab1_0, 0, Val);
  OLEDAffichageChoixMenu(Choix2, Tab1_0, 1, Val);
  OLEDAffichageChoixMenu(Choix3, Tab1_0, 2, Val);
  ecranOLED.display();
}

// Menu de Niveau 1, choix 1 du Niveau 0.
void OLED_Menu1_1(int Val) {
  int Tab1_1[2] = {1, 1} ;
  char Titre[9+1] = ">Capteur:";
  char Choix1[9+1] = ">Capteur1" ;
  char Choix2[9+1] = ">Capteur2" ;
  char Choix3[6+1] = "<Exit" ;
  InitOLED();
  ecranOLED.println(Titre);
  OLEDAffichageChoixMenu(Choix1, Tab1_1, 0, Val);
  OLEDAffichageChoixMenu(Choix2, Tab1_1, 1, Val);
  OLEDAffichageChoixMenu(Choix3, Tab1_1, 2, Val);
  ecranOLED.display();
}

// DisplayOLED(): Fonction d'affichage de l'écran OLED 
void DisplayOLED() {
  if (encoderPosBefore != encoderPos) {
    switch (encoderButton) {
      case 0 :
        OLED_Menu0_0(encoderPos % 2);     // encoder modulo nb de choix - 1
        break;
      case 1 :
        if (MenuPos == 0) {
          OLED_Menu1_0(encoderPos % 3);
        }
        else if (MenuPos == 1) {
          OLED_Menu1_1(encoderPos % 3);
        }
        break;
      case 2 :
        if (MenuPos == 100) {
          //Serial.println("Fonction 1");
        }
        else if (MenuPos == 101) {
          //Serial.println("Fonction 2");
        }
        else if (MenuPos == 102){
          encoderButton = 0 ;
          encoderButtonBefore = encoderButton;
        }

        else if (MenuPos == 110){
          //Serial.println("Capteur 1");
        }
        else if (MenuPos == 111){
          //Serial.println("Capteur 2");
        }
        else if (MenuPos == 112){
          encoderButton = 0 ;
          encoderButtonBefore = encoderButton;
        }
        break;
      default:
        ecranOLED.setCursor(0, 0);
        ecranOLED.println("Main Menu:") ;
        ecranOLED.println(">Fonction") ;
        ecranOLED.println(">Capteur") ;
        ecranOLED.display();
        encoderButton = 0 ;
        encoderButtonBefore = encoderButton;
        break;
    }

    encoderPosBefore = encoderPos;
  }
}


// Function for Rotary encoder
void doEncoder() {
  if (digitalRead(pinEncoder_CLK) == HIGH && digitalRead(pinEncoder_DT) == HIGH) {
    encoderPos-- ;
  }
  else if (digitalRead(pinEncoder_CLK) == HIGH && digitalRead(pinEncoder_DT) == LOW) {
    encoderPos++ ;
  }
  Serial.print("encoderPos=");
  Serial.print(encoderPos);
  Serial.print(" ; encoderButton=");
  Serial.print(encoderButton);
  Serial.print(" ; MenuPos=");
  Serial.println(MenuPos);
  //DisplayOLED();
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