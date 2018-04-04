
int leftMotor1 = 9;
int leftMotor2 = 10;
int rightMotor1 = 5;
int rightMotor2 = 6;
int motorSpeed = 182;
int motorToTurn = rightMotor1;
int secondaryMotor = leftMotor1;

// defines pins numbers
const int trigPin = 2;
const int echoPin = 3;
// defines variables
long duration = 0;
int distance = 20;

int completedLED = 12;

bool turning = false;


int ir_R = 7;
int ir_L = 8;
int hit_R = HIGH;  // High = 1 = NO WALL. LOW = 0 = CLOSE TO WALL
int hit_L = HIGH;
int directionCount = 0;
int turnCount = 0;

//0 left turn, 1 right turn
int directions[4] = {0, 1, 1, 0};


void setup() {
  pinMode(ir_R, INPUT);
  pinMode(ir_L, INPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(completedLED, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  analogWrite(leftMotor1, 0);
  analogWrite(rightMotor1, 0);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor2, 0);
  digitalWrite(LED_BUILTIN, LOW);

  delay(15);

  Serial.begin(9600);

}

void loop() {
  hit_R = digitalRead(ir_R);
  hit_L = digitalRead(ir_L);
  Serial.println(hit_L);
  
if(directionCount >= 4){

      if(turnCount < 150){
        straightenOut();
        turnCount++;
      }else{
  
      analogWrite(rightMotor1, 0);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor2, 0);
      analogWrite(leftMotor1, 0);
      }
}else if(turning || distance < 5){
    turning = true;
    if(directions[directionCount] == 0){
      //turn left
      analogWrite(rightMotor1, 220);
      analogWrite(leftMotor2, 180);
      
      
    }else{
      //turn right
      analogWrite(rightMotor2, 220);
      analogWrite(leftMotor1, 180);
    }
    turnCount++;
    if(turnCount == 30){
      turning = false;
      directionCount++;
      turnCount = 0;
      
    }
  }else{
    //go forward
    straightenOut();
  }
  delay(20);
  analogWrite(rightMotor1, 0);
    analogWrite(leftMotor1, 0);
  analogWrite(rightMotor2, 0);
    analogWrite(leftMotor2, 0);
    delay(10);
  
calculateDistance();

//  if (!turning){ // Following path
//    
//    getDirection();
//    
//  } else { // In a turn
//
//    getTurn();
//    
//  }
//
//  writeMotors();
  
}


void straightenOut(){

  if(directionCount == 2){
    if(!hit_L){
      driftRight();
    }else{
      driftLeft();
    }
  }else if(directionCount == 3){
    if(!hit_R){
      driftLeft();
    }else{
      driftRight();
    }
  }else{
    if(!hit_R){
      driftLeft();
    }else if(!hit_L){
      driftRight();
    }
    else{
      straight();
    }
  }   
}


void straight(){
  analogWrite(rightMotor1, 190);
   analogWrite(leftMotor1, 140);
}

void driftRight(){
  analogWrite(rightMotor1, 170);
  analogWrite(leftMotor1, 180);
}

void driftLeft(){
   analogWrite(rightMotor1, 200);
   analogWrite(leftMotor1, 140);
}

void setMotor(int motor){
  if(motor == rightMotor1){
    motorToTurn = rightMotor1;
    secondaryMotor = leftMotor1;
  }
  else{
    motorToTurn = leftMotor1;
    secondaryMotor = rightMotor1;
  }
}

void calculateDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
//  Serial.println(duration);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
 // Serial.print("Distance: ");
  //Serial.println(distance);
}

void writeMotors(){
  if(motorToTurn == rightMotor1){
    analogWrite(motorToTurn, motorSpeed + 40);
  } else {
    analogWrite(motorToTurn, motorSpeed);
  }
  delay(17);
  analogWrite(rightMotor1, 0);
  analogWrite(leftMotor1, 0);
  delay(20);
}

void getTurn(){
  
      if (directions[directionCount] == 0) {
        //sharp turn left
        Serial.println("turning LEFT");
        setMotor(rightMotor1);
      } else if (directions[directionCount] == 1) {
        Serial.println("turning RIGHT");
        setMotor(leftMotor1);
      }
      
      if(hit_L == LOW && hit_R == LOW) {
        Serial.println("end of turn");
          turning = false;
          directionCount++;
      }
      
}

void getDirection(){
      if ((hit_R == LOW && hit_L == HIGH) ) { //hit left
      //analogWrite(leftMotor1,motorSpeed);

      setMotor(rightMotor1);
    } else if ((hit_R == HIGH && hit_L == LOW) ) { //hit right
      //analogWrite(rightMotor1, motorSpeed);
      setMotor(leftMotor1);

    } else if (hit_R == HIGH && hit_L == HIGH) {
      Serial.print("init turn");
      if (directionCount <= (sizeof(directions) / sizeof(int))) {
        //motorSpeed = 0;
      }
      turning = true;
    }
}


