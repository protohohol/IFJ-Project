#include "code_generator.h"
#include "instruction_list.h"

void codeStart(DLList* list) {
	printf(".IFJcode22\n\
	DEFVAR GF@tmp1\n\
	DEFVAR GF@tmp2\n\
	DEFVAR GF@tmp3\n\
	JUMP $$main\n\
	\n\
	LABEL $readi\n\
		PUSHFRAME\n\
		DEFVAR LF@VAR\n\
		READ LF@VAR int\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL $readf\n\
		PUSHFRAME\n\
		DEFVAR LF@VAR\n\
		READ LF@VAR float\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL $reads\n\
		PUSHFRAME\n\
		DEFVAR LF@VAR\n\
		READ LF@VAR string\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL $floatval\n\
		PUSHFRAME\n\
		DEFVAR LF@$floatval$return\n\
		MOVE LF@$floatval$return LF@%0\n\
		TYPE GF@tmp1 LF@%0\n\
		JUMPIFEQ $floatval$type$int GF@tmp1 string@int\n\
		JUMPIFEQ $floatval$type$nil GF@tmp1 string@nil\n\
		JUMP $floatval$end\n\
		LABEL $floatval$type$int\n\
		INT2FLOAT LF@$floatval$return LF@%0\n\
		JUMP $floatval$end\n\
		LABEL $floatval$type$nil\n\
		INT2FLOAT LF@$floatval$return int@0\n\
		LABEL $floatval$end\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL $intval\n\
		PUSHFRAME\n\
		DEFVAR LF@$intval$return\n\
		MOVE LF@$intval$return LF@%0\n\
		TYPE GF@tmp1 LF@%0\n\
		JUMPIFEQ $intval$type$float GF@tmp1 string@float\n\
		JUMPIFEQ $intval$type$nil GF@tmp1 string@nil\n\
		JUMP $intval$end\n\
		LABEL $intval$type$float\n\
		FLOAT2INT LF@$intval$return LF@%0\n\
		JUMP $intval$end\n\
		LABEL $intval$type$nil\n\
		MOVE LF@$intval$return int@0\n\
		LABEL $intval$end\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL $strval\n\
		PUSHFRAME\n\
		DEFVAR LF@$strval$return\n\
		MOVE LF@$strval$return LF@%0\n\
		TYPE GF@tmp1 LF@%0\n\
		JUMPIFEQ $strval$type$nil GF@tmp1 string@nil\n\
		JUMP $strval$end\n\
		LABEL $strval$type$nil\n\
		MOVE LF@$strval$return string@ \n\
		LABEL $strval$end\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL $strlen\n\
		PUSHFRAME\n\
		DEFVAR LF@$strlen$return\n\
		STRLEN LF@$strlen$return LF@%0\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL $substring\n\
		PUSHFRAME\n\
		DEFVAR LF@$substring$return\n\
		MOVE LF@$substring$return string@ \n\
		DEFVAR LF@$substring$control\n\
		LT LF@$substring$control LF@%1 int@0\n\
		JUMPIFEQ $substring$end LF@$substring$control bool@true\n\
		LT LF@$substring$control LF@%2 int@0\n\
		JUMPIFEQ $substring$end LF@$substring$control bool@true\n\
		GT LF@$substring$control LF@%1 LF@%2\n\
		JUMPIFEQ $substring$end LF@$substring$control bool@true\n\
		DEFVAR LF@$substring$len\n\
		STRLEN LF@$substring$len LF@%0\n\
		GT LF@$substring$control LF@%1 LF@$substring$len\n\
		JUMPIFEQ $substring$end LF@$substring$control bool@true\n\
		GT LF@$substring$control LF@%2 LF@$substring$len\n\
		JUMPIFEQ $substring$end LF@$substring$control bool@true\n\
		DEFVAR LF@$substring$char\n\
		LABEL $substring$loop\n\
		GETCHAR LF@$substring$char LF@%0 LF@%1\n\
		CONCAT LF@$substring$return LF@$substring$char\n\
		LT LF@$substring$control LF@%1 LF@%2\n\
		JUMPIFEQ $substring$loop LF@$substring$control bool@true\n\
		LABEL $substring$end\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABEL $ord\n\
		PUSHFRAME\n\
		DEFVAR LF@$ord$return\n\
		MOVE LF@$ord$return int@0\n\
		DEFVAR LF@$ord$len\n\
		STRLEN LF@$ord$len LF%0\n\
		JUMPIFEQ $ord$end LF@$ord$len int@0\n\
		STRI2INT LF@$ord$return LF%0 int@0\n\
		LABLE $ord$end\n\
		POPFRAME\n\
		RETURN\n\
	\n\
	LABLE $chr\n\
		PUSHFRAME\n\
		DEFVAR LF@$chr$return\n\
		INT2CHAR LF@$chr$return LF@%0\n\
		POPFRAME\n\
		RETURN\n\
	");
}

void printInstruction(DLList* list) {
	DLL_First(list);
	while(DLL_IsActive(list)) {
		switch (list->activeElement->data.operator){
			
		}
	}
}