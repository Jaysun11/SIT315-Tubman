const byte led_pin = 13;
const byte sensor_pin = 2;

volatile byte sensorValue = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(sensor_pin),sensor_triggered,RISING);
}

void loop() {

   digitalWrite(led_pin,sensorValue);

}

void sensor_triggered(){
  
  Serial.println("Sensor State Change");
  
  if (sensorValue == LOW){
    sensorValue = HIGH;
    Serial.println("Setting Light to ON");
  } else {
    sensorValue = LOW;
     Serial.println("Setting Light to OFF");
  }
  
}