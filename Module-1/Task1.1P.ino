// C++ code
//
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop()
{
  
  int sensorReading = digitalRead(2);
  
  
  if (sensorReading == 1) {
    Serial.println("Motion Detected");
    digitalWrite(13, HIGH);
  }
  else {
    Serial.println("No Motion Detected");
    digitalWrite(13, LOW);
  }
  
  
}