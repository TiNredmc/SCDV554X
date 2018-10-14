
#incude <SCDV554X.h>
SCDQ5541 ledMatrix(2, 3, 4); //Clock,Data,Load

void setup() {
  ledMatrix.begin();
  ledMatrix.bitbang(0xC0); // clear display
  ledMatrix.bitbang(0xA0);// select digit 0 for 'T'
  delay(50);
  ledMatrix.bitbang(0x1F);//11111
  delay(50);
  ledMatrix.bitbang(0x24);//00100
  delay(50);
  ledMatrix.bitbang(0x44);//00100   T
  delay(50);
  ledMatrix.bitbang(0x64);//00100
  delay(50);
  ledMatrix.bitbang(0x84);//00100
  ledMatrix.bitbang(0xA1);// select digit 1 for'L'
  delay(50);
  ledMatrix.bitbang(0x10);//10000
  delay(50);
  ledMatrix.bitbang(0x30);//10000
  delay(50);
  ledMatrix.bitbang(0x50);//10000   L
  delay(50);
  ledMatrix.bitbang(0x70);//10000
  delay(50);
  ledMatrix.bitbang(0x9F);//11111
  ledMatrix.bitbang(0xA2);// select digit 1 for'H'
  delay(50);
  ledMatrix.bitbang(0x11);//10001
  delay(50);
  ledMatrix.bitbang(0x31);//10001
  delay(50);
  ledMatrix.bitbang(0x5F);//11111   H
  delay(50);
  ledMatrix.bitbang(0x71);//10001
  delay(50);
  ledMatrix.bitbang(0x91);//10001
  ledMatrix.bitbang(0xA3);// select digit 3 for'X'
  delay(50);
  ledMatrix.bitbang(0x11);//10001
  delay(50);
  ledMatrix.bitbang(0x2A);//01010
  delay(50);
  ledMatrix.bitbang(0x44);//00100   X
  delay(50);
  ledMatrix.bitbang(0x6A);//01010
  delay(50);
  ledMatrix.bitbang(0x91);//10001
  delay(50);
}
void loop() {
  delay(50);
  setup();
  
}
