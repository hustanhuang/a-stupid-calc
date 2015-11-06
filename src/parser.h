#ifndef PARSER_H_
#define PARSER_H_

#include "defines.h"
#include "tokens.h"

int parse(const char *expr, tokenNode *infix);

#endif
