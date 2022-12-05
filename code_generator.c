#include "code_generator.h"
#include "instruction_list.h"

void codeStart(DLList* list) {
	printf(".IFJcode22\n\
	JUMP main\n\
	");
	//todo: standart functions
}

void printInstruction(DLList* list) {
	DLL_First(list);
	while(DLL_IsActive(list)) {
		switch (list->activeElement->data.operator){
			
		}
	}
}