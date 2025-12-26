#include "tok.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define TOK_MAX 64

ASM_Token ParseToken(const STRING buffer, int length) {
  ASM_Token out = {0};
  if (length == 1) {
    out.type = buffer[0];
  } else {
    out.value = malloc(++length);
    memcpy(out.value, buffer, length);

    if (isdigit(buffer[0]))
      out.type = ASM_TOK_LITERAL;
    else
      out.type = ASM_TOK_IDENTIFIER;
  }
  return out;
}

vector_ASM_Token FetchTokens(const STRING file_path) {
  FILE *file;
  fopen_s(&file, file_path, "rt");

  if (!file) {
    fprintf(stderr, "Failed to open file: %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  vector_ASM_Token tokens = MAKE_VECTOR(ASM_Token);

  ASM_Token token;

  char tok_buffer[TOK_MAX];
  int tok_length = 0;
  int C = fgetc(file);
  while (C != EOF) {
    if (isspace(C) && C != '\n') {
      C = fgetc(file);
      continue;
    }
    if (isalnum(C)) {
      tok_length = 0;
      do {
        tok_buffer[tok_length++] = C;
        C = fgetc(file);
      } while (isalnum(C));
      tok_buffer[tok_length] = 0;
    } else {
      tok_buffer[0] = C;
      tok_length = 1;
      C = fgetc(file);
    }

    token = ParseToken(tok_buffer, tok_length);

    PUSH(tokens, token);
  }
  return tokens;
}
