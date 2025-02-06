#include <Arduino.h>
#pragma once

#define MOTOR_A_L1 13
#define MOTOR_A_L2 12
#define MOTOR_B_L1 8
#define MOTOR_B_L2 7
#define PWMA 9
#define PWMB 10

class MIVER {
public:
	MIVER::MIVER();
	void setMotorSpeed(int i, int speed);
	void setMotorSpeeds(int right, int left);
};