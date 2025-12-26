#include "asm/encode.h"
#include "asm.h"
#include "asm/asm.h"
#include "instruc.h"

inline uint8_t arg_size_match(ASM_ByteSize arg, ASM_OperandSpec spec) {
  ASM_ByteSize spec_size;
  if (spec & ASM_OP_BYTE)
    spec_size = ASM_BYTE;
  else if (spec & ASM_OP_WORD)
    spec_size = ASM_WORD;
  else if (spec & ASM_OP_DWORD)
    spec_size = ASM_DWORD;
  else
    return 0;

  if (spec_size == arg)
    return 0;
  else if (spec_size > arg)
    return 1;
  else
    return -1;
}

bool arg_match(ASM_Petal_InstructionArgument *arg, ASM_OperandSpec spec) {
  if (arg->indirect && spec & ASM_MEM)
    return true;

  uint8_t match = arg_size_match(arg->size, spec);
  switch (arg->type) {
  case ASM_ARGUMENT_IMMEDIATE:
    if (spec & ASM_IMM && match >= 0)
      return true;
    break;
  case ASM_ARGUMENT_LABEL:
    if (spec & ASM_IMM && match >= 0)
      return true;
    break;
  case ASM_ARGUMENT_REGISTER:
    if (spec & ASM_REG && match == 0)
      return true;
    break;
  }
}

uint8_t find_instruction(ASM_BushLeaf_Instruction *ins) {
  for (uint16_t i = 0; i != NUM_INSTRUCTIONS; ++i) {
  }

  exit(EXIT_FAILURE);
}

void AssembleInstruction(ASM_BushLeaf_Instruction *ins, vector_uint8_t *out,
                         bool mark_labels) {
  uint8_t opcode = find_instruction(&ins);
}

vector_uint8_t AssembleBush(ASM_Bush *bush) {
  vector_uint8_t out = MAKE_VECTOR(uint8_t);

  for (size_t i = 0; i < bush->leaves.size; ++i) {
    if (bush->leaves.at(i)->type == ASM_LEAF_INSTRUCTION) {
      AssembleInstruction((ASM_BushLeaf_Instruction *)&bush->leaves.at(i), &out,
                          true);
    }
  }
  return out;
}