#include "Arduino.h"
#include "SCDV554X.h"


void SCDV554X::bitbang(unsigned char code)
    {
      digitalWrite(m_load, LOW);
      for (int i = 0; i < 8; i++) {
        digitalWrite(m_clock, LOW);
        digitalWrite(m_data, code & 0x01);
        digitalWrite(m_clock, HIGH);
        code >>= 1;
      }
      digitalWrite(m_load, HIGH);
    }
	
void SCDV554X::clear()
{
  bitbang(0xc0);
}

void SCDV554X::setBrightness(int percent)
{
  bitbang(0xf0 + map(percent, 0, 100, 6, 0));
}

void SCDV554X::setPowerdownMode(boolean on)
{
  if (on)
    bitbang(0xff);
  else
    setBrightness(100);
}

void SCDV554X::setLampTest(boolean on)
{
  if (on)
    bitbang(0xf8);
  else
    clear();
}

void SCDV554X::begin()
{
  pinMode(m_clock, OUTPUT);
  pinMode(m_data, OUTPUT);
  pinMode(m_load, OUTPUT);
  clear();
}

void SCDV554X::sendDigitData(int digit, char *rowData)
{
  if (digit < 0 || digit > 3)
    return;
  bitbang(0xa0 + digit);
  for (int row = 0; row < 5; row++) {
    bitbang(rowData[row] | row << 5);
  }
}