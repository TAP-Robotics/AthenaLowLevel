#include <menc/menc.hpp>

// set initial values for encoder positions
volatile long MENC::MENC_A_POS = 0l;
volatile long MENC::MENC_B_POS = 0l;
const int8_t MENC::ENCUP_TABLE[] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};

MENC::MENC() {
	pinMode(MENC_A_A, INPUT);  // PD2 (Pin D2)
	pinMode(MENC_A_B, INPUT);  // PD3 (Pin D3)
	pinMode(MENC_B_A, INPUT);  // PC4 (Pin A4)
	pinMode(MENC_B_B, INPUT);  // PC5 (Pin A5)
	
	// Enable pin change interrupts for PD2, PD3, PC4, and PC5
    PCMSK2 |= (1 << MENC_A_A) | (1 << MENC_A_B);  // Enable interrupt for PD2 and PD3
    PCMSK1 |= (1 << MENC_B_A) | (1 << MENC_B_B);  // Enable interrupt for PC4 and PC5
    PCICR |= (1 << PCIE1) | (1 << PCIE2);         // Enable PCINT1 and PCINT2 interrupt groups

    sei();  // Enable global interrupts
}

// MOTOR_B
ISR(PCINT1_vect) {
	static uint8_t enc_last_read = 0;
	enc_last_read <<=2;
	// b00aa0000
	// b00000011 << 4 = b00110000 
	// Mask it with &
	
	enc_last_read |= (PINC & (3 << 4)) >> 4;
	MENC::MENC_B_POS += MENC::ENCUP_TABLE[(enc_last_read & 0x0f)];
}

// MOTOR_A
ISR(PCINT2_vect) {
	static uint8_t enc_last_read = 0;
	enc_last_read <<=2;
	// 00000011 << 2
	enc_last_read |= (PIND & (3 << 2)) >> 2;
	MENC::MENC_A_POS += MENC::ENCUP_TABLE[(enc_last_read & 0x0f)];
}

EncoderValues MENC::getEncoderValues() {
	EncoderValues vals;
	vals.MOTOR_A = MENC_A_POS;
	vals.MOTOR_B = MENC_B_POS;
	return vals;
}