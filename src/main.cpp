#include <menc/menc.hpp>
#include <pidker/pidker.hpp>

MENC menc;
PIDKER pdiker;

MotorPID leftMotor(0.0, 0.0, 0.0, MOTOR_A_L1, MOTOR_A_L2, PWMA);
MotorPID rightMotor(0.0, 0.0, 0.0, MOTOR_B_L1, MOTOR_B_L2, PWMB);

#define TARGET_MIN 2500 // Minimum target position for erratic function
#define TARGET_MAX 3200 // Maximum target position for erratic function
#define TARGET_CHANGE_INTERVAL_MS 500 // Change target every 500 milliseconds (0.5 seconds)

void setup() {
  Serial.begin(115200);
}


float getErraticTargetPosition() {
  static unsigned long lastTargetChangeTime = 0;
  static float currentErraticTarget = 2800; // Initial target (can be any value within range)

  unsigned long currentTime = millis();
  if (currentTime - lastTargetChangeTime >= TARGET_CHANGE_INTERVAL_MS) {
    currentErraticTarget = random(TARGET_MIN, TARGET_MAX + 1); // +1 to include TARGET_MAX in range
    lastTargetChangeTime = currentTime;
  }
  return currentErraticTarget;
}

void loop() {
  float ert = getErraticTargetPosition();
  pdiker.calculatePID(leftMotor, ert, menc.MENC_A_POS);
  pdiker.calculatePID(rightMotor, ert, menc.MENC_B_POS);
  Serial.print(menc.MENC_A_POS);
  Serial.print(" ");
  Serial.println(menc.MENC_B_POS);
}