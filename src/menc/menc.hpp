#include <Arduino.h>
#pragma once

// DEFINE PORTD (Actual) PCINT pins
#define MENC_A_A PD2
#define MENC_A_B PD3

// DEFINE PORTC (Analog) PCINT pins
#define MENC_B_A PC4
#define MENC_B_B PC5

struct EncoderValues {
	long MOTOR_A;
	long MOTOR_B;
};

class MENC{
public:
	static const int8_t ENCUP_TABLE[]; 
	static volatile long MENC_A_POS;
	static volatile long MENC_B_POS;
	MENC();
	static EncoderValues getEncoderValues();
};