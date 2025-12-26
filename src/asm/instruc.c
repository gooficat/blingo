#include "asm/instruc.h"

const ASM_Instruction INSTRUCTION_SET[] = {
    {"ADD", 0x00, {(ASM_REG | OPSIZE_BYTE), (ASM_REG | ASM_MEM | OPSIZE_BYTE)}},
};

const ASM_Register REGISTERS[] = {
    {"AX", 0x00, OPSIZE_WORD},
    {"CX", 0x01, OPSIZE_WORD},
    {"DX", 0x02, OPSIZE_WORD},
    {"BX", 0x03, OPSIZE_WORD},
};