#include <SoftwareSerial.h>
struct Package {
    double alchohol;
    double ammonia;
};

void
sendPackage(double alchohol, double ammonia, SoftwareSerial Serial) {
    Serial.print(alchohol, DEC);
    Serial.print(" ");
    Serial.print(ammonia, DEC);
    Serial.println("");
}