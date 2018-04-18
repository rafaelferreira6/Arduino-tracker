/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
long timer = 5000; // 1000ms — 20 results (...)
long prevMillis=0;
double avgDB = 0;
 
void setup() 
{
   Serial.begin(9600);
}
 
 
void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample;
         }
         else if (sample < signalMin)
         {
            signalMin = sample; 
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = ((peakToPeak * 3.3) / 1024) * 0.707;  // convert to RMS voltage
   double first = log10(volts/0.00631)*20;
   double second = first + 94 - 44 - 25;
   avgDB += second;
   //Serial.println(avgDB);
  
   if(startMillis - prevMillis > timer){
    prevMillis = startMillis;
    avgDB = avgDB / 100;
    Serial.println("- - - - - - - -");
    Serial.println(avgDB);
    Serial.println("- - - - - - - -");
    avgDB=0;
   }
}
