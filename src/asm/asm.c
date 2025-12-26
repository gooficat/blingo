#include "asm/asm.h"
#include "asm/tok.h"
#include "defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASM_BushLeaf_PTR parse_expression(vector_ASM_Token *tokens, size_t *i) {
  ASM_BushLeaf_Instruction *out = NEW(ASM_BushLeaf_Instruction, {0});

  out->name = copystr(tokens->at(*i).value);

  // todo parse args

  return out;
}

vector_ASM_BushLeaf_PTR GenerateAsmBush(vector_ASM_Token *tokens) {
  vector_ASM_BushLeaf_PTR out = MAKE_VECTOR(ASM_BushLeaf_PTR);

  for (size_t i = 0; i != tokens->size; ++i) {
    ASM_BushLeaf_PTR leaf;
    switch (tokens->at(i).type) {
    case ASM_TOK_IDENTIFIER:
      if (tokens->at(i + 1).type == ASM_TOK_COLON) {
        leaf = NEW(             //
            ASM_BushLeaf_Label, //
            {
                .base = {ASM_LEAF_LABEL},
                .name = copystr(tokens->at(i).value),
            });
        ++i;
      } else {
        leaf = parse_expression(tokens, &i);
      }
      break;
    case ASM_TOK_EOL:
      continue;
    default:
      fprintf(stderr, "Error: unexpected token '%c'\n", tokens->at(i).type);
      exit(EXIT_FAILURE);
    }
    PUSH(out, leaf);
  }

  return out;
}