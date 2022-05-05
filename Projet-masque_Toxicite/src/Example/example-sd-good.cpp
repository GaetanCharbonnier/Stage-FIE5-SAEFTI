/*
//=============================================================================================================================================
//=============================================================================================================================================

Fichier : Projet-masque_toxicite

Description : Programme permettant de faire des mesures de toxicite, et de stoker ces informations sur une microSD dans un fichier au format CSV

Auteur : CHARBONNIER GAETAN

date de création : 02/05/2022
//=============================================================================================================================================
//=============================================================================================================================================
*/

/*
#include <Arduino.h>
#include <SoftwareSerial.h> //Creer une serial virtuel
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
#include <SPI.h> // Bibliothèque pour Slot Carte SD
#include <SD.h> // Bibliothèque pour Slot Carte SD

#define FILE_WRITE (O_READ | O_WRITE | O_CREAT | O_APPEND)
#define FILE_READ O_READ
#define Vc 4.95
#define R0 27.42

// Variables Carte SD
const int SDchipSelect = 4; // Module Carte SD Branché sur la PIN 4 pour le CS (Chip Select)
const char* filename = "MasqVal.csv";
File dataFile;

// Variables pour les capteurs 
GAS_GMXXX<TwoWire> gas;
unsigned int no2, c2h5ch, voc, co;

// Autres variables 
const long delaiIntervalleMesure = 2000; // intervalle d'enregistrement des mesures (en millis secondes)


//=========================
// Initialisation Programme
//=========================
void setup() {
  // Initialisation de la liaison série 
  Serial.begin(9600);
  Serial.println(F("Programme Projet Toxicite des fumees - ToxSdis"));
  Serial.println(F("=============================================="));
  Serial.println();
  gas.begin(Wire, 0x08);

//----------------------------------------------------------------------
// Verification : est-ce que la carte SD est accessible depuis l'arduino ?
//----------------------------------------------------------------------
 Serial.print("Initialisation de la SD card...");
 if (!SD.begin(SDchipSelect)) {
  Serial.println();
  Serial.println("Echec de l'initialisation du lecteur SD card Vérifiez:");
  Serial.println("* La bonne insertion de la carte");
  Serial.println("* Le bon cablâge du module SD");
  Serial.println("* que la vrariable du Pin 'cs' est correct ");
  Serial.println("Appuyé sur le bouton reset de l'aduino, pour redémarer le programme ");
  while (true);
  }
  Serial.println("Terminé !");
  Serial.println();  
  }
 

//====================
// Boucle Principale
//====================
void loop() {

//-------------------------------------------------
// Lecture des données : NO2, C2H5CH, VOC, CO, HCHO
//-------------------------------------------------
  //NO2
  no2 = gas.getGM102B();
  if (no2 > 999) no2 = 999;

  //C2H5CH
  c2h5ch = gas.getGM302B();
  if (c2h5ch > 999) c2h5ch = 999;

  //VOC
  voc = gas.getGM502B();
  if (voc > 999) voc = 999;

  //CO
  co = gas.getGM702B();
  if (co > 999) co = 999;
 
  //HCHO
  int sensorValue=analogRead(A0);
  double Rs=(1023.0/sensorValue)-1;
  double HCHOppm=pow(10.0,((log10(Rs/R0)-0.0827)/(-0.4807)));
    if (HCHOppm > 999) HCHOppm = 999;
  delay(2000);

  //--------------------------------------------------------------------------------------------------
  // Vérification : si aucune valeur n'est detecte par le microcontroleur, on wait 2s et on redemarre la fonction loop
  //--------------------------------------------------------------------------------------------------
  if (isnan(no2)||isnan(c2h5ch)||isnan(voc)||isnan(co)||isnan(HCHOppm)){
    Serial.println(F("Aucune valeur retournée par les capteurs"));
    delay(2000);
    return;
  }

  //--------------------------------------------------------
  // Affichage des valeurs sur le moniteur de l'IDE Arduino
  //--------------------------------------------------------
  Serial.print("NO2: ");Serial.print(no2);
  Serial.print(" ppm");Serial.print("  =  ");Serial.print(gas.calcVol(no2)); Serial.println("V");

  Serial.print("C2H5CH: ");Serial.print(c2h5ch);
  Serial.print(" ppm");Serial.print("  =  ");Serial.print(gas.calcVol(c2h5ch)); Serial.println("V");

  Serial.print("VOC: ");Serial.print(voc);
  Serial.print(" ppm");Serial.print("  =  ");Serial.print(gas.calcVol(voc)); Serial.println("V");

  Serial.print("CO: ");Serial.print(co);
  Serial.print(" ppm");Serial.print("  =  ");Serial.print(gas.calcVol(co)); Serial.println("V");

  Serial.print("HCHO: ");Serial.print(HCHOppm);Serial.println(" ppm"); 
  Serial.println("----------------------------------------------------------------");


//-----------------------------------
// ==> SD Card : enregistrement des données
//-----------------------------------
  
  dataFile = SD.open(filename, FILE_WRITE); // Ouverture du fichier => FILE_WRITE ->  ouvre le fichier en lecture et en écriture,
  if (dataFile) {  // Test pour écriture
    Serial.println(F("Ecriture en cours"));

    dataFile.print(no2);
    dataFile.print(";"); //délimiteur du fichier CSV
    dataFile.println(c2h5ch);
    dataFile.print(";");
    dataFile.println(voc);
    dataFile.print(";");
    dataFile.println(co);
    dataFile.print(";");
    dataFile.println(HCHOppm);

    dataFile.close(); 
    Serial.println(F("Enregistrement des données réussi sur la carte SD"));

  }
  else {
  Serial.println(F("Erreur lors de la tentative d'ouverture du fichier en écriture"));
  }
  Serial.println();
  delay(delaiIntervalleMesure);

}

*/