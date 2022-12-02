#include "code_generator.h"
#include "instruction_list.h"


void printInstruction(DLList* list) {
	DLL_First(list);
	while(DLL_IsActive(list)) {
		switch (list->activeElement->data.operator.type){
			
		}
	}
}