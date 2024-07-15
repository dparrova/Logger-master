

 /* 
Created in 20-may-2023 for Arduino Nano Boards
Modified by DiegoCh 
For some Arduino Nano board use 
File->Preferences menu, click on the little icon to the right of the Additional Boards Manager URLs: and add this line after any that are already present (or as the first line if you’ve never added any before):
https://raw.githubusercontent.com/dbuezas/lgt8fx/master/package_lgt8fx_index.json
Tools->Board: Boards Manager… window type LGT8fx in the filter/search box, and you should see LGT8Fx Boards.
*/

// CONNECTIONS:
// DS1302 CLK/SCLK --> 3
// DS1302 DAT/IO --> 2
// DS1302 RST/CE --> 4
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>
#include <MAX6675.h>


#include <SPI.h> //librerias para SD
#include <SD.h>

#define DHTTYPE DHT11
#define DHTPIN 5    

#define ssr_pin 8
#define CS_PIN 10
#define CS_PIN_SD 9 
#define PIN_BUZZER 6
  
File myFile;
File myFileDate;

char fileName[] = "Datos.csv";
char fileNameDate[] = "fecha.txt";
char fileConf[]= "conf.cfg";
char texto[]="";

char Fecha;
float h;
float t;
float temperatura;

ThreeWire myWire(2,3,4); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
DHT dht(DHTPIN, DHTTYPE);
MAX6675 tcouple(CS_PIN);

void setup () 
{
    Serial.begin(115200);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.println(__TIME__);

    

    Rtc.Begin();
    dht.begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

    //Tarjeta MicroSD 

   if (SD.begin(CS_PIN_SD))
    {
    Serial.println("SD card is present & ready");
    
    if (SD.exists(fileName)) //Comprobar si archivos Datos Existe
    {
      Serial.println("Archivo Datos existe");
    }
    else{
        myFile = SD.open(fileName,FILE_WRITE);
        if(myFile){
        myFile.println("Dia,Hora,Humedad,Temperatura1,Temperatura2,DeltaTemperatura");
        myFile.close();
         }
        }      
    } 
    
    else
    {
    Serial.println("SD card missing or failure");
    buzzer("Error");
    }
}

void loop () 
{
    
    RtcDateTime now = Rtc.GetDateTime();
    float h = dht.readHumidity()+4 ;
    float t = dht.readTemperature()-6 ; //Ambiente
    float temperatura   = tcouple.readTempC()-4; //Secador
    delay(1000);
    float DetalT = temperatura - t;

    String datos = printDateTime(now)+"," +String(h) + "," + String( t )+ "," + String( temperatura)+ "," + String(DetalT);
    Serial.println(datos);
   
    writeToFile(datos);
    delay(58000); // 60 segundos
    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

   
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

String printDateTime(const RtcDateTime& dt)
{
    char datestring[20];
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u,%02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
   return datestring;
}

void writeToFile(String data)
{
  if(SD.exists(fileName)){
  myFile = SD.open(fileName, FILE_WRITE);
  if (myFile) // it opened OK
    {
    myFile.println(data);
    myFile.close(); 
    buzzer("Done");
    }
  else {
    Serial.println("Error opening file");
    buzzer("Error");
    }
  }
  else{
     buzzer("Error");
    }
}



void buzzer(String tipo)
{
  if(tipo == "Done"){
  tone(PIN_BUZZER,880);
  delay(500);
  noTone(PIN_BUZZER);
  }
  else{
    Serial.println("Error");
    while(1){ 
   //   tone(PIN_BUZZER,880);
   //   delay(200);
   //   noTone(PIN_BUZZER); 
   //   delay(100);  
   //   tone(PIN_BUZZER,880);
   //   delay(200);
   //   noTone(PIN_BUZZER);
   //   delay(300);
      }
    }
}
