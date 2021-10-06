#include <spi_master.h>

#define SLAVE_PIN 8

Master master;

void setup() {
    master.setup(SLAVE_PIN);
    master.setCurrentAngle(180);
    master.setTargetAngle(325);
    master.setMotorID(225);
    master.setCRC(calc_CRC(master));
}

void loop() {
    master.enable(SLAVE_PIN);
    write(master);
    master.disable(SLAVE_PIN);

    delay(1000);  // works perfectly with desired delay
}