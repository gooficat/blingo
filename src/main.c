#include "main.h"
#include "asm/asm.h"
#include "asm/tok.h"
#include <stdio.h>
int main(void) {
  vector_ASM_Token tokens = FetchTokens("../tests/test.asm");

  for (size_t i = 0; i < tokens.size; ++i) {
    if (!tokens.at(i).value)
      printf("%c\n", tokens.at(i).type);
    else
      printf("%s\n", tokens.at(i).value);
  }

  vector_ASM_BushLeaf_PTR bush = GenerateAsmBush(&tokens);

  PrintBush(bush);

  return 0;
}
