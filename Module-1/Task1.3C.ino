const byte led_pin_1 = 13;
const byte led_pin_2 = 12;
const byte pir_sensor_pin = 2;
const byte pir_sensor_pin_2 = 3;


volatile byte pirSensorValue = LOW;
volatile byte pirSensorValue2 = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin_1,OUTPUT);
  pinMode(led_pin_2,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pir_sensor_pin),pir_sensor_triggered,RISING);
  attachInterrupt(digitalPinToInterrupt(pir_sensor_pin_2),pir_sensor_triggered_2,RISING);
}

void loop() {

  digitalWrite(led_pin_1,pirSensorValue);
  digitalWrite(led_pin_2,pirSensorValue2);

}

void pir_sensor_triggered(){
  
  Serial.println("PIR Sensor State Changed");
  
  if (pirSensorValue == LOW){
    pirSensorValue = HIGH;
    Serial.println("Setting Light 1 to ON");
  } else {
    pirSensorValue = LOW;
     Serial.println("Setting Light 1 to OFF");
  }
  
}



void pir_sensor_triggered_2(){
  
  Serial.println("PIR Sensor 2 State Changed");
  
  if (pirSensorValue2 == LOW){
    pirSensorValue2 = HIGH;
    Serial.println("Setting Light 2 to ON");
  } else {
    pirSensorValue2 = LOW;
     Serial.println("Setting Light 2 to OFF");
  }
  
}