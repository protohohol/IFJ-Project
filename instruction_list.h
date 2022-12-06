#ifndef INSTRUCTION_LIST
#define INSTRUCTION_LIST

#include <stdio.h>
#include <stdbool.h>

#include "scanner.h"
#include "symbol_table.h"
#include "str.h"
#include "code_generator.h"

typedef enum {
    F_GF,   //global frame
    F_LF,   //local frame
    F_TF,   //temporary frame
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

void DLL_InsertFirst(DLList* list, taCode data);

void DLL_InsertLast(DLList* list, taCode data);

void DLL_First(DLList* list);

void DLL_Last(DLList* list);

void DLL_GetFirst(DLList* list, taCode* dataPtr);

void DLL_GetLast(DLList* list, taCode* dataPtr);

void DLL_DeleteFirst(DLList* list);

void DLL_DeleteLast(DLList* list);

void DLL_DeleteAfter(DLList* list);

void DLL_DeleteBefore(DLList* list);

void DLL_InsertAfter(DLList* list, taCode data);

void DLL_InsertBefore(DLList* list, taCode data);

void DLL_GetValue(DLList* list, taCode* dataPtr);

void DLL_SetValue(DLList* list, taCode data);

void DLL_Next(DLList* list);

void DLL_Previous(DLList* list);

int DLL_IsActive(DLList* list);

#endif