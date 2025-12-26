#include "main.h"
#include "asm/asm.h"
#include "asm/encode.h"
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

  ASM_Bush bush = GenerateAsmBush(&tokens);

  vector_uint8_t bytes = AssembleBush(&bush);

  FILE *f;
  fopen_s(&f, "../tests/test.bin", "rt");
  fwrite(bytes.data, 1, bytes.size, f);

  PrintBush(bush);

  return 0;
}
