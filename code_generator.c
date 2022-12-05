#include "code_generator.h"
#include "instruction_list.h"

void codeStart(DLList* list) {
	printf(".IFJcode22\n\
	DEFVAR GF@tmp1\n\
	DEFVAR GF@tmp2\n\
	DEFVAR GF@tmp3\n\
	JUMP main\n\
	\n\
	LABEL readi\n\
		PUSHFRAME\n\
		DEFVAR LF@VAR\n\
		READ LF@VAR int\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL readf\n\
		PUSHFRAME\n\
		DEFVAR LF@VAR\n\
		READ LF@VAR float\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL reads\n\
		PUSHFRAME\n\
		DEFVAR LF@VAR\n\
		READ LF@VAR string\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL write\n\
		LABLE write$loop\n\
		POPS GF@tmp1\n\
		JUMPIFEQ write$end GF@tmp1 nil@nil\n\
		WRITE GF@tmp1\n\
		JUMP write$loop\n\
		LABLE write$end\n\
	\n\
	LABEL floatval\n\
		POPS GF@tmp1\n\
		DEFVAR LF@varType\n\
		DEFVAR LF@return\n\
		TYPE LF@varType GF@tmp1\n\
		JUMPIFEQ floatval$nil LF@varType string@nil\n\
		JUMPIFEQ floatval$int LF@varType string@int\n\
		JUMPIFEQ floatval$float LF@varType string@float\n\
		JUMP floatval$end\n\
		\n\
		LABEL floatval$nil\n\
	");
}

void printInstruction(DLList* list) {
	DLL_First(list);
	while(DLL_IsActive(list)) {
		switch (list->activeElement->data.operator){
			
		}
	}
}