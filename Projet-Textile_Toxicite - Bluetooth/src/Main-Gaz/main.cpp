/*
#include <Arduino.h>
#include <SoftwareSerial.h> //Creer une serial virtuel
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
#include <SPI.h> // Bibliothèque pour Slot Carte SD
#include <SD.h>  // Bibliothèque pour Slot Carte SD

// Déclarer l'adresse I2C du capteur
int CS = 7;
File fichierSD;
#define FILE_WRITE (O_READ | O_WRITE | O_CREAT | O_APPEND)
#define FILE_READ O_READ

GAS_GMXXX<TwoWire> gas;

int stAlarm1 = 0;       // st - "state" Alarm initialisation
unsigned int stval = 0; 
unsigned int stval2 = 0;
unsigned int stval3 = 0;
unsigned int stval4 = 0;
float slAlarmVal = 400; // sl - "slider"
boolean blalarm1 = 0;

unsigned int val1 = 0;
unsigned int val2 = 0;
unsigned int val3 = 0;
unsigned int val4 = 0;

long unsigned tempoMesure = 0; // temps de ref. entre chaque mesure

void setup()
{
  // Wire.begin ();
  Serial.begin(9600);
  gas.begin(Wire, 0x08); // Essayer 0x55 ------ use the hardware I2C
  tempoMesure = 0;

  while (!Serial)
  {
    ; // wait for serial port to connect.
  }

  Serial.print("\nInitializing SD card...");
  pinMode(CS, OUTPUT);// SS PIN (10 or 4 on most Arduino boards)

  // Pour la carte SD
  // if (!card.init(SPI_HALF_SPEED, chipSelect)) {
  if (!SD.begin(CS)){ // Initialisation de la carte SD
    Serial.println(F("Initialisation impossible !"));
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
    Serial.println(F("Initialisation OK"));
  }

   //Ouverture du fichier==========================
    File dataFile = SD.open("MasqueVal.csv", FILE_WRITE);
    dataFile.println("Date;Heure;Conso_Totale;GM102B;GM302B;GM502B;GM702B");
}

// Boucle Programme Principal
void loop(){
  // make a string for assembling the data to log:
  String dataString = "";
  // Ouverture du fichier==========================
    File dataFile = SD.open("MasqueVal.csv", FILE_WRITE);
  // Test pour écriture
  if (dataFile)
  {
    // Serial.println(F("Ecriture en cours"));
    // Ecriture
    dataFile.print(val1);
    dataFile.print(";");
    dataFile.print(val2);
    dataFile.print(";");
    dataFile.print(val3);
    dataFile.print(";");
    dataFile.print(val4);

    dataFile.close();

    // print to the serial port too:
    Serial.println(dataString);
    Serial.print(val1); 
    Serial.print(';'); 
    Serial.println(val2);
    Serial.print(';'); 
    Serial.println(val3);
    Serial.print(';'); 
    Serial.println(val4);
  }
  else
  {
  Serial.println("error opening datalog.txt");
  delay(1000);
  }
  // Fermeture du fichier avec une ligne de plus============
}

//Recuperer les valeurs du capteur multigas
void getSensor(){

  val1 = 0;
  val2 = 0;
  val3 = 0;
  val4 = 0;

  // GM102B NO2 sensor
  val1 = gas.getGM102B();
  if (val1 > 999)
    val1 = 999;

  // GM302B C2H5CH sensor
  val2 = gas.getGM302B();
  if (val2 > 999)
    val2 = 999;

  // GM502B VOC sensor
  val3 = gas.getGM502B();
  if (val3 > 999)
    val3 = 999;

  // GM702B CO sensor
  val4 = gas.getGM702B();
  if (val4 > 999)
    val4 = 999;

  Serial.print("gas102B = ");
  Serial.println((int)val1);
  Serial.print(" ppm, ");
  Serial.print("gas302B = ");
  Serial.println((int)val2);
  Serial.print(" ppm, ");
  Serial.print("gas502B = ");
  Serial.println((int)val3);
  Serial.print(" ppm, ");
  Serial.print("gas702B = ");
  Serial.print((int)val4);
  Serial.print(" ppm ");
}
*/