/*
  line_follower.ino
  Baseline two-sensor line-following robot for Arduino.

  Hardware assumed:
    - 2x IR reflectance sensors (digital output, e.g. TCRT5000 modules),
      mounted left/right, straddling the line.
      Sensor output convention used here: LOW = sensor sees the (dark) line,
      HIGH = sensor sees the (light) background.
      --> If your modules are wired the opposite way, swap LINE_DETECTED
          below, or just swap the LOW/HIGH checks.
    - L298N (or similar dual H-bridge) motor driver, 2 DC motors.

  Wiring (adjust to your actual pins):
    Left IR sensor   -> D2
    Right IR sensor  -> D3
    Left motor  IN1  -> D5   (direction)
    Left motor  IN2  -> D6   (direction)
    Left motor  ENA  -> D9   (PWM speed)
    Right motor IN3  -> D7   (direction)
    Right motor IN4  -> D8   (direction)
    Right motor ENB  -> D10  (PWM speed)
*/

// ---------- Pin definitions ----------
const uint8_t PIN_LEFT_SENSOR  = 2;
const uint8_t PIN_RIGHT_SENSOR = 3;

const uint8_t PIN_LEFT_IN1  = 5;
const uint8_t PIN_LEFT_IN2  = 6;
const uint8_t PIN_LEFT_EN   = 9;   // PWM

const uint8_t PIN_RIGHT_IN1 = 7;
const uint8_t PIN_RIGHT_IN2 = 8;
const uint8_t PIN_RIGHT_EN  = 10;  // PWM

// ---------- Tuning ----------
const int BASE_SPEED = 150;   // 0-255, forward cruising speed
const int TURN_SPEED = 100;   // 0-255, speed of the "slow" wheel while correcting
const bool LINE_DETECTED = LOW;  // sensor reading that means "on the black line"

// ---------- Motor primitives ----------
void setLeftMotor(int speed) {          // speed: -255..255, negative = reverse
    if (speed >= 0) {
        digitalWrite(PIN_LEFT_IN1, HIGH);
        digitalWrite(PIN_LEFT_IN2, LOW);
    } else {
        digitalWrite(PIN_LEFT_IN1, LOW);
        digitalWrite(PIN_LEFT_IN2, HIGH);
        speed = -speed;
    }
    analogWrite(PIN_LEFT_EN, constrain(speed, 0, 255));
}

void setRightMotor(int speed) {
    if (speed >= 0) {
        digitalWrite(PIN_RIGHT_IN1, HIGH);
        digitalWrite(PIN_RIGHT_IN2, LOW);
    } else {
        digitalWrite(PIN_RIGHT_IN1, LOW);
        digitalWrite(PIN_RIGHT_IN2, HIGH);
        speed = -speed;
    }
    analogWrite(PIN_RIGHT_EN, constrain(speed, 0, 255));
}

void driveForward() {
    setLeftMotor(BASE_SPEED);
    setRightMotor(BASE_SPEED);
}

void stopMotors() {
    setLeftMotor(0);
    setRightMotor(0);
}

// Nudge right: slow the right wheel so the robot arcs back toward the line
void correctRight() {
    setLeftMotor(BASE_SPEED);
    setRightMotor(TURN_SPEED);
}

// Nudge left: slow the left wheel
void correctLeft() {
    setLeftMotor(TURN_SPEED);
    setRightMotor(BASE_SPEED);
}

// ---------- Setup ----------
void setup() {
    pinMode(PIN_LEFT_SENSOR, INPUT);
    pinMode(PIN_RIGHT_SENSOR, INPUT);

    pinMode(PIN_LEFT_IN1, OUTPUT);
    pinMode(PIN_LEFT_IN2, OUTPUT);
    pinMode(PIN_LEFT_EN, OUTPUT);
    pinMode(PIN_RIGHT_IN1, OUTPUT);
    pinMode(PIN_RIGHT_IN2, OUTPUT);
    pinMode(PIN_RIGHT_EN, OUTPUT);

    stopMotors();
}

// ---------- Main loop ----------
void loop() {
    bool leftOnLine  = (digitalRead(PIN_LEFT_SENSOR)  == LINE_DETECTED);
    bool rightOnLine = (digitalRead(PIN_RIGHT_SENSOR) == LINE_DETECTED);

    if (leftOnLine && rightOnLine) {
        // both sensors on the line: straddling correctly, or crossing an
        // intersection/thick marker -> just go straight
        driveForward();
    } else if (leftOnLine && !rightOnLine) {
        // line has drifted left relative to the robot -> steer left
        correctLeft();
    } else if (!leftOnLine && rightOnLine) {
        // line has drifted right relative to the robot -> steer right
        correctRight();
    } else {
        // neither sensor sees the line -> lost it.
        // Baseline behaviour: stop. (Extension: spin slowly to search.)
        stopMotors();
    }
}
