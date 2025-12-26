#pragma once
#include "defs.h"

ENUM(ASM_TokType,
	 {
		 ASM_TOK_EOF = '\0',
		 ASM_TOK_EOL = '\n',

		 ASM_TOK_SQUARE_L = '[',
		 ASM_TOK_SQUARE_R = ']',

		 ASM_TOK_PAREN_L = '(',
		 ASM_TOK_PAREN_R = ')',

		 ASM_TOK_LITERAL,
		 ASM_TOK_IDENTIFIER,

		 ASM_TOK_COLON = ':',
		 ASM_TOK_SEMI = ';',
		 ASM_TOK_COMMA = ',',

		 ASM_TOK_ADD = '+',
		 ASM_TOK_SUB = '-',
		 ASM_TOK_MUL = '*',
		 ASM_TOK_DIV = '/',
		 ASM_TOK_MOD = '%',
		 ASM_TOK_DOLLAR = '$',
	 });

CLASS(ASM_Token)
{
	ASM_TokType type;
	STRING value;
};

VECTOR_TYPE(ASM_Token);

vector_ASM_Token FetchTokens(const STRING file_path);
