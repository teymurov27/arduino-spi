#ifndef spi_master_H
#define spi_master_H

#include <Arduino.h>
#include <SPI.h>

class Master {
   public:
    explicit Master(unsigned int id = 0, double current = 0, double target = 0);
    void setup(int SS_PIN);
    void setMotorID(unsigned int id);
    unsigned int getMotorID(void);
    void setCurrentAngle(double current);
    double getCurrentAngle(void);
    void setTargetAngle(double target);
    double getTargetAngle(void);
    void setCRC(byte crc);

    void enable(int SS_PIN);
    void disable(int SS_PIN);

   private:
    unsigned int motorID;
    double currentAngle;
    double targetAngle;
    byte CRC;
};

template <typename A_Type>
unsigned int write(const A_Type& value) {
    const byte* p = (const byte*)&value;  // const pointer to byte macro. (const byte*) written like this because it is macro and can not create a pointer without casting.
    unsigned int i;
    for (i = 0; i < sizeof value; ++i) {
        SPI.transfer(*p++);     // dereferencing the pointer and transferring pointed value.
        delayMicroseconds(20);  // it turns out without delay unexpected behaviour happens as SPI freezes, so it is crucial to include microdelay of 20.
    }
    return i;
}

template <typename A_Type>
unsigned int calc_CRC(A_Type& targetStructure) {
    byte* addr = (byte*)&targetStructure;                // byte is typedef defined macro and you can not create a pointer to macro without casting.
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
                              // 0x8C = 10001100 and this corresponds to CRC = X8 + X5 + X4 + 1.
            inbyte >>= 1;
        }
    }
    return crc;
}

#endif
