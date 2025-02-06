#include <menc/menc.hpp>

MENC menc;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(menc.MENC_A_POS);
  Serial.print(" | ");
  Serial.println(menc.MENC_B_POS);
}