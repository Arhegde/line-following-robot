// IR sensor pins
#define IR_LEFT A0
#define IR_RIGHT A1

// Motor driver pins
#define IN1 9   // Left Motor +
#define IN2 10  // Left Motor -
#define IN3 5   // Right Motor +
#define IN4 6   // Right Motor -
#define ENA 3   // Left Motor Speed (PWM)
#define ENB 11  // Right Motor Speed (PWM)

// Motor speed (adjust as needed: 0 to 255)
int motorSpeed = 65;

void setup() {
  // Sensor inputs
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Motor outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600); // Optional for debugging
}

void loop() {
  // Read sensor values
  int leftSensor = digitalRead(IR_LEFT);
  int rightSensor = digitalRead(IR_RIGHT);

  // Optional: print values for testing
  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.print(" | Right: ");
  Serial.println(rightSensor);

  if (leftSensor == LOW && rightSensor == LOW) {
    // Both sensors on black -> move forward
    moveForward();
  }
  else if (leftSensor == LOW && rightSensor == HIGH) {
    // Left on black, right on white -> turn right
    turnRight();
  }
  else if (leftSensor == HIGH && rightSensor == LOW) {
    // Right on black, left on white -> turn left
    turnLeft();
  }
  else {
    // Both on white (off track) -> stop or search
    stopMotors();
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, motorSpeed);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, 0);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}