#ifndef spi_slave_H
#define spi_slave_H

#include <Arduino.h>
#include <SPI.h>

class Slave {
   public:
    explicit Slave(unsigned int id = 0, double current = 0, double target = 0);
    unsigned int getMotorID(void);
    double getCurrentAngle(void);
    double getTargetAngle(void);
    byte getCRC(void);

    void setup();

   private:
    unsigned int motorID;
    double currentAngle;
    double targetAngle;
    byte CRC;
};

template <typename A_Type>
unsigned int read(A_Type& value) {
    byte* p = (byte*)&value;
    unsigned int i;
    *p++ = SPDR;  // get first byte from SPI Data Register.
    for (i = 1; i < sizeof value; ++i)
        *p++ = SPI.transfer(0);  // Send dummy data everytime receiving byte.
    return i;
}

template <typename A_Type>
unsigned int calc_CRC(A_Type& targetStructure) {
    byte* addr = (byte*)&targetStructure;                // Pretend its really a pointer to a byte instead, the reason is byte is typedef defined macro and you can not create a pointer to macro without casting.
    byte crc = 0b0;                                      // 0b0 is 0 but in binary form.
    long len = (sizeof targetStructure - sizeof(byte));  // The last byte of structure is always the CRC.
                                                         // so ignore the last byte of the structure.
    while (len--) {
        byte inbyte = *addr++;
        for (byte i = 8; i; --i) {
            byte mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix)
                crc ^= 0x8C;  // Our polynomial function in hexadecimal format.
                              // 0x8C = 0b10001100 and this corresponds to CRC = X8 + X5 + X4 + 1.
            inbyte >>= 1;
        }
    }
    return crc;
}

#endif
