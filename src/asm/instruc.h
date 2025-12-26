#pragma once

#include "defs.h"
#include <stdint.h>

ENUM(ASM_OperandSpec,
     {
         ASM_OP_BYTE = 0b1,
         ASM_OP_WORD = 0b10,
         ASM_OP_DWORD = 0b100,

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

ASM_Register *find_register(const char *name);
ASM_Instruction *find_instruction_name_only(const char *name);