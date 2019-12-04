int LED1 = 13;
int dryValue = 660;
int midValue = 340;
int wetValue = 220;
int sensor_pin = 0;
int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;
int motion_pin = 4;
int motion_state = LOW;
int motion_val = 0;
unsigned int timeRed = 0;
boolean redBlink = false;
int maxTimeBeforeBlink = 10000;
int currentColor;
char message[10]={"Water me!"}; 

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
 //RGB LED 
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  pinMode(motion_pin, INPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(sensor_pin);
  // print out the value you read:
  //Serial.println(sensorValue);
  
  controlData(sensorValue);
  delay(1);  // delay in between reads for stability

  if(currentColor == "red"){
   sendMessage();
  }
  delay(1000);

  //motion detector
//  if(digitalRead(motion_pin)==HIGH) {
//    //Serial.println("Movement detected.");
//    delay(10000);
//  } else {
//    //Serial.println("Did not detect movement.");
//  }

}


//function to analyze the data received and change the LED's color accordingly
void controlData(int data){
    //if data shows that soil is humid, LED turns green
    if (data < midValue-100) {
    RGB_color(0, 255, 0); // Green
    currentColor= "green";
    resetRed();
    } 
    else {
      //if data shows that soil is getting close to dry, LED turns blue
      if(data > midValue-100 && data < midValue+100){
        RGB_color(0, 0, 255); // Blue
        currentColor = "blue";
        resetRed();
       }else{
        
        //if data shows that soil is dry, LED turns red
        if(data > midValue+100){
          RGB_color(255, 0, 0); // Red
          currentColor = "red";
          if(timeRed==0){
            timeRed = millis();
          }
          //Serial.println(timeRed);
          if(!redBlink){
              //Serial.print("Delta time ");
              //Serial.println(millis() - timeRed);
              if(millis() - timeRed > 10000){
                delay(100);
                redBlink = true;
               
              }
              
            }
          else{
              blinkRed();
           }
      
          }
         
       }
      
     }
     
  }

//function to change the LED's color
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

 //makes the LED blink in red
 void blinkRed(){
      //Serial.println("blink");
      digitalWrite(red_light_pin, HIGH);  
      delay(100);
      digitalWrite(red_light_pin, LOW); 
      delay(100);
       
 }

 void sendMessage(){
  
    Serial.write(message, 10);
    delay(1000);
  
 }

 //puts red back to initial value, to allow to blink again when needed
 void resetRed(){
        
        redBlink = false;
        timeRed = 0;
        delay(100);
       
 }
