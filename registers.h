#ifndef REGISTERS_H
#define REGISTERS_H
#include <cstdint>

class Registers
{
public:
    Registers();
    //getter
    uint16_t getPC() const;
    uint16_t getIR() const;
    uint16_t getCC() const;
    uint16_t getR(uint8_t) const;
    uint16_t getMAR() const;
    uint16_t getMDR() const;
   //setter
    void setPC(uint16_t);
    void setIR(uint16_t);
    void setCC(uint16_t);
    void setR(uint8_t, uint16_t);
    void setMAR(uint16_t);
    void setMDR(uint16_t);

    void resetRegisters();
private:
    uint16_t PC;
    uint16_t IR;
    uint16_t CC;
    uint16_t R[8];
    uint16_t MAR;
    uint16_t MDR;
};

#endif // REGISTERS_H
