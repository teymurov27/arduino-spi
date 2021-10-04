#include <spi_slave.h>

Slave slave;
volatile bool haveData;

void setup() {
    Serial.begin(9600);
    slave.setup();
}
void loop() {
    if (haveData) {
        haveData = false;
        if (calc_CRC(slave) == slave.getCRC()) {
            Serial.println(slave.getCurrentAngle());
            Serial.println(slave.getTargetAngle());
            Serial.println(slave.getMotorID());
            Serial.println(calc_CRC(slave));
        }
    }
}

// SPI interrupt routine
ISR(SPI_STC_vect) {
    while ((SPSR | (1 << SPIF)) == 0x00)
        ;

    read(slave);
    haveData = true;
}