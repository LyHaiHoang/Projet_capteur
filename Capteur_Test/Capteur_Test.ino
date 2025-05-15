#include <SPI.h>               // Library for SPI to control Digital Potentiometer
#include <SoftwareSerial.h>    // Library for HC-05 bluetooth module
#include <stdlib.h>

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
long debounceDelay = 180;
volatile int ChoixCapteur = -1;              // Choix de capteur entre FlexSenosr(110) et Graphite Sensor (111)
// _____ Digital Potentiometer _____
// #define pinPot_CS 10      //pin 10 to control Digital Potentiometer
const byte pinPot_CS = 10;
#define pinPot_SCK 13
#define pinPot_SDI 11
const int  maxPositions = 256;
const long rAB = 52700;
const byte rWiper = 125; 
const byte pot0 = 0x11;
const byte pot0Shutdown = 0x21;
volatile float R_pot = 0 ;
// _____ Flex Sensor _____
#define pinFlexSensor A2            // Pin connected to voltage divider output
const float VCC = 5.0;                   // Voltage at Ardunio 5V line
const float R_DIV = 1000;                // Resistor [ohm] used to create a voltage divider
const float flatResistance = 35994.36;   // Resistance when flat
const float bendResistance = 120000.0;   // Resistance at 90 deg bending (80000)
// _____ Graphite Sensor _____
#define pinGraphiteSensor A0
volatile float R_graphite = 0 ;
const float R1 = 100000;      // Resistance in [ohm]
const float R3 = 100000;      // Resistance in [ohm]
const float R5 = 10000;       // Resistance in [ohm]
const float R6 = 1000;        // Resistance in [ohm]
const float C1 = 0.0000001;   // Capa in [F]
const float C2 = 0.0000001;   // Capa in [F]
const float C4 = 0.000001;   // Capa in [F]

volatile float DataToSend = 0.0 ;

#define baudrate 9600


void setup(){
  Serial.begin(baudrate);
  Serial.println("----- Programme Capteur Start -----");

  // --- Rotary Encoder ---
  pinMode(pinEncoder_CLK, INPUT);
  digitalWrite(pinEncoder_CLK, HIGH);
  pinMode(pinEncoder_DT, INPUT);
  digitalWrite(pinEncoder_DT, HIGH);
  pinMode(pinEncoder_SW, INPUT);
  // --- Digital Potentiometer ---
  Set_DigitalPotentiometer();
  setPotWiper(pot0, 128);
  // _____ Flex Sensor _____
  pinMode(pinFlexSensor, INPUT);
  digitalWrite(pinFlexSensor, LOW);
  // _____ Graphite Sensor _____
  pinMode(pinGraphiteSensor, INPUT);

  Serial.println("Fin Initialisation");
}

void loop(){

  // DataToSend = Flex_Mesure();
  DataToSend = Graphite_Mesure();
  // Serial.print("DataToSend = ");
  // Serial.println(DataToSend);
  delay(1000);
  
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
//==================== Function for Sensors ====================
        //========== flex Sensor ==========
float Flex_Mesure(){
  //Calculation of the flex sensor's resistance
  int ADC_flex = analogRead(pinFlexSensor);
  float V_flex = (ADC_flex * VCC) / 1023.0;
  float R_flex = R_DIV * ( V_flex / (VCC-V_flex));
  long angle  = map(R_flex, flatResistance, bendResistance, 0, 90);
  // Serial.print("R_flex = ");
  // Serial.println(R_flex);
  return R_flex ;
}
        //========== Graphite Sensor ==========
float Graphite_Mesure(){
  //Calculation of the Graphite sensor's resistance
  int mesure = analogRead(pinGraphiteSensor);
  float V_ADC = mesure * VCC / 1023.0 ;
  float R_graph = (1+R3/R_pot)*R1*(VCC/V_ADC)-(R1+R5) ;
  Serial.print("R_graph = ");
  Serial.println(R_graph);
  return R_graph;
}
//==================== Digital Potentiometer ====================
void Set_DigitalPotentiometer(){
  pinMode(pinPot_CS, OUTPUT);
  digitalWrite(pinPot_CS, HIGH);
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
  Serial.print("Resistance Pot: ");
  Serial.print(R_pot);
  Serial.println(" ; ");
}




