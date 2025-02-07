#include <Arduino.h>
#include <menc/menc.hpp>
#include <miver/miver.hpp>

#pragma once
#define KP 0.45
#define KI 0.15
#define KD 0.40
#define DBAND 5.0
#define MINTEG 100.0
#define HSTTHRES 5 

struct MotorPID {
	float einteg = 0;
	float lastError = 0;
	float hysterisis = 0;

	int L1;
	int L2;
	int EN;
	MotorPID(float einteg = 0, float lastError = 0, float hysterisis = 0, 
             int l1 = 0, int l2 = 0, int en = 0)
        : einteg(einteg), lastError(lastError), hysterisis(hysterisis),
          L1(l1), L2(l2), EN(en) {}
};

class PIDKER {
public:

	PIDKER::PIDKER();
	void doPID(float targetLeft, float targetRight);
	float calculatePID(MotorPID &motor, long targetPos, long currentPos);
};
// float MENC::findUofT(long targetPos)
// {
// 	// Tuned PID gains (adjust based on your system)
// 	float kp = 0.8;			 // Reduced proportional gain
// 	float ki = 0.1;			 // Reduced integral gain
// 	float kd = 0.3;			 // Adjusted derivative gain
// 	float deadband = 5;		 // Minimum error to respond to
// 	float maxIntegral = 100; // Anti-windup

// 	// Calculate error
// 	float error = targetPos - motorLeftPosition;

// 	// Deadband - ignore small errors
// 	if (abs(error) < deadband)
// 	{
// 		digitalWrite(MOTOR_LEADS_A1, LOW);
// 		digitalWrite(MOTOR_LEADS_B1, LOW);
// 		einteg = 0; // Reset integral term
// 		return 0;
// 	}

// 	// PID calculations with clamping
// 	einteg += error;
// 	einteg = constrain(einteg, -maxIntegral, maxIntegral); // Anti-windup
// 	float derivative = error - lastError;
// 	lastError = error;

// 	float output = kp * error + ki * einteg + kd * derivative;

// 	// Hysteresis control
// 	static float hysteresis = 0;
// 	const float hysteresisThreshold = 10; // Adjust based on needed smoothness

// 	if (output > hysteresisThreshold)
// 	{
// 		digitalWrite(MOTOR_LEADS_A1, HIGH);
// 		digitalWrite(MOTOR_LEADS_B1, LOW);
// 		hysteresis = output; // Remember last direction
// 	}
// 	else if (output < -hysteresisThreshold)
// 	{
// 		digitalWrite(MOTOR_LEADS_A1, LOW);
// 		digitalWrite(MOTOR_LEADS_B1, HIGH);
// 		hysteresis = output;
// 	}
// 	else
// 	{
// 		// Maintain previous state until threshold crossed
// 		if (hysteresis > 0)
// 		{
// 			digitalWrite(MOTOR_LEADS_A1, HIGH);
// 			digitalWrite(MOTOR_LEADS_B1, LOW);
// 		}
// 		else
// 		{
// 			digitalWrite(MOTOR_LEADS_A1, LOW);
// 			digitalWrite(MOTOR_LEADS_B1, HIGH);
// 		}
// 	}

// 	return output;
// }