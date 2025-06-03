#include "instructions.h"

void fetch()
{
    uint16_t pc = registers.getPC();
    registers.setMAR(pc);
    registers.setMDR(memory.readMemory(pc));
    registers.setIR(registers.getMDR());
    registers.setPC(pc + 1);
}

void decode()
{
    // Extract opcode
    opcode = (registers.getIR() >> 12) & 0xF;

    switch (opcode)
    {
    // BR
    case 0x0:
        ir = registers.getIR();
        nzp = (ir >> 9) & 0x7; // Extract nzp bits
        // Extract PCoffset9
        offset9 = ir & 0x1FF;
        SignExtension9(offset9);
        break;
        // ADD
    case 0x1:
        dr = (registers.getIR() >> 9) & 0x7;     // Destination register
        sr1 = (registers.getIR() >> 6) & 0x7;   // Source register 1
        flag = (registers.getIR() >> 5) & 0x1; // Immediate Or Not
        // Immediate
        if (flag)
        {
            imm5 = registers.getIR() & 0x1F; // Extract immediate
            if (imm5 & 0x10)// Sign extension
            {
                imm5 |= 0xFFE0;
            }
        }
        // Register
        else
        {
            sr2 = registers.getIR() & 0x7; // Source register 2
        }
        break;
        // LD
    case 0x2:
        dr = (registers.getIR() >> 9) & 0x0007;
        offset9 = registers.getIR() & 0x01FF;
        SignExtension9(offset9);
        break;
        //ST
    case 0x3:
        sr = (registers.getIR() >> 9) & 0x7;
        offset9 = registers.getIR() & 0x1FF;
        SignExtension9(offset9);
        break;
        //JSR & JSRR
    case 0x4:
        flag = (registers.getIR() >> 11) & 0x1;
        //JSR
        if (flag){
            offset11 = registers.getIR() & 0x7FF; // Extract offset11
            if (offset11 & 0x0400) // Sign extension
            {
                offset11 |= 0xF800;
            }
        }
        //JSRR
        else{
            base_r = (registers.getIR() >> 6) & 0x7;
        }
        break;
        //AND
    case 0x5:
        dr = (registers.getIR() >> 9) & 0x7;
        sr1 = (registers.getIR() >> 6) & 0x7;
        flag = (registers.getIR() >> 5) & 0x1;
        // Immediate mode
        if (flag) {
            imm5 = registers.getIR() & 0x1F;
            if (imm5 & 0x10)// Sign extension
            {
                imm5 |= 0xFFE0;
            }
        }
        // Register
        else{
            sr2 = registers.getIR() & 0x7; // Source register 2
        }
        break;
        // LDR
    case 0x6:
        offset6 = registers.getIR() & 0x003F;
        SignExtension6(offset6);
        base_r = (registers.getIR() >> 6) & 0x0007;
        dr = (registers.getIR() >> 9) & 0x0007;
        break;
        //STR
    case 0x7:
        sr = (registers.getIR() >> 9) & 0x7;
        base_r = (registers.getIR() >> 6) & 0x7;
        offset6 = registers.getIR() & 0x3F;
        SignExtension6(offset6);
        break;
        //NOT
    case 0x9:
        dr = (registers.getIR() >> 9) & 0x7; // destination register
        sr = (registers.getIR() >> 6) & 0x7; // source register
        break;
        //LDI
    case 0xA:
        dr = (registers.getIR() >> 9) & 0x7;
        offset9 = registers.getIR() & 0x01FF;
        SignExtension9(offset9);
        break;
        //STI
    case 0xB:
        sr = (registers.getIR() >> 9) & 0x7;
        offset9 = registers.getIR() & 0x1FF;
        SignExtension9(offset9);
        break;
        //RET & JMP
    case 0xC:
        //JMP
        if (((registers.getIR() >> 6) & 0x7) != 7)
            base_r = (registers.getIR() >> 6) & 0x7;
        break;
        //LEA
    case 0xE:
        dr = (registers.getIR() >> 9) & 0x0007;
        offset9 = registers.getIR() & 0x1FF;
        SignExtension9(offset9);
        break;
    default:
        //unsupported opcode
        break;
    }
}

void evaluateAddress()
{
    switch (opcode) {
    //BR
    case 0x0:
        address=registers.getPC() + offset9;
        break;
        //LD
    case 0x2:
        address = registers.getPC() + offset9;
        registers.setMAR(address);
        break;
        //ST
    case 0x3:
        address = registers.getPC() + offset9;
        break;
        //JSR & JSRR
    case 0x4:
        //JSR
        if (flag){
            address=registers.getPC() + offset11;
            //JSRR
        }else{
            address=registers.getR(base_r);
        }
        break;
        //LDR
    case 0x6:
        address = registers.getR(base_r) + offset6;
        registers.setMAR(address);
        break;
        //STR
    case 0x7:
        address = registers.getR(base_r) + offset6;
        break;
        //LDI
    case 0xA:
        address = registers.getPC() + offset9;
        registers.setMAR(address);
        address = memory.readMemory(registers.getMAR());
        registers.setMAR(address);
        break;
        //STI
    case 0xB:
        address = registers.getPC() + offset9;
        break;
        //RET & JMP
    case 0xC:
        //RET
        if (((registers.getIR() >> 6) & 0x7) == 7) {
            address=registers.getR(7);
        }
        //JMP
        else {
            address=registers.getR(base_r);
        }
        break;
        //LEA
    case 0xE:
        address = registers.getPC() + offset9;
        break;
    }
}

void fetchOperands()
{
    switch (opcode)
    {
    //ADD
    case 0x1:
        v_sr1 = registers.getR(sr1);
        v_sr2 = registers.getR(sr2);
        break;
        //LD
    case 0x2:
        registers.setMDR(memory.readMemory(registers.getMAR()));
        break;
        //ST
    case 0x3:
        value=registers.getR(sr);
        break;
        //AND
    case 0x5:
        v_sr1 = registers.getR(sr1);
        v_sr2 = registers.getR(sr2);
        break;
        //LDR
    case 0x6:
        registers.setMDR(memory.readMemory(registers.getMAR()));
        break;
        //STR
    case 0x7:
        value=registers.getR(sr);
        break;
        //NOT
    case 0x9:
        v_sr1=registers.getR(sr);
        break;
        //LDI
    case 0xA:
        registers.setMDR(memory.readMemory(registers.getMAR()));
        break;
        //STI
    case 0xB:
        value=registers.getR(dr);
        break;
    }
}

void execute()
{
    switch (opcode)
    {
    // ADD
    case 0x1:
        // Immediate
        if (flag)
        {
            GateALU=v_sr1 + static_cast<int16_t>(imm5);
        }
        // Register
        else {
            GateALU=v_sr1 + v_sr2;
        }
        break;
        // AND
    case 0x5:
        // Immediate
        if (flag)
        {
            GateALU = registers.getR(sr1) & static_cast<int16_t>(imm5);
        }
        // Register
        else
        {
            GateALU = registers.getR(sr1) & registers.getR(sr2);
        }
        break;
        //NOT
    case 0x9:
        GateALU=~v_sr1;
        break;
    }
}

void store()
{
    switch (opcode)
    {
    // BR
    case 0x0:
    {
        uint16_t cc = registers.getCC();
        // Check if any of the conditions are met
        if (CheckConditions(cc))
        {
            registers.setPC(address);
        }
    }
        break;
        // ADD
    case 0x1:
    {
        registers.setR(dr, GateALU);
        uint16_t result = registers.getR(dr);
        setConditions(result);
    }
        break;
        // LD
    case 0x2:
    {
        uint16_t value = registers.getMDR();
        registers.setR(dr, value);
        setConditions(value);
    }
        break;
        //ST
    case 0x3:
    {
        registers.setMAR(address);
        registers.setMDR(value);
        index = registers.getMAR();
        memory.writeMemory(registers.getMAR(), registers.getMDR());
    }
        break;
        // JSR JSRR
    case 0x4:
    {
        uint16_t currentPC = registers.getPC(); // Get the current PC
        // Store the current PC in R7
        registers.setR(7, currentPC);
        registers.setPC(address); // Update PC with the offset
    }
        break;
        // AND
    case 0x5:
    {
        registers.setR(dr, GateALU);
        uint16_t result = registers.getR(dr);
        setConditions(result);
    }
        break;
        //LDR
    case 0x6:
    {
        uint16_t value = registers.getMDR();
        registers.setR(dr, value);
        setConditions(value);
    }
        break;
        //STR
    case 0x7:
    {
        registers.setMAR(address);
        registers.setMDR(value);
        memory.writeMemory(registers.getMAR(), registers.getMDR());
        index = registers.getMAR();
    }
        break;
        // NOT
    case 0x9:
    {
        registers.setR(dr, GateALU);
        uint16_t result = registers.getR(dr);
        setConditions(result);
    }
        break;
        //LDI
    case 0xA:
    {
        uint16_t value = registers.getMDR();
        registers.setR(dr, value);
        setConditions(value);
    }
        break;
        //STI
    case 0xB:
    {
        registers.setMAR(address);
        registers.setMDR(value);
        memory.writeMemory(memory.readMemory(registers.getMAR()), registers.getMDR());
        index=memory.readMemory(registers.getMAR());
    }
        break;
        //RET & JMP
    case 0xC:
    {
        registers.setPC(address);
    }
        break;
        // LEA
    case 0xE:
    {
        registers.setR(dr, address);
    }
        break;
    default:
        // Handle unsupported opcode
        break;
    }
}

void SignExtension6(int16_t& Offset6){
    if (offset6 & 0x0020)
    {
        offset6 |= 0xFFC0;
    }
}

void SignExtension9(int16_t& Offset9){
    if (offset9 & 0x100)
    {
        offset9 |= 0xFE00;
    }
}

bool CheckConditions(uint16_t cc){
    return ((nzp & 0x4) && (cc & 0x4)) ||((nzp & 0x2) && (cc & 0x2)) ||((nzp & 0x1) && (cc & 0x1));
}

void setConditions(uint16_t result){
    if (result == 0)
    {
        registers.setCC(0x02); // Zero
    }
    else if (result >> 15)
    {
        registers.setCC(0x04); // Negative
    }
    else
    {
        registers.setCC(0x01); // Positive
    }
}

bool isHalt(){
    return (registers.getMDR() == 0xF025);
}
