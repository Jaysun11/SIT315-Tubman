const byte led_pin_1 = 13;
const byte led_pin_2 = 12;
const byte led_pin_3 = 11;
const byte led_pin_4 = 10;

const byte pir_sensor_pin = 2;
const byte pir_sensor_pin_2 = 3;

volatile byte LED_state = LOW;
volatile byte pirSensorValue = LOW;
volatile byte pirSensorValue2 = LOW;
volatile byte pirSensorValue3 = LOW;

void setup() {
  
  //Timer Setup Using timer 1
  cli();// Temporarily stop interrupts
  
  TCCR1A = 0;			//Reset TCCR1A register
  TCCR1B = 0;			//Reset TCCR1B register
  
    // Set Timer 1 prescaler to 1024 
  TCCR1B |= B00000101;     
  
  //Enable compare match on timer 1
  TIMSK1 |= B00000010;        
  
  //Set the compare match value on timer 1 to 31250 (2 seconds with prescaler 1024)
  OCR1A = 31250;              
  
  sei(); // Enable interrupts
  
  
  Serial.begin(9600);
  pinMode(led_pin_1,OUTPUT);
  pinMode(led_pin_2,OUTPUT);
  pinMode(led_pin_3,OUTPUT);
  pinMode(led_pin_4,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pir_sensor_pin),pir_sensor_triggered,RISING);
  attachInterrupt(digitalPinToInterrupt(pir_sensor_pin_2),pir_sensor_triggered_2,RISING);

  //Setup PCINT for interrupt on 3rd sensor
  PCICR |= B00000100; //Enable interrupts on PCINT Group 2
  PCMSK2 |= B00100000; // Pin D5 enabled for interrupt

}

void loop() {

  digitalWrite(led_pin_1,pirSensorValue);
  digitalWrite(led_pin_2,pirSensorValue2);
  digitalWrite(led_pin_3,LED_state);
  digitalWrite(led_pin_4,pirSensorValue3);

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

void pir_sensor_triggered_3(){
  
  Serial.println("PIR Sensor 3 State Changed");
  
  if (pirSensorValue3 == LOW){
    pirSensorValue3 = HIGH;
    Serial.println("Setting Light 4 to ON");
  } else {
    pirSensorValue3 = LOW;
     Serial.println("Setting Light 4 to OFF");
  }
  
}

ISR(TIMER1_COMPA_vect){
  TCNT1  = 0;                  //Reset timer for next interrupt
  Serial.println("Interrupt triggered from timer (2 seconds)");
  if(LED_state == LOW){
    LED_state = HIGH;
    Serial.println("LED 3 ON");
  } else {
    LED_state = LOW;
    Serial.println("LED 3 OFF");
  }
 
}

ISR (PCINT2_vect){
  //Interrupt routine for D5 on PCINT Group 2
  pir_sensor_triggered_3();
  
  
}


