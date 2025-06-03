#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include "registers.h"
#include <cstdint>
#include "memory.h"
#include <QFile>

extern Registers registers;
extern uint16_t ir;
extern uint16_t nzp;
extern uint16_t dr;
extern uint16_t sr1;
extern uint16_t address;
extern uint16_t v_sr1;
extern uint16_t v_sr2;
extern uint16_t GateALU;
extern uint16_t value;
extern uint16_t sr2;
extern uint16_t imm5;
extern int16_t offset9;
extern int16_t offset6;
extern int16_t offset11;
extern uint16_t base_r;
extern uint16_t flag;
extern uint16_t opcode;
extern uint16_t sr;
extern int index;
extern Memory memory;
extern QFile Binaryfile;
extern int manager;
#endif // GLOBALVARIABLE_H
