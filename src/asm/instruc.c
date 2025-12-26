#include "asm/instruc.h"
#include "defs.h"
#include <string.h>

const ASM_Instruction INSTRUCTION_SET[] = {
    {"add", 0x00, {(ASM_REG | ASM_OP_BYTE), (ASM_REG | ASM_MEM | ASM_OP_BYTE)}},
};
const uint16_t NUM_INSTRUCTIONS =
    sizeof(INSTRUCTION_SET) / sizeof(INSTRUCTION_SET[0]);

const ASM_Register REGISTERS[] = {
    {"ax", 0x00, ASM_OP_WORD},
    {"cx", 0x01, ASM_OP_WORD},
    {"dx", 0x02, ASM_OP_WORD},
    {"bx", 0x03, ASM_OP_WORD},
};

const uint8_t NUM_REGISTERS = sizeof(REGISTERS) / sizeof(REGISTERS[0]);

ASM_Register *find_register(const char *name) {

  for (uint8_t i = 0; i != NUM_REGISTERS; ++i)
    if (!strcmp(name, REGISTERS[i].name))
      return &REGISTERS[i];

  return NULL;
}

ASM_Instruction *find_instruction_name_only(const char *name) {

  for (uint8_t i = 0; i != NUM_INSTRUCTIONS; ++i)
    if (!strcmp(name, INSTRUCTION_SET[i].name))
      return &INSTRUCTION_SET[i];

  return NULL;
}