import processing.serial.*;

Serial port; 
Table table;
int prevMillis = 0;


String data; 
String c;

void setup() {
  port = new Serial(this, Serial.list()[1], 9600);

  println(Serial.list());

  table = new Table();
  table.addColumn("Date");
  table.addColumn("Hour");
  table.addColumn("Altitude");
  table.addColumn("Long");
  table.addColumn("Lat");
  table.addColumn("Sound");
  table.addColumn("Air");
  table.addColumn("Light");
}

void draw() {  
  if (port.available() > 0) {
    delay(100);
    TableRow newRow = table.addRow();
    data = port.readString();
    //println(trim(data));

    for (int i=0; i<data.length(); i++) {
      if (data.charAt(i) == 'A') {
        println("Date " + data.substring(1, data.indexOf('B')));
        c= data.substring(1, data.indexOf('B'));
        newRow.setString("Date", c);
      }

      if (data.charAt(i) == 'B') {
        println("Hour: " + data.substring(i+1, data.indexOf('C')));
        c= data.substring(i+1, data.indexOf('C'));
        newRow.setString("Hour", c);
      }

      if (data.charAt(i) == 'C') {
        println("Altitude: " + data.substring(i+1, data.indexOf('D')));
        c= data.substring(i+1, data.indexOf('D'));
        newRow.setString("Altitude", c);
      }

      if (data.charAt(i) == 'D') {
        println("Long: " + data.substring(i+1, data.indexOf('E')));
        c= data.substring(i+1, data.indexOf('E'));
        newRow.setString("Long", c);
      }

      if (data.charAt(i) == 'E') {
        println("Lat: " + data.substring(i+1, data.indexOf('F')));
        c= data.substring(i+1, data.indexOf('F'));
        newRow.setString("Lat", c);
      }

      if (data.charAt(i) == 'F') {
        println("Sound: " + data.substring(i+1, data.indexOf('G')));
        c= data.substring(i+1, data.indexOf('G'));
        newRow.setString("Sound", c);
      }

      if (data.charAt(i) == 'G') {
        println("Air: " + data.substring(i+1, data.indexOf('H')));
        c= data.substring(i+1, data.indexOf('H'));
        newRow.setString("Air", c);
      }

      if (data.charAt(i) == 'H') {
        println("Light: " + data.substring(i+1, data.length()));
        c= data.substring(i+1, data.length());
        newRow.setString("Light", c);
      }
    }
    //newRow.setString("Longitude", data);
    saveTable(table, "data/new_timer.csv");
  }
}
