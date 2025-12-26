#pragma once

#include "defs.h"
#include <stdint.h>

ENUM(ASM_OperandSpec,
     {
         OPSIZE_BYTE = 0b1,
         OPSIZE_WORD = 0b10,
         OPSIZE_DWORD = 0b100,

         ASM_NO_OP = 0,
         ASM_MEM = 0b1000,
         ASM_REG = 0b10000,
         ASM_IMM = 0b100000,
         ASM_ADDR = 0b100000,
     } //
);

CLASS(ASM_Instruction) {
  STRING name; //
  uint8_t opcode;
  ASM_OperandSpec operands[2];
};

CLASS(ASM_Register) {
  STRING name;
  uint8_t opcode;
  ASM_OperandSpec size;
};

extern const ASM_Instruction INSTRUCTION_SET[];
extern const ASM_Register REGISTERS[];