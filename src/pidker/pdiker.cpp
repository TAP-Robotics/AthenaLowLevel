#include <pidker/pidker.hpp>

PIDKER::PIDKER() {

}

void PIDKER::doPID(float targetLeft, float targetRight) {
	
}

float PIDKER::calculatePID(MotorPID &motor, long targetPos, long currentPos) {
	
	//
	float error = targetPos - currentPos;

	if(abs(error) < DBAND) {
		motor.einteg = 0;
		digitalWrite(motor.L1, LOW);
		digitalWrite(motor.L2, LOW);
		analogWrite(motor.EN, 0);
		return 0;
	}

	motor.einteg = constrain(motor.einteg + error, -MINTEG, MINTEG);
	float derivative = error - motor.lastError;
	motor.lastError = error;

	float output = KP * error + KI * motor.einteg + KD * derivative;
	int pwmSpeed = constrain(abs(output), 0, 255);
	analogWrite(motor.EN, pwmSpeed);
	if (output > HSTTHRES) {
		digitalWrite(motor.L1, HIGH);
		digitalWrite(motor.L2, LOW);
		motor.hysterisis = output;
	} else if (output < -HSTTHRES) {
		digitalWrite(motor.L1, LOW);
		digitalWrite(motor.L2, HIGH);
		motor.hysterisis = output;
	} else {
		if (motor.hysterisis > 0) {
			digitalWrite(motor.L1, HIGH);
			digitalWrite(motor.L2, LOW);
		} else {
			digitalWrite(motor.L1, LOW);
			digitalWrite(motor.L2, HIGH);
		}
	}
}