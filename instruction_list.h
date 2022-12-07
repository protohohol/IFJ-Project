#ifndef INSTRUCTION_LIST
#define INSTRUCTION_LIST

#include <stdio.h>
#include <stdbool.h>

#include "scanner.h"
#include "symbol_table.h"
#include "str.h"
#include "symstack.h"

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

    I_DEFAULT,

} instructions;

typedef enum {
    F_DEFAULT,
    F_GF,       //global frame
    F_LF,       //local frame
    F_TF,       //temporary frame   
} frame_type;

typedef struct {
    string out;
    char* value;
    data_type type;
    frame_type frame;
} operand_t;

typedef struct {
    operand_t operand_1;
    operand_t operand_2;
    operand_t result;
    instructions operator;
} taCode;

typedef struct DLLElement{
    taCode data;
    struct DLLElement *previousElement;
    struct DLLElement *nextElement;
} *DLLElementPtr;

typedef struct {
    DLLElementPtr firstElement;
    DLLElementPtr lastElement;
    DLLElementPtr activeElement;
} DLList;

void DLL_Init(DLList* list);

void DLL_Dispose(DLList* list);

void DLL_InsertFirst(DLList* list, taCode* data);

void DLL_InsertLast(DLList* list, taCode* data);

void DLL_First(DLList* list);

void DLL_Last(DLList* list);

void DLL_GetFirst(DLList* list, taCode* dataPtr);

void DLL_GetLast(DLList* list, taCode* dataPtr);

void DLL_DeleteFirst(DLList* list);

void DLL_DeleteLast(DLList* list);

void DLL_DeleteAfter(DLList* list);

void DLL_DeleteBefore(DLList* list);

void DLL_InsertAfter(DLList* list, taCode* data);

void DLL_InsertBefore(DLList* list, taCode* data);

void DLL_GetValue(DLList* list, taCode* dataPtr);

void DLL_SetValue(DLList* list, taCode* data);

void DLL_Next(DLList* list);

void DLL_Previous(DLList* list);

int DLL_IsActive(DLList* list);

void init_data(taCode* target);

bool set_operand_value(operand_t* target, char* source);

void free_data_value(taCode* target);

bool insert_data(taCode* target, taCode* source);

void clear_data(taCode* source);

#endif