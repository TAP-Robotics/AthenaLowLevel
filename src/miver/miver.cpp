#include <miver/miver.hpp>
MIVER::MIVER() {
	pinMode(MOTOR_A_L1, OUTPUT);
	pinMode(MOTOR_A_L2, OUTPUT);
	pinMode(MOTOR_B_L1, OUTPUT);
	pinMode(MOTOR_B_L2, OUTPUT);

	pinMode(PWMA, OUTPUT);
	pinMode(PWMB, OUTPUT);
}

// r (0 not reversed, 1 reversed) i (i 1 left, 0 right)
void MIVER::setMotorSpeed(int i, int speed) {
	int r = 0;
	if (speed < 0) {
		speed= -speed;
		r = 1;
	}
	if (speed > 255) speed=255;
	analogWrite(PWMA, speed);
	analogWrite(PWMB, speed);
	if (i == 1) {
		if (r == 0) {digitalWrite(MOTOR_A_L1, HIGH); digitalWrite(MOTOR_A_L2, LOW);}
		if (r == 1) {digitalWrite(MOTOR_A_L1, LOW); digitalWrite(MOTOR_A_L2, HIGH);}
	} else {
		if (r == 0) {digitalWrite(MOTOR_B_L1, HIGH); digitalWrite(MOTOR_B_L2, LOW);}
		if (r == 1) {digitalWrite(MOTOR_B_L1, LOW); digitalWrite(MOTOR_B_L2, HIGH);}
	}	
}

void MIVER::setMotorSpeeds(int right, int left) {
    MIVER::setMotorSpeed(0, left);  // Set MOTOR_B (left motor)
    MIVER::setMotorSpeed(1, right); // Set MOTOR_A (right motor)
}