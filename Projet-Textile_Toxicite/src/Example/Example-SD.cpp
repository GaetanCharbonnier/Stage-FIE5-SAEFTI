/*#include <Arduino.h> // Bibliothèque Arduino
#include <Wire.h> 	// Gestion de la liaison I2C
#include <SPI.h>	// Bibliothèque pour Slot Carte SD
#include <SD.h> 	// Bibliothèque pour Slot Carte SD

…..(...., …, …);  //Déclarer l'adresse I2C du capteur

File fichierSD;
#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

//Début déclaration détecteur de …..

unsigned int TotalPulse; // unsigned int , donnee comprise entre 0 et ….
unsigned int ….;
unsigned int ….;
unsigned int ….;
unsigned int ….;
unsigned int ….;

//Fin déclaration détecteur de …..

//Début déclaration détecteur de …..

unsigned int TotalPulse; // unsigned int , donnee comprise entre 0 et ….
unsigned int ….;
boolean …
int…
byte…
float…

//Fin déclaration détecteur de …..
void printnvram(uint8_t address) {
  Serial.print("Address 0x");
  Serial.print(address, HEX);
  Serial.print(" = 0x");
  Serial.println(RTC.readnvram(address), HEX);
}
//Conversion d'un Tableau de uint8_t en un Double Mot uint32_t
union ArrayToInteger {
  byte array[4];
  uint32_t integer;
};

void setup()
{
 // Initialiser une connexion série pour signaler les valeurs à l'hôte
Serial.begin(9600);
// Configurer les LED comme sorties
   pinMode(LedBleu, OUTPUT);
 // digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
   pinMode(LedVerte, OUTPUT);
//  digitalWrite(statusLCD, LOW);  // We have an active-low LED attached
   pinMode(LedRouge, OUTPUT);
     pinMode(CS_SD, OUTPUT);

  // Initialise la liaison I2C  
  Wire.begin();

 //Initialise la date et le jour au moment de la compilation
  // /!\ /!\ Les lignes qui suivent sert à définir la date et l'heure afin de régler le module,
  // pour les montages suivant il ne faut surtout PAS la mettre, sinon à chaque démarrage
  // le module se réinitialisera à la date et heure de compilation
DateTime dt = DateTime(__DATE__, __TIME__);
// RTC.adjust(dt);

//Pour la carte SD=====================
 //Initialisation de l'instance
 if(!SD.begin(10)) {//10 pour notre carte, peut etre different
 Serial.println(F("Initialisation impossible !"));
 TestSD = 0;
 return;
 }
 Serial.println(F("Initialisation OK"));
 TestSD=10;
//Fin carte SD==========================
//Test Parametrage Colonne Fichiers Carte SD
/*char datafileTest[13]; //tableau de 13 espaces pour le nom
 sprintf(datafileTest,"%02d%04d.csv",05,2019); // %d pour un int
 datafileTest[13]='\0';//à mettre pour fermer convenablement le fichier
 //Ouverture du fichier==========================
 	fichierSD = SD.open(datafileTest, FILE_WRITE);
 	//Test pour écriture
 	if(fichierSD) {
 	//Serial.println(F("Ecriture en cours"));
 	//Ecriture
 	fichierSD.println("Date;Heure;Conso_Totale;Conso_Mensuel;Conso_Jour;Pression_Amont;Pression_Aval;Compteur_Lumiere");
 	fichierSD.close();
 	}
}


 * Boucle Programme Principal
 

void loop()
{

DateTime now = RTC.now();
  //On nomme le fichier selon la date, donc toutes les donnees prises le meme jour dans un seul fichier==========
 char datafile[13]; //tableau de 13 espaces pour le nom
 int jourfile=now.day();
 int moisfile = now.month();
 int anneefile= now.year();
 sprintf(datafile,"%02d%04d.csv",moisfile,anneefile); // %d pour un int
 datafile[13]='\0';//à mettre pour fermer convenablement le fichier
 //Fin nommer fichier==================

 //Ouverture du fichier==========================
   fichierSD = SD.open(datafile, FILE_WRITE);
   
   //Test pour écriture
   if(fichierSD) {
   //Serial.println(F("Ecriture en cours"));
   //Ecriture
   NbEcritureSD = NbEcritureSD +1;
   fichierSD.print(jour);
   fichierSD.print(";");
   fichierSD.print(heure);
   fichierSD.print(";");
   fichierSD.print((TotalPulse*FacteurDebit)/1000.0);
   fichierSD.print(";");
   fichierSD.print((TotalPulseMensuel*FacteurDebit)/1000.0);
   fichierSD.print(";");
   fichierSD.print((TotalPulseJour*FacteurDebit)/1000.0);
   fichierSD.print(";");
   fichierSD.print(pressure_bar1);
   fichierSD.print(";");
   fichierSD.print(pressure_bar);
   fichierSD.print(";");
   fichierSD.print(CptTpsLumiere);
   fichierSD.print(";");
   fichierSD.print(MaxTemp);
   fichierSD.print(";");
   fichierSD.print(MinTemp);
   fichierSD.print(";");
   fichierSD.print(MaxHum);
   fichierSD.print(";");
   fichierSD.println(MinHum);
   
   
   fichierSD.close();
   MemJourSauvSD=jour1.toInt();
   }
   else {
	CptEchecSD = CptEchecSD + 1;
   }
   
   //Fermeture du fichier avec une ligne de plus============
  }

 //Allumer la LED Bleu si il y a une detection de debit d'eau
   if (flowRate > 0.1) //(photocellReading >= LumiereMini || etatShunt) && flowRate > 1.0 )
   {
   	digitalWrite(LedBleu, LOW);
   }
   else
   {
   	digitalWrite(LedBleu, HIGH);
   }
   
   // Gestion LED Verte et Rouge suivant propreté du filtre
   if (flowRate > 1.0 && (pressure_bar1 - pressure_bar < 0.5))
   {
   	digitalWrite(LedVerte, LOW);
   	digitalWrite(LedRouge, HIGH);
   }
   else if (flowRate > 1.0 && pressure_bar1 - pressure_bar >= 0.5)
   {
   	digitalWrite(LedVerte, HIGH);
   	digitalWrite(LedRouge, LOW);
   }  
   else if  (flowRate < 1.0 || photocellReading < LumiereMini)
   {
   	digitalWrite(LedVerte, HIGH);
   	digitalWrite(LedRouge, HIGH);
   }
}
*/