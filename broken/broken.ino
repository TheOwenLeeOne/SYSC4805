
int rightMotor1 = 9;
int rightMotor2 = 10;
int leftMotor1 = 6;
int leftMotor2 = 5;
int motorSpeed = 175;
int motorToTurn = rightMotor1;
int secondaryMotor = leftMotor1;

bool turning;


int ir_R = 7;
int ir_L = 8;
int hit_R = HIGH;  // HIGH = no line
int hit_L = HIGH;
int directionCount = 0;

int directions[11] = {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0};


void setup() {
  pinMode(ir_R, INPUT);
  pinMode(ir_L, INPUT);


  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor2, 0);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);

}

void loop() {
  hit_R = digitalRead(ir_R);
  hit_L = digitalRead(ir_L);

  if (!turning) {
    if (hit_R == LOW && hit_L == LOW ) {
      //analogWrite(rightMotor1,motorSpeed);
    }
    else if ((hit_R == LOW && hit_L == HIGH) ) { //hit right
      //analogWrite(leftMotor1,motorSpeed);

      setMotor(leftMotor1);
    } else if ((hit_R == HIGH && hit_L == LOW) ) { //hit left
      //analogWrite(rightMotor1, motorSpeed);
      setMotor(rightMotor1);

    } else if (hit_R == HIGH && hit_L == HIGH) {
      Serial.print("init turn");
      if (directionCount <= (sizeof(directions) / sizeof(int))) {
        //motorSpeed = 0;
      }
      turning = true;
    }
  }
    else { //is turning
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
  

  analogWrite(motorToTurn, motorSpeed);
  analogWrite(secondaryMotor, motorSpeed/2);
  delay(10);
  analogWrite(rightMotor1, 0);
  analogWrite(leftMotor1, 0);
  delay(15);
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

