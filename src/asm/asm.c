#include "asm/asm.h"
#include "asm/instruc.h"
#include "asm/tok.h"
#include "defs.h"
#include "instruc.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASM_Petal_InstructionArgument parse_imm(vector_ASM_Token *tokens, size_t *i) {
  ASM_Petal_InstructionArgument arg = {0};
  arg.type = ASM_ARGUMENT_IMMEDIATE;
  arg.value = ullfromstr(tokens->at(*i).value);
  ++(*i);
  return arg;
}

ASM_Petal_InstructionArgument parse_alpha(vector_ASM_Token *tokens, size_t *i) {
  ASM_Petal_InstructionArgument arg = {0};

  ASM_Register *reg = find_register(tokens->at(*i).value);
  if (reg) {
    arg.type = ASM_ARGUMENT_REGISTER;
    arg.value = reg->opcode;
  } else {
    arg.type = ASM_ARGUMENT_LABEL;
    printf("label %s\n", tokens->at(*i).value);
    // todo: put the label value on the operand. search the current working unit
    // for label match
  }
  ++(*i);
  return arg;
}

ASM_Petal_InstructionArgument parse_indir(vector_ASM_Token *tokens, size_t *i) {
  ASM_Petal_InstructionArgument arg = {0};
  arg.indirect = true;
  ASM_Petal_InstructionArgument *current = &arg;
  for (;;) {
    ++(*i);
    if (tokens->at(*i).type == ASM_TOK_LITERAL) {
      current->type = ASM_ARGUMENT_IMMEDIATE;
      // remember: there is an indirection argument
      // that decides how this works. for
      // indirection perhaps there is no difference
      // between "memory" and "immediate"
      *current = parse_imm(tokens, i);
      // possible thing to add next: multiple degree
      // indirection for other encoding backends
      if (tokens->at(*i).type != ASM_TOK_SQUARE_R) {
        int op = tokens->at(*i).type;
        current->operand = op;
        current->offset = malloc(sizeof(ASM_Petal_InstructionArgument));
        current = current->offset;
      } else {
        current->operand = 0;
        break;
      }
    } else {
    }
  }
  ++(*i);
  return arg;
}

ASM_BushLeaf_PTR parse_expression(vector_ASM_Token *tokens, size_t *i_) {
  ASM_BushLeaf_Instruction *out = NEW(ASM_BushLeaf_Instruction, {0});
  size_t i = *i_;
  out->base.type = ASM_LEAF_INSTRUCTION;

  out->name = copystr(tokens->at(i).value);

  out->arguments = MAKE_VECTOR(ASM_Petal_InstructionArgument);

  ++i;
  printf("Starting at %c %s\n", tokens->at(i).type, tokens->at(i).value);
  while (i < tokens->size) {
    printf("parsing for %s; %c: '%s'\ni is %llu\n", out->name,
           tokens->at(i).type, tokens->at(i).value ? tokens->at(i).value : "",
           i);
    switch (tokens->at(i).type) {
    case ASM_TOK_LITERAL:
      PUSH(out->arguments, parse_imm(tokens, &i));
      break;
    case ASM_TOK_SQUARE_L:
      PUSH(out->arguments, parse_indir(tokens, &i));
      break;
    case ASM_TOK_IDENTIFIER:
      PUSH(out->arguments, parse_alpha(tokens, &i));
      break;
    default: {
      printf("of type %c", tokens->at(i).type);
      ++i;
      goto breakout;
    }
    }
    printf("now of type %c", tokens->at(i).type);
    if (tokens->at(i).type != ASM_TOK_COMMA)
      goto breakout;
    else {
      ++i;
    }
  }
breakout:;
  printf("Ending at %c %s\n", tokens->at(i - 1).type, tokens->at(i - 1).value);

  *i_ = i;
  return out;
}

vector_ASM_BushLeaf_PTR GenerateAsmBush(vector_ASM_Token *tokens) {
  vector_ASM_BushLeaf_PTR out = MAKE_VECTOR(ASM_BushLeaf_PTR);

  size_t i = 0;
  while (i < tokens->size) {
    ASM_BushLeaf_PTR leaf;
    switch (tokens->at(i).type) {
    case ASM_TOK_IDENTIFIER:
      if (tokens->at(i + 1).type == ASM_TOK_COLON) {
        leaf = NEW( //
            ASM_BushLeaf_Label,
            {
                .base = {ASM_LEAF_LABEL},
                .name = copystr(tokens->at(i).value),
            } //
        );
        i += 2;
      } else {
        leaf = parse_expression(tokens, &i);
      }
      break;
    case ASM_TOK_EOL:
      continue;
    default:
      fprintf(stderr, "Error: unexpected token '%c'. i is %llu\n",
              tokens->at(i).type, i);
      exit(EXIT_FAILURE);
    }
    PUSH(out, leaf);
  }

  return out;
}

void PrintBushI(vector_ASM_BushLeaf_PTR *bush, size_t *i_i) {
  size_t i = *i_i;
  for (i = 0; i != bush->size; ++i) {
    switch (bush->at(i)->type) {
    case ASM_LEAF_INSTRUCTION: {
      ASM_BushLeaf_Instruction *instruction =
          (ASM_BushLeaf_Instruction *)bush->at(i);
      printf("instruction: '%s' with %llu args:\n", instruction->name,
             instruction->arguments.size);
      for (uint8_t i = 0; i < instruction->arguments.size; i++) {
        printf("\ttype: %i, val: %llu\n", instruction->arguments.at(i).type,
               instruction->arguments.at(i).value);
      }
    } break;
    case ASM_LEAF_LABEL: {
      ASM_BushLeaf_Label *label = (ASM_BushLeaf_Label *)bush->at(i);
      printf("label: %s\n", label->name);
    } break;
    case ASM_LEAF_DIRECTIVE:
      break;
    }
  }
out:;
  *i_i = i;
}
