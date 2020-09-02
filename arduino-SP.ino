#include "MsTimer2.h"
#include "SAF.h"
#include <Wire.h>
#include <SoftwareSerial.h>

struct Package {
    double alchohol;
    double ammonia;
};

SoftwareSerial softSerial(2, 4);

const int SAMPLE_RATE = 10;

const int PIN_ALCHOHOL = A0;
Signal<SAMPLE_RATE * 10> alchohol;
const int PIN_NH3 = A1;
Signal<SAMPLE_RATE * 10> ammonia;

void
ISRMsTimer2() {
  DSPUpdate(alchohol, (unsigned short)analogRead(PIN_ALCHOHOL));
  DSPUpdate(ammonia, (unsigned short)analogRead(PIN_NH3));
}

void
transmissionEvent() {
  Package pack;
  pack.alchohol = SAFAverage(alchohol).current;
  pack.ammonia = SAFAverage(ammonia).current;
  for(int i = 0; i < sizeof(Package); i++) {
    Serial.write(*((char *)(&pack) + i));
  }
}

void
setup() {
  Serial.begin(115200);
  softSerial.begin(9600);
  delay(10);
  
  DSPinit(alchohol);
  DSPinit(ammonia);
  
  MsTimer2::set(1000 / SAMPLE_RATE, ISRMsTimer2);
  MsTimer2::start();

  Wire.begin(0x04);
  Wire.onRequest(transmissionEvent);
}

void
loop() {
}
