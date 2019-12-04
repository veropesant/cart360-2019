char message[10];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.readBytes(message,10);
  Serial.println(message);
  delay(1000);
 

}
