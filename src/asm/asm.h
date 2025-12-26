#pragma once

#include "asm/tok.h"
#include "defs.h"
#include <stdbool.h>
#include <stdint.h>

ENUM(ASM_BushLeafType,
     {ASM_LEAF_LABEL, ASM_LEAF_DIRECTIVE, ASM_LEAF_INSTRUCTION});

CLASS(ASM_BushLeaf) { ASM_BushLeafType type; };

CLASS(ASM_BushLeaf_Label) {
  ASM_BushLeaf base;
  STRING name;
};

ENUM(ASM_Petal_InstructionArgumentType,
     {
         ASM_ARGUMENT_IMMEDIATE,
         ASM_ARGUMENT_LABEL,
         ASM_ARGUMENT_REGISTER,
     } //
);

ENUM(ASM_ByteSize, {ASM_BYTE = 1, ASM_WORD = 2, ASM_DWORD = 4, ASM_QWORD = 8});

CLASS(ASM_Petal_InstructionArgument) {
  ASM_Petal_InstructionArgumentType type;
  ASM_ByteSize size;

  uintmax_t value;
  bool indirect;

  // arguments may be offset as such
  char operand;
  ASM_Petal_InstructionArgument *offset;
};

VECTOR_TYPE(ASM_Petal_InstructionArgument);

CLASS(ASM_BushLeaf_Instruction) {
  ASM_BushLeaf base;
  STRING name;
  vector_ASM_Petal_InstructionArgument arguments;
};

typedef ASM_BushLeaf *ASM_BushLeaf_PTR;

VECTOR_TYPE(ASM_BushLeaf_PTR);

vector_ASM_BushLeaf_PTR GenerateAsmBush(vector_ASM_Token *tokens);
