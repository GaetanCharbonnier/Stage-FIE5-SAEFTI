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

SoftwareSerial BTSerial(7, 6); // RX - TX  => BT-TX=6 BT-RX=7
#define SDA 4
#define SCL 5

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
  BTSerial.begin(9600);
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
  }
  // Fermeture du fichier avec une ligne de plus============

  String message; // message blt comportant l'information

  while (BTSerial.available())
  {
    Serial.println("reçu sur bluetooth");
    // Lecture du message envoyé par le BT
    message = BTSerial.readString();

    // Recuperation de l'etat initial pour définir la position des sliders
    if (message == "etat")
    {
      BTSerial.println("stalarm=" + String(stAlarm1));
      delay(100);
      BTSerial.println("stval=" + String(stval));
      delay(100);
      BTSerial.println("stval2=" + String(stval2));
      delay(100);
      BTSerial.println("stval3=" + String(stval3));
      delay(100);
      BTSerial.println("stval4=" + String(stval4));
      delay(100);
      BTSerial.println("sltemp=" + String(slAlarmVal));
      delay(100);
    }

    if (message == "stval=1")
    {
      stval = 1;
      Serial.println("A");
    }
    else if (message == "stval=0")
    {
      stval = 0;
      Serial.println("B");
    }
    else if (message == "stval2=1")
    {
      stval2 = 1;
      Serial.println("C");
    }
    else if (message == "stval2=0")
    {
      stval2 = 0;
      Serial.println("D");
    }
    else if (message == "stval3=1")
    {
      stval3 = 1;
      Serial.println("E");
    }
    else if (message == "stval3=0")
    {
      stval3 = 0;
      Serial.println("F");
    }
    else if (message == "stval4=1")
    {
      stval4 = 1;
      Serial.println("G");
    }
    else if (message == "stval4=0")
    {
      stval4 = 0;
      Serial.println("H");
    }
    else if (message == "stalarm=1")
    {
      stAlarm1 = 1;
      Serial.println("J");
    }
    else if (message == "stalarm1=0")
    {
      stAlarm1 = 0;
      Serial.println("K");
    }
    else
    {
      Serial.println("G");
      decoupeur(message);
    }

    Serial.println("#");
    Serial.println(message);
    Serial.println("#");

  }

if(stAlarm1 == 1){
    if(blalarm1 == 1){
      // envoie l'information alarme a l'application
      BTSerial.println("alarm=1" ); 
      Serial.println("envoie au Bt de alarm=1");
    }    
  

  // MutliGas Sensor - VCC 3V3

  if (stval == 1 && ((millis() - tempoMesure) > 5000)){
    getSensor();
    Serial.println("Envoie de la temperature au BT");
    BTSerial.println("stval=" + String(val1));
    delay(100);
    BTSerial.println("stval2=" + String(val2));
    delay(100);
    BTSerial.println("stval3=" + String(val3));
    delay(100);
    BTSerial.println("stval4=" + String(val4));
    delay(100);
    tempoMesure = millis();

    Serial.print("float temperature");
    Serial.println((float)val1);
    Serial.print("slalarmtemp");
    Serial.println(slAlarmVal);
    // on va comparer aussi la temperature a slAlarmTemp pour declencher l'alarme de l'arduino
    if ((float)stval > slAlarmVal)
    {
      Serial.println("Alarme arduino");
    }
  }
}
  while (Serial.available())
  {
    Serial.println("Recu sur serial");
    message = Serial.readString();    // Lecture du message envoyé par le serial usb
    BTSerial.println(message);   // Ecriture du message dans le BT
  } 
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

// Decouper les varaibles pour mettre plusieurs variables dans un seul message
void decoupeur(String inputString){

  char inputChar[inputString.length() + 1];
  inputString.toCharArray(inputChar, inputString.length() + 1);
  // lit toute les commandes separes par des &
  char *command = strtok(inputChar, "&");
  // boucle sur toutes les commandes
  while (command != 0)
  {
    // decoupe command en deux valeurs , separateur :
    char *valueCommand = strchr(command, '=');
    if (valueCommand != 0)
    {
      *valueCommand = 0;
      ++valueCommand;
      // aiguillage par rapport a la valeur de command
      if (String(command) == "slalarm")
      {
        slAlarmVal = String(valueCommand).toFloat();
      }
      else if (String(command) == "color")
      {
        // color = String(valueCommand) ;
      }
    }
    // Recherche une nouvelle commande separes pas un &
    command = strtok(0, "&");
  }
}

*/