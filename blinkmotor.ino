// defines pins numbers
const int dirR = 4;
const int dirL = 7;
const int r = 5;
const int l = 6;
const int trigPin = 10;
const int echoPin = 9;

// defines variables
long duration;
int distance;
int turnPwm = 170;
int turnTime = 370;

void setup() {
  pinMode(dirL, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(l, OUTPUT);
  pinMode(dirR, OUTPUT);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
// neverused encoders
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
 
  Serial.begin(9600);
  pauseMotors(500);
}

void loop() {
  distance = readDistance();
  printDistance();
  if(distance < 6){
    pauseMotors(3);
    goAnyWhere();
  }else{
    go(200);
  }
}

void printDistance{
  Serial.print("Distance: ");
  Serial.println(distance);
}

void goAnyWhere(){
  pauseMotors(300);
  turnLeft();
  Serial.println("Left turn");
  pauseMotors(500);
    if(readDistance() < 8){
      turnAround();
	  if(readDistance() < 8){
		  turnRight();
		  Serial.println("Right turn");
		  pauseMotors(500);
	  }
	}
}

void turnLeft(){
	leftFront(turnPwm);
    rightFront(turnPwm);
    delay(turnTime);
}

void turnRight(){
  leftBack(turnPwm);
  rightBack(turnPwm);
  delay(turnTime);
}

void turnAround(){
  Serial.println("Turn around");
  leftFront(turnPwm);
  rightFront(turnPwm);
  delay(turnTime*2);
  pauseMotors(300);
}

void go(int pwm){
   rightFront(pwm);
   leftBack(pwm+3);
  }

void pauseMotors(int pauseTime){
  stopRight();
  stopLeft();
  delay(pauseTime);
}

void leftFront(int pwm){
  digitalWrite(dirL, LOW); 
  analogWrite(l, pwm);
}
void rightFront(int pwm){
  digitalWrite(dirR, LOW); 
  analogWrite(r, pwm); 
}

void leftBack(int pwm){
  digitalWrite(dirL, HIGH); 
  analogWrite(l, pwm);
}
void rightBack(int pwm){
  digitalWrite(dirR, HIGH);
  analogWrite(r, pwm);
}

void stopLeft(){
  digitalWrite(l, HIGH); 
}

void stopRight(){
  digitalWrite(r, HIGH); 
}


void printEncoders(){
  Serial.print("EncRB:");
  Serial.print(analogRead(A0));
  Serial.print("\tEncLB:");
  Serial.print(analogRead(A1));
  Serial.print("\tEncRA:");
  Serial.print(analogRead(A2));
  Serial.print("\tEncLA:");
  Serial.println(analogRead(A3));
}

int readDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  return distance;
}
