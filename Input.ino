

#include <Wire.h>


/*
  static struct InputState {
  bool switches [2];
  struct ButtonState buttons [2];

  } gameInputState;
*/
 void uiInputTick() {
  for (int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameInputState.buttons[i].state;
    gameInputState.buttons[i].state = digitalRead(Buttons[i]);
    gameInputState.buttons[i].isRising = (!previousState && gameInputState.buttons[i].state);
  }
}

void WireRequestArray(int address, uint8_t* buffer, uint8_t amount);
void WireWriteRegister(int address, uint8_t reg, uint8_t value);
void WireWriteByte(int address, uint8_t value);

static float const    SensorMaximumReading = 512.0;
static float const    SensorMaximumAccel  = 9.81 * 4.0;
static uint8_t const  SensorAccelerometer = 0x1D;
static uint32_t const ShakeThreshold      = 16;
static float          ShakeAccumulator    = 0;

void ShakeInit()
{
  WireWriteRegister(SensorAccelerometer, 0x31, 1);
  WireWriteRegister(SensorAccelerometer, 0x2D, 1 << 3);
}

bool ShakeIsShaking()
{
  return ShakeAccumulator >= ShakeThreshold;
}

void ShakeTick()
{
  size_t const DataLength = 6;
  uint32_t data[DataLength] = { 0 };

  WireWriteByte(SensorAccelerometer, 0x32);
  WireRequestArray(SensorAccelerometer, data, DataLength);

  uint16_t xi = (data[1] << 8) | data[0];
  uint16_t yi = (data[3] << 8) | data[2];
  uint16_t zi = (data[5] << 8) | data[4];
  float x = *(int16_t*)(&xi) / SensorMaximumReading * SensorMaximumAccel;
  float y = *(int16_t*)(&yi) / SensorMaximumReading * SensorMaximumAccel;
  float z = *(int16_t*)(&zi) / SensorMaximumReading * SensorMaximumAccel;

  ShakeAccumulator = sqrt(x * x + y * y + z * z);
}
#include <Wire.h>

/**
   You need to use your own Instance of the TwoWire Object (instead of the standard `Wire`)
   because they communicate over the wrong pins!
*/
static TwoWire orbitWire(0);

void WireInit()
{
  orbitWire.begin();
}

void WireWriteByte(int address, uint8_t value)
{
  orbitWire.beginTransmission(address);
  orbitWire.write(value);
  orbitWire.endTransmission();
}

void WireWriteRegister(int address, uint8_t reg, uint8_t value)
{
  orbitWire.beginTransmission(address);
  orbitWire.write(reg);
  orbitWire.write(value);
  orbitWire.endTransmission();
}

/**
   WireRequestArray(int address, uint32_t* buffer, uint8_t amount)

   address - I2C Address of Chip
   buffer - Buffer to store data
   amount - Bytes of information to store!
*/
void WireRequestArray(int address, uint32_t* buffer, uint8_t amount)
{
  orbitWire.requestFrom(address, amount);
  do
  {
    while (!orbitWire.available());
    *(buffer++) = orbitWire.read();
  } while (--amount > 0);
}

