int sensorPin = A3;
int sensorValue = 0;
void setup() {
 Serial.begin(9600);
 pinMode(sensorPin, INPUT);
}
void loop() {
 sensorValue = analogRead(sensorPin);
 Serial.println(sensorValue);
}
