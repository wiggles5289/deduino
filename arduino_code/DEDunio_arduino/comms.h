#ifndef comms_h
#define comms_h

#if defined(ARDUINO_DUE)
#define SERIAL_TIMEOUT 50 // too low of a value will cause displays to jump as connection is not fast enogth
#else
#define SERIAL_TIMEOUT 100 // too low of a value will cause displays to jump as connection is not fast enogth
#endif

#define BAUDRATE 9600 // base baud rate

#if defined(ARDUINO_UNO)
#define BAUDRATE_MULTIPLIER 3 // native USB serial - speed is irrlevent it's hardware controled but setting a common cap limit seems like a good idea
#else
#define BAUDRATE_MULTIPLIER 12 // Serial speed multiplier - 3 is a safe number for Ardiuno Uno on a USB hub, it is Hardcoded into the connector app, so don't change it.
#endif

#if defined(ARDUINO_DUE_NATIVE)
#define COM SerialUSB
#else
#define COM Serial
#endif


////////// Serial Operation Functions //////////////
void initSerial() {
  COM.begin(BAUDRATE * BAUDRATE_MULTIPLIER);
  COM.setTimeout(SERIAL_TIMEOUT);
}

//Sleep main logic (every read is reporting to this function)
bool gotoSleep = false;
#define TIMED_OUT (millis()-last_comm) > (SLEEP_TIMER * 1000)
unsigned long last_comm = millis();

void commsCheck(short report){
  if (report > 0) {
    last_comm = millis();
    gotoSleep = false;
    return;
  } else if (TIMED_OUT) {
    gotoSleep = true;
  }
}
#endif


