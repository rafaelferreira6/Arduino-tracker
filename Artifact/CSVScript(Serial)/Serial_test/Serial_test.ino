long prevMillis = 0;
long timer = 10000;

void setup() {
  Serial.begin(9600);

}

void loop() {
  unsigned long curMillis = millis();

  if (curMillis - prevMillis > timer) {
    /*-GPS-*/
    Serial.print("A");
    Serial.print(20);
    Serial.print("/");
    Serial.print(02);
    Serial.print("/");
    Serial.println(2018);

    Serial.print("B");
    Serial.print(15);
    Serial.print(":");
    Serial.println(58);

    Serial.print("C");
    Serial.println(23.48);

    Serial.print("D");
    Serial.println(-8.238237);

    Serial.print("E");
    Serial.println(3.238232);

    Serial.print("F");
    Serial.println(23);
    
    Serial.print("G");
    Serial.println(6);
    
    Serial.print("H");
    Serial.println(10);

    prevMillis = curMillis;
  }
}
