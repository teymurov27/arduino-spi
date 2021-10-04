#include "spi_slave.h"

Slave::Slave(unsigned int id, double current, double target) {
    this->motorID = id;
    this->currentAngle = current;
    this->targetAngle = target;
}

unsigned int Slave::getMotorID(void) {
    return this->motorID;
}

double Slave::getCurrentAngle(void) {
    return this->currentAngle;
}

double Slave::getTargetAngle(void) {
    return this->targetAngle;
}

byte Slave::getCRC(void) {
    return this->CRC;
}

void Slave::setup() {
    pinMode(MISO, OUTPUT);  // have to send on master in so it set as output.

    SPCR = (1 << SPE);      // turn on SPI in slave mode.
    SPI.attachInterrupt();  // turn on interrupt.
}
