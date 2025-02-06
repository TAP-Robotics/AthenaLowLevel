#include <menc/menc.hpp>
#include <miver/miver.hpp>

MENC menc;
MIVER miver;

void setup() {
  Serial.begin(9600);
}

void loop() {
  miver.setMotorSpeeds(225, 255);
  Serial.print(menc.MENC_A_POS);
  Serial.print(" | ");
  Serial.println(menc.MENC_B_POS);
}