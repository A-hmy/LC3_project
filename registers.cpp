#include "registers.h"

Registers::Registers()
{
    PC = 0;
    IR = 0;
    CC = 0;
    MAR = 0;
    MDR = 0;
    for (int i = 0; i <= 7; ++i) {
        R[i] = 0;
    }
}
void Registers::resetRegisters(){
    PC = 0;
    IR = 0;
    CC = 0;
    MAR = 0;
    MDR = 0;
    for (int i = 0; i <= 7; ++i) {
        R[i] = 0;
    }
}
uint16_t Registers::getPC() const
{
    return PC;
}
uint16_t Registers::getIR() const
{
    return IR;
}
uint16_t Registers::getCC() const
{
    return CC;
}
uint16_t Registers::getR(uint8_t index) const
{
        return R[index];
}
uint16_t Registers::getMAR() const
{
    return MAR;
}
uint16_t Registers::getMDR() const
{
    return MDR;
}

void Registers::setPC(uint16_t addr)
{
    PC = addr;
}
void Registers::setIR(uint16_t value)
{
    IR = value;
}
void Registers::setCC(uint16_t nzp)
{
    CC = nzp;
}
void Registers::setR(uint8_t index, uint16_t value)
{
        R[index] = value;
}
void Registers::setMAR(uint16_t value)
{
    MAR = value;
}
void Registers::setMDR(uint16_t data)
{
    MDR = data;
}
