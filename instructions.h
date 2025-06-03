#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "registers.h"
#include "memory.h"
#include"globalvariable.h"
//function LC3 architectural phases
void SignExtension6(int16_t&);
void SignExtension9(int16_t&);
bool CheckConditions(uint16_t);
void setConditions(uint16_t);
 void fetch();
 void decode();
 void  evaluateAddress();
 void fetchOperands();
 void execute();
 void  store();
 bool isHalt();
#endif // INSTRUCTIONS_H
