#include "spi_master.h"

Master::Master(unsigned int id, double current, double target) {
    this->motorID = id;
    this->currentAngle = current;
    this->targetAngle = target;
}

void Master::setup(int SS_PIN) {
    pinMode(SCK, OUTPUT);     // Put SCK, MOSI, SS pins into output mode
    pinMode(MOSI, OUTPUT);    // Put SCK, MOSI, SS pins into output mode
    pinMode(SS_PIN, OUTPUT);  // also put SCK, MOSI into LOW state, and SS into HIGH state.

    digitalWrite(SS_PIN, HIGH);  // ensure SLAVE stays high for now
    digitalWrite(SCK, LOW);
    digitalWrite(MOSI, LOW);

    SPI.begin();  // begin SPI

    SPI.setClockDivider(SPI_CLOCK_DIV8);  // Slow down the master a bit
}

void Master::setMotorID(unsigned int id) {  // motorID mutator
    this->motorID = id;
}

unsigned int Master::getMotorID(void) {  // motorID accessor
    return this->motorID;
}

void Master::setCurrentAngle(double current) {  // currentAngle mutator
    this->currentAngle = current;
}

double Master::getCurrentAngle(void) {  // currentAngle accessor
    return this->currentAngle;
}

void Master::setTargetAngle(double target) {  // targetAngle mutator
    this->targetAngle = target;
}

double Master::getTargetAngle(void) {  // targetAngle accessor
    return this->targetAngle;
}

void Master::setCRC(byte crc) {
    this->CRC = crc;
}

void Master::enable(int SS_PIN) {
    digitalWrite(SS_PIN, LOW);  // enable SS
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
}

void Master::disable(int SS_PIN) {
    digitalWrite(SS_PIN, HIGH);  // diable SS
    SPI.endTransaction();
}
