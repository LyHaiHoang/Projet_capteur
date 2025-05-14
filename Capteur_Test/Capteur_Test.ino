#include <SPI.h>


// _____ Flex Sensor _____
const int pinFlexSensor = A2;                 // Pin connected to voltage divider output
const float VCC = 5.0;                  // Voltage at Ardunio 5V line
const float R_DIV = 1000.0;            // Resistor used to create a voltage divider
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
volatile float DataToSend = 0.0 ;
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

#define baudrate 9600


void setup(){
  Serial.begin(baudrate);
  // --- Digital Potentiometer ---
  Set_DigitalPotentiometer();
  setPotWiper(pot0, 128);

  // _____ Flex Sensor _____
  pinMode(pinFlexSensor, INPUT);
  // _____ Graphite Sensor _____
  pinMode(pinGraphiteSensor, INPUT);

}

void loop(){

  // DataToSend = Flex_Mesure();
  DataToSend = Graphite_Mesure();
  Serial.print("DataToSend = ");
  Serial.println(DataToSend);
  delay(1000);
  
}


//==================== Function for Sensors ====================
        //========== flex Sensor ==========
float Flex_Mesure(){
  //Calculation of the flex sensor's resistance
  int ADC_flex = analogRead(pinFlexSensor);
  float V_flex = (ADC_flex * VCC) / 1023.0;
  float R_flex = R_DIV * ( V_flex / (VCC-V_flex));
  long angle  = map(R_flex, flatResistance, bendResistance, 0, 90);
  Serial.print("R_flex = ");
  Serial.println(R_flex);
  Serial.print(" ; ");
  return R_flex ;
}
        //========== Graphite Sensor ==========
float Graphite_Mesure(){
  int mesure = analogRead(pinGraphiteSensor);
  float V_ADC = mesure * VCC / 1023.0 ;
  float R_graph = (1+R3/R_pot)*R1*(VCC/V_ADC)-(R1+R5) ;
  Serial.print("R_graph = ");
  Serial.print(R_graph);
  Serial.print(" ; ");
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
  Serial.print("R_pot= ");
  Serial.println(R_pot);
}



