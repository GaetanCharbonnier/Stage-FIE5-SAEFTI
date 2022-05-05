/*
#include <SimpleDHT.h>
#include <SoftwareSerial.h> // va creer un serial virtuel


SoftwareSerial BTSerial(10, 11); // RX | TX  = > BT-TX=10 BT-RX=11

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 5;
SimpleDHT11 dht11(pinDHT11);


int stAlarm = 0;
int stTemp = 0;
float slAlarmTemp = 35;
boolean blAlarm = 0;


byte temperature = 0;
byte humidity = 0;

long unsigned tempoMesure = 0;



void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); 
  tempoMesure = 0;
}

void loop() {

String message;

 while (BTSerial.available()){
  Serial.println("Recu sur bluetooth");
      // Lecture du message envoyÃ© par le BT
      // Read message send by BT
      message = BTSerial.readString();
      // Ecriture du message dans le serial usb
      // write in serial usb
      
      // recuperation de l'etat initial pour definir la position des sliders
      if(message=="etat"){

        BTSerial.println("stalarm=" + String(stAlarm));
        delay(100);
        BTSerial.println("sttemp=" + String(stTemp));  
        delay(100);
        BTSerial.println("sltemp=" + String(slAlarmTemp));  
 
      }
 
      if(message=="sttemp=1"){
        stTemp=1;
        Serial.println("A");
      }
      else if(message=="sttemp=0"){
        stTemp=0;
        Serial.println("B");
      }
      else if(message=="stalarm=1"){
        stAlarm=1;
        Serial.println("C");
      }
      else if(message=="stalarm=0"){
        stAlarm=0;
        Serial.println("D");
      }      
      else if(message=="led"){
        digitalWrite(PIN_LED,HIGH);
        Serial.println("E");
      }
      else if(message=="noled"){
        digitalWrite(PIN_LED,LOW);
        Serial.println("F");
      }
      else{
        Serial.println("G");
        decoupeur(message);
      }
      
      Serial.println("#");
      Serial.println(message);
      Serial.println("#");
    }


 if(stAlarm == 1){
    if(blAlarm == 1){
      // envoie l'information alarme a l'application
      BTSerial.println("alarm=1" ); 
      Serial.println("envoie au Bt de alarm=1");
    }    
  }

//Temperature

  if(stTemp ==1 && ((millis() - tempoMesure) > 5000)){
    getTemperature();
    Serial.println("Envoie de la temperature au BT");
    BTSerial.println("temp=" + String(temperature) ); 
    delay(100);
    BTSerial.println("hum=" + String(humidity) );  
    delay(100);
    tempoMesure = millis();

  Serial.print("float temperature");
  Serial.println((float)temperature);
  Serial.print("slalarmtemp");
  Serial.println(slAlarmTemp);
    // on va comparer aussi la temperature a slAlarmTemp pour declencher l'alarme de l'arduino
    if( (float)temperature > slAlarmTemp ){
      Serial.println("Alarme arduino");
    }
    
  }

 


  while (Serial.available()){
    Serial.println("Recu sur serial");
      // Lecture du message envoyÃ© par le serial usb
      // Read message send by serial usb
      message = Serial.readString();
      // Ecriture du message dans le BT
      // write in BT 
      BTSerial.println(message);
    }
  // start working...
  //Serial.println("=================================");
  //Serial.println(analogRead(PIN_PIR));
  //Serial.println(digitalRead(PIN_PIR2));
  
  

  
  
}


void getTemperature(){

   temperature = 0;
   humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

}

void decoupeur(String inputString){

      char inputChar[inputString.length()+1] ;
      inputString.toCharArray(inputChar,inputString.length()+1);
 
        // lit toute les commandes separes par des &
        // Read each command pair 
        char* command = strtok(inputChar, "&");
        // boucle sur toutes les commandes
        while (command != 0)
        {
            // decoupe command en deux valeurs , separateur :
            // Split the command in two values
            char* valueCommand = strchr(command, '=');
            if (valueCommand != 0)
            {
                *valueCommand = 0;
                ++valueCommand;         
                // aiguillage par rapport a la valeur de command 
                  if(String(command) == "slalarm"){
                    slAlarmTemp = String(valueCommand).toFloat();
                    
                  }else if(String(command) == "color"){
                    
                    //color = String(valueCommand) ;
                    
                  }
            }
            // Recherche une nouvelle commande separes pas un &
            // Find the next command in input string
            command = strtok(0, "&");
        }
}
*/
