//Define what pins we are using on the arduino
int frontleft = 13;
int frontright = 12;
int backleft = 11;
int backright = 10;

//Define sensor pins on arduino and 2 sensore vars
int trigger_pin = 2;
int echo_pin = 3;

int timein;
int distance;

//Define the pins for lights for the motor
int frontlight = 4;
int backlight = 6;

int lightsensor = A0;
int val;

//This var is used by an random statment then an if statement to see whitch way it turns
int decide;

void setup() {
  //Begin and test Serial
  Serial.begin(9600);
  Serial.println("Serial is a Go");

  //Define motor pins to output power
  pinMode(frontleft, OUTPUT);
  pinMode(frontright, OUTPUT);
  pinMode(backleft, OUTPUT);
  pinMode(backright, OUTPUT);

  //Defines the sensor's trigger and echo pins
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  //Define the pins to output power to led
  pinMode(frontlight, OUTPUT);
  pinMode(backlight, OUTPUT);
  pinMode(lightsensor, INPUT);
}


void loop() {
  //Turns on the sensor for ten mircoseconds then turns it off
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_pin, LOW);

  //Records the incoming signal and then does some simple math
  timein = pulseIn (echo_pin, HIGH);
  distance = (timein * 0.034) / 2;

  //Prints distance
  //Serial.println(distance);

  //Picks a random number to choose if it turns left or right
  decide = random(0, 2);
  //Serial.println(decide);


  //Reads light sensor
  val = analogRead(lightsensor);
  Serial.println(val);

  digitalWrite(backlight, LOW);

  //If the distance is greaterthen or = to 11 go to forward()
  if (distance >= 59){
    forward();
  }
  //If distance is between 0-60 go to stop
  if (distance > 20 && distance < 60) {

    //If decide = 0 go to turnright
    if (decide == 1){
      //stopit();
      turnright();
    }

    else {
      //digitalWrite(leftlight, HIGH);
      //digitalWrite(rightlight, LOW);
      //stopit();
      turnleft();
    }
  }

  //If distance is below -100 go forward                                                                                                                                                                                                              
  if (distance <= -100) {
    forward();
  }
  
  if (distance < 19 && distance > 0) {
    stopit();
  }
}


//This function turns on all four wheels
void forward() {
  Serial.println("Moving Foward");
  
  digitalWrite(frontleft, LOW);
  digitalWrite(frontright, LOW);
  digitalWrite(backleft, LOW);
  digitalWrite(backright, LOW);

  if(val <= 50){
    digitalWrite(frontlight, HIGH);
  }
  else{
    digitalWrite(frontlight, LOW);
  }
}


//This function stops all wheels
void stopit() {
  Serial.println("STOPPING");
  
  digitalWrite(frontleft, HIGH);
  digitalWrite(frontright, HIGH);
  digitalWrite(backleft, HIGH);
  digitalWrite(backright, HIGH);

  digitalWrite(backlight, HIGH);
}


//This function tuns off the left 2 wheels to turn left
void turnright() {
  Serial.println("Turning Right");

  digitalWrite(frontleft, HIGH);
  digitalWrite(frontright, HIGH);
  digitalWrite(backleft, HIGH);
  digitalWrite(backright, HIGH);

  delay(500);

  //Turn off motors on 1 side(Making it turn left)
  digitalWrite(frontleft, LOW);
  digitalWrite(backleft, LOW);

  digitalWrite(frontright, HIGH);
  digitalWrite(backright, HIGH);

  delay(2000);
  //forward();
}


//This function tuns off the right 2 wheels to turn left
void turnleft() {
  Serial.println("Turning left");

  digitalWrite(frontleft, HIGH);
  digitalWrite(frontright, HIGH);
  digitalWrite(backleft, HIGH);
  digitalWrite(backright, HIGH);

  delay(500);

  //Turn off motors on 1 side(Making it turn left)
  digitalWrite(frontleft, HIGH);
  digitalWrite(backleft, HIGH);

  digitalWrite(frontright, LOW);
  digitalWrite(backright, LOW);
  
  delay(2000);
  //forward();
}
