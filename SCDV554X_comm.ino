//This is example code for load data bit to SCDV554X 4 digits vertical format 5x5 display from Osram.

#include<SPI.h> //init. library for spi device .I will communicate with SCDV554X via SPI bus interface .
const int Load= 10; //Load enable pin.

void SCDV554X.begin(){
pinMode(Load, OUTPUT);//set pin10 to output for switching "send bit" or "display data out"
SPI.begin(); //Start SPI 
SPI.setDataMode(SPI_MODE0); //Set SPI Mode 0 send data at rising edge 
SPI.setBitOrder(LSBFIRST);//set the LSB first instead MSB first 
digitalWrite(Load, LOW);//Enable BarLOAD pin 
SPI.transfer(0xC0); // clear display
digitalWrite(Load, HIGH);//Disable BarLOAD pin
delayMicroseconds(1);
}

void setup(){
digitalWrite(Load, LOW);
SPI.transfer(0xF8); // test lamp
digitalWrite(Load, HIGH);
delay(1000); // just wait for 1 sec ;D
digitalWrite(Load, LOW);
SPI.transfer(0xC0); // clear display after test lamp
digitalWrite(Load, HIGH);
}


void loop(){
digitalWrite(Load, LOW);
SPI.transfer(0xA1);// select digit 1 for'H'
SPI.transfer(0x11);//10001
SPI.transfer(0x31);//10001
SPI.transfer(0x5F);//11111   H
SPI.transfer(0x71);//10001
SPI.transfer(0x8f);//10001
SPI.transfer(0xA2);// select digit 2 for 'I'
SPI.transfer(0x0E);//01110
SPI.transfer(0x24);//00100
SPI.transfer(0x44);//00100   I
SPI.transfer(0x64);//00100
SPI.transfer(0x8E);//01110
digitalWrite(Load, HIGH);
digitalWrite(Load, LOW);
SPI.transfer(0xC0); // clear display
digitalWrite(Load, HIGH);
}



void SCDV554X.mosi(uint_8t Dat){
digitalWrite(Load, LOW);
SPI.transfer(Dat);
delayMicroseconds(1);
digitalWrite(Load, HIGH);
}
