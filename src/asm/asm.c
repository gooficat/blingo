#include "asm/asm.h"
#include "defs.h"

#include <stdio.h>

vector_ASM_BushLeaf_PTR GenerateAsmBush(vector_ASM_Token* tokens)
{
	vector_ASM_BushLeaf_PTR out = MAKE_VECTOR(ASM_BushLeaf_PTR);

	for (size_t i = 0; i != tokens->size; ++i)
	{
		if (tokens->at(i).value)
		{
			printf("%s\n", tokens->at(i).value);
		}
		else
		{
			printf("%c\n", tokens->at(i).type);
		}
	}

	return out;
}