#ifndef MEMORY_H
#define MEMORY_H
#include <cstdint>
#include <vector>
class Memory
{
public:
    Memory();
    Memory(uint16_t);
    uint16_t readMemory(uint16_t) const;
    void writeMemory(uint16_t addr, uint16_t data);
    void resetMemory();

private:
    std::vector<uint16_t> memory;
};

#endif // MEMORY_H
