#ifndef _CODE_GENERATOR_H
#define _CODE_GENERATOR_H

#include <stdio.h>
#include <stdbool.h>

#include "scanner.h"
#include "symbol_table.h"
#include "str.h"

typedef enum {
    I_MOVE,
    I_CREATEFRAME,
    I_PUSHFRAME,
    I_POPFRAME,
    I_DEFVAR,
    I_CALL,
    I_RETURN,

    I_PUSHS,
    I_POPS,
    I_CLEARS,

    I_ADD,
    I_SUB,
    I_MUL,
    I_DIV,
    I_IDIV,

    I_ADDS,
    I_SUBS,
    I_MULS,
    I_DIVS,
    I_IDIVS,

    I_LT,
    I_GT,
    I_EQ,
    I_LTS,
    I_GTS,
    I_EQS,

    I_AND,
    I_OR,
    I_NOT,
    I_ANDS,
    I_ORS,
    I_NOTS,

    I_INT2FLOAT,
    I_FLOAT2INT,
    I_INT2CHAR,
    I_STRI2INT,
    I_INT2FLOATS,
    I_FLOAT2INTS,
    I_INT2CHARS,
    I_STRI2INTS,

    I_READ,
    I_WRITE,

    I_CONCAT,
    I_STRLEN,
    I_GETCHAR,
    I_SETCHAR,

    I_TYPE,

    I_LABEL,
    I_JUMP,
    I_JUMPIFEQ,
    I_JUMPIFNEQ,
    I_JUMPIFEQS,
    I_JUMPIFNEQS,
    I_EXIT,

    I_BREAK,
    I_DPRINT,

    I_COMMENT,

}instructions;

#endif