#include "memory.h"

Memory::Memory()
{
    memory.resize(0);
}
Memory::Memory(uint16_t size)
{
    memory.resize(size);
}
uint16_t Memory::readMemory(uint16_t addr) const
{
    return memory[addr];
}
void Memory::writeMemory(uint16_t addr, uint16_t data)
{
    memory[addr] = data;
}

void Memory:: resetMemory(){
    std::fill(memory.begin(), memory.end(), 0);
}
