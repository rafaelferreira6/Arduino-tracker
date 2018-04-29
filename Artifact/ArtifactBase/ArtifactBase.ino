/*---Includes---*/
/*-GPS-*/
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

/*-Light-*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);


/*---Vars---*/
/*-GPS-*/
SoftwareSerial serial_connection(10, 11); //RX=pin 11, TX=pin 10
TinyGPSPlus gps;

/*-Sound- A0*/
int Sound_sensorPin = A0;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
double avgDB = 0;

/*-Air- A3*/
int Air_sensorPin = A3;
int Air_sensorValue = 0;
double avgAir = 0;
int i=0;

/*-Light-*/ 
int k = 0; 
double avgLight = 0; 

/*-Global-*/
long prevMillis=0;
long timer=5000; // Sound: 1000ms - 20 results (5000 -> 100) //


/*-Light Function (config)-*/
void configureSensor(void){
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
}

void setup() {
  Serial.begin(9600);
  
  /*-GPS-*/
  serial_connection.begin(9600);//This opens up communications to the GPS

  /*-Air-*/
  pinMode(Air_sensorPin, INPUT);

  /*-Light-*/ 
  if(!tsl.begin()){
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  configureSensor();
}

void loop() {
  unsigned long curMillis = millis();

  /*-Sound's Vars-*/
  unsigned int peakToPeak = 0;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  /*-Light's Vars/Event-*/ 
  sensors_event_t event;
  tsl.getEvent(&event);
  
  /*-GPS-*/
  while(serial_connection.available()){gps.encode(serial_connection.read());}
  
  /*-Sound-*/
  //Collect data for 50 mS
  while (millis() - curMillis < sampleWindow){
   sample = analogRead(Sound_sensorPin);
    if (sample < 1024){
      if (sample > signalMax){signalMax = sample;}
      else if (sample < signalMin){signalMin = sample;}
    }
   }
   
   peakToPeak = signalMax - signalMin;
   double volts = ((peakToPeak * 3.3) / 1024) * 0.707;
   double first = log10(volts/0.00631)*20;
   double second = first + 94 - 44 - 25;
   avgDB += second;
   //Serial.println(second);

   /*-Air-*/
   Air_sensorValue = analogRead(Air_sensorPin);
   avgAir+=Air_sensorValue;
   i++;
   
   /*-Light-*/ 
   if (event.light){
     avgLight+= event.light; 
     k++;
   }else{
    Serial.println("Sensor overload");
   }
   
   if(curMillis - prevMillis > timer && gps.satellites.value()>=1 && gps.location.lat() != 0){
    prevMillis = curMillis;
    /*-GPS-*/
    Serial.println("- - - - - - - - - - -");
    Serial.println("GPS");
    Serial.println("- - - - - - - - - - -");
    Serial.println("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);
    Serial.println("Altitude Meters:");
    Serial.println(gps.altitude.meters());
    Serial.println("Date:");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.println(gps.date.year());
    Serial.println("Time:");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.println(gps.time.minute());
    Serial.println("- - - - - - - - - - -");
    Serial.println("");
    /*-SOUND-*/ 
    avgDB = avgDB / ((timer/0.05)/1000);
    Serial.println("- - - - - - - -");
    Serial.print("MIC: ");
    Serial.println(avgDB);
    Serial.println("- - - - - - - -");
    Serial.println("");
    avgDB=0;
    /*-AIR-*/
    Serial.println("- - - - - - - -");
    Serial.print("AIR: ");
    Serial.println(avgAir / i);
    Serial.println("- - - - - - - -");
    Serial.println("");
    avgAir=0;
    i=0; 
    /*-LIGHT-*/ 
    Serial.println("- - - - - - - -");
    Serial.print("LIGHT: ");
    Serial.println(avgLight / k);
    Serial.println("- - - - - - - -");
    Serial.println("");
    avgLight=0;
    k=0; 
   }
   else if(curMillis - prevMillis > timer && gps.location.lat() == 0){
    Serial.println("- - - - - - - -");
    Serial.println("Syncing...");
    Serial.println("- - - - - - - -");
    Serial.println("");
   }
}
