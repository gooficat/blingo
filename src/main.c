#include "main.h"
#include "asm/asm.h"
#include "asm/tok.h"
#include <stdio.h>
int main(void) {
  vector_ASM_Token tokens = FetchTokens("../tests/test.asm");

  vector_ASM_BushLeaf_PTR bush = GenerateAsmBush(&tokens);

  for (size_t i = 0; i < bush.size; ++i) {
    printf("%c\n", bush.at(i)->type);
  }
  return 0;
}
