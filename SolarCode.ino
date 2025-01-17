const int solarCellPin0 = A0;  // Analog input pin connected to the solar cell
const int solarCellPin1 = A1; 
const int solarCellPin2 = A2; 
const int numReadings = 300;
float readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
float total = 0;              // the running total
float average = 0;            // the average

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}


void loop() {
  int analogValue0 = analogRead(solarCellPin0);  // Read the analog value from the solar cell
  int analogValue1 = analogRead(solarCellPin1);
  int analogValue2 = analogRead(solarCellPin2);   
  float voltage0 = analogValue0  * (5.0 / 1023.0);  // Convert analog reading to voltage (assuming a 5V Arduino)
  float voltage1 = analogValue1  * (5.0 / 1023.0);
  float voltage2 = analogValue2  * (5.0 / 1023.0);  

  //Serial.print("Analog Value 0: ");
  //Serial.println(analogValue0);

  //Serial.print("Voltage0 (V): ");
  //Serial.println(voltage0);

  //Serial.print("Analog Value 1: ");
  //Serial.println(analogValue1);

  //Serial.print("Voltage1 (V): ");
  //Serial.println(voltage1);

  //Serial.print("Analog Value 2: ");
  //Serial.println(analogValue2);

  //Serial.print("Voltage2 (V): ");
  //Serial.println(voltage2);

  float voltageAvg = (voltage0 + voltage1 + voltage2) / 3;
  //Serial.println(voltageAvg);

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = voltageAvg;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);

  delay(1);  // Delay for 1 second before reading again
}
