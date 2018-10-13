class SCDQ5541 {
  private:
    int m_clock, m_data, m_load;
  public:
    void bitbang(unsigned char code)
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

    SCDQ5541(int clock, int data, int load)
      : m_clock(clock)
      , m_data(data)
      , m_load(load) {}
    void begin();
    void clear();
    void sendDigitData(int digit, char *digitData);
    void setBrightness(int percent);
    void setPowerdownMode(boolean on);
    void setLampTest(boolean on);
};

void SCDQ5541::clear()
{
  bitbang(0xc0);
}

void SCDQ5541::setBrightness(int percent)
{
  bitbang(0xf0 + map(percent, 0, 100, 6, 0));
}

void SCDQ5541::setPowerdownMode(boolean on)
{
  if (on)
    bitbang(0xff);
  else
    setBrightness(100);
}

void SCDQ5541::setLampTest(boolean on)
{
  if (on)
    bitbang(0xf8);
  else
    clear();
}

void SCDQ5541::begin()
{
  pinMode(m_clock, OUTPUT);
  pinMode(m_data, OUTPUT);
  pinMode(m_load, OUTPUT);
  clear();
}

void SCDQ5541::sendDigitData(int digit, char *rowData)
{
  if (digit < 0 || digit > 3)
    return;
  bitbang(0xa0 + digit);
  for (int row = 0; row < 5; row++) {
    bitbang(rowData[row] | row << 5);
  }
}

SCDQ5541 ledMatrix(2, 0, 4); //Clock,Data,Load

void setup() {
  ledMatrix.begin();
  ledMatrix.bitbang(0xC0); // clear display
  ledMatrix.bitbang(0xA0);// select digit 0 for'up arrow'
  ledMatrix.bitbang(0x04);//00100
  ledMatrix.bitbang(0x2E);//01110
  ledMatrix.bitbang(0x55);//10101
  ledMatrix.bitbang(0x64);//00100
  ledMatrix.bitbang(0x84);//00100
  ledMatrix.bitbang(0xA1);// select digit 1 for'H'
  ledMatrix.bitbang(0x11);//10001
  ledMatrix.bitbang(0x31);//10001
  ledMatrix.bitbang(0x5F);//11111   H
  ledMatrix.bitbang(0x71);//10001
  ledMatrix.bitbang(0x91);//10001
  ledMatrix.bitbang(0xA2);// select digit 2 for 'I'
  ledMatrix.bitbang(0x0E);//01110
  ledMatrix.bitbang(0x24);//00100
  ledMatrix.bitbang(0x44);//00100   I
  ledMatrix.bitbang(0x64);//00100
  ledMatrix.bitbang(0x8E);//01110
  ledMatrix.bitbang(0xA3);// select digit 3 for'down arrow'
  ledMatrix.bitbang(0x04);//00100
  ledMatrix.bitbang(0x24);//00100
  ledMatrix.bitbang(0x55);//10101
  ledMatrix.bitbang(0x6E);//01110
  ledMatrix.bitbang(0x84);//00100
}
void loop() {
  static int b = 0;
  ledMatrix.setBrightness(b);
  b = (b + 5) % 100;
  delay(50);
}
