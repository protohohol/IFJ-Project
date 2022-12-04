#include "instruction_list.h"

void DLL_Init( DLList *list ) {
	list->firstElement = NULL;
	list->activeElement = NULL;
	list->lastElement = NULL;
}

void DLL_Dispose( DLList *list ) {
	if(list->firstElement != NULL) { 
		DLLElementPtr tmpElement = list->firstElement;
		while(tmpElement->nextElement != NULL) { 
			DLLElementPtr tmpElementNext = tmpElement->nextElement;
			free(tmpElement);
			tmpElement = tmpElementNext;
		}
		list->firstElement = NULL;
		list->activeElement = NULL;
		list->lastElement = NULL;
	}
}


void DLL_InsertFirst( DLList *list, taCode data ) {
	DLLElementPtr newElement  = (DLLElementPtr)malloc(sizeof(struct DLLElement)); 
	if(newElement == NULL){
		return;
    }
	if(list->firstElement == NULL && list->lastElement == NULL){ 
		newElement->data = data;
		newElement->nextElement = NULL;
		newElement->previousElement = NULL;
		list->firstElement = newElement;
		list->lastElement = newElement;
	}
	else { 
		newElement->data = data;
		list->firstElement->previousElement = newElement;
		newElement->nextElement = list->firstElement;
		newElement->previousElement = NULL;
		list->firstElement = newElement;
	}
}


void DLL_InsertLast( DLList *list, taCode data ) {
	DLLElementPtr newElement  = (DLLElementPtr)malloc(sizeof(struct DLLElement)); 
	if(newElement == NULL){
		return;
    }
	if(list->firstElement == NULL && list->lastElement == NULL){
		newElement->data = data;
		newElement->nextElement = NULL;
		newElement->previousElement = NULL;
		list->lastElement = newElement;
		list->firstElement = newElement;
	}
	else { 
		list->lastElement->nextElement = newElement;
		newElement->data = data;
		newElement->nextElement = NULL;
		newElement->previousElement = list->lastElement;
		list->lastElement = newElement;
	}
}


void DLL_First( DLList *list ) {
	list->activeElement = list->firstElement;
}


void DLL_Last( DLList *list ) {
	list->activeElement = list->lastElement;
}


void DLL_GetFirst( DLList *list, taCode *dataPtr ) {
	if(list->firstElement == NULL){
		return;
	}
	else{
		*dataPtr = list->firstElement->data;
	}
}

void DLL_GetLast( DLList *list, taCode *dataPtr ) {
	if(list->firstElement == NULL){
		return;
	}
	else{
		*dataPtr = list->lastElement->data;
	}
}

void DLL_DeleteFirst( DLList *list ) {
	if(list->firstElement != NULL)
	{
		DLLElementPtr tmpElement = list->firstElement;
		if(list->activeElement = list->firstElement) 
			list->activeElement = NULL;
		if(tmpElement->nextElement == NULL){
			list->firstElement = NULL;
			list->lastElement = NULL;
		}
		else{
			list->firstElement = tmpElement->nextElement;
			list->firstElement->previousElement = NULL; 
		}
		free(tmpElement);
	}
}

void DLL_DeleteLast( DLList *list ) {
	if(list->firstElement != NULL)
	{
		DLLElementPtr tmpElement = list->lastElement;
		if(list->activeElement = list->lastElement)
			list->activeElement = NULL;
		if(tmpElement->previousElement == NULL){
			list->firstElement = NULL;
			list->lastElement = NULL;
		}
		else{
			list->lastElement = tmpElement->previousElement;
			list->lastElement->nextElement = NULL;
		}
		free(tmpElement);
	}
}

void DLL_DeleteAfter( DLList *list ) {
	if(list->activeElement != NULL && list->activeElement != list->lastElement)
	{
		DLLElementPtr tmpElement = list->activeElement->nextElement;
		if(tmpElement->nextElement != NULL){
			list->activeElement->nextElement = tmpElement->nextElement;
			list->activeElement->nextElement->previousElement = list->activeElement;
		}
		else{
			list->activeElement->nextElement = NULL;
			list->lastElement = list->activeElement;
		}
		
		free(tmpElement);
	}
}

void DLL_DeleteBefore( DLList *list ) {
	if(list->activeElement != NULL && list->activeElement != list->firstElement)
	{
		DLLElementPtr tmpElement = list->activeElement->previousElement;
		if(tmpElement->previousElement != NULL){
			list->activeElement->previousElement = tmpElement->previousElement;
			list->activeElement->previousElement->nextElement = list->activeElement;
		}
		else{
			list->activeElement->previousElement = NULL;
			list->firstElement = list->activeElement;
		}
		
		free(tmpElement);
	}
}

void DLL_InsertAfter( DLList *list, taCode data ) {
	if(list->activeElement != NULL){
		DLLElementPtr newElement  = (DLLElementPtr)malloc(sizeof(struct DLLElement));
		if(newElement == NULL)
			return;
		else{
			if(list->activeElement->nextElement != NULL){
				newElement->nextElement = list->activeElement->nextElement;
				newElement->nextElement->previousElement = newElement;
			}
			else{
				newElement->nextElement = NULL;
				list->lastElement = newElement;
			}
			newElement->data = data;
			newElement->previousElement = list->activeElement;
			list->activeElement->nextElement = newElement;
		}
	}
}

void DLL_InsertBefore( DLList *list, taCode data ) {
	if(list->activeElement != NULL){
		DLLElementPtr newElement  = (DLLElementPtr)malloc(sizeof(struct DLLElement));
		if(newElement == NULL)
			return;
		else{
			if(list->activeElement->previousElement != NULL){
				newElement->previousElement = list->activeElement->previousElement;
				newElement->previousElement->nextElement = newElement;
			}
			else{
				newElement->previousElement = NULL;
				list->firstElement = newElement;
			}
			newElement->data = data;
			newElement->nextElement = list->activeElement;
			list->activeElement->previousElement = newElement;
		}
	}
}

void DLL_GetValue( DLList *list, taCode *dataPtr ) {
	if(list->activeElement == NULL)
		return;
	else
		*dataPtr = list->activeElement->data;
}

void DLL_SetValue( DLList *list, taCode data ) {
	if(list->activeElement != NULL){
		list->activeElement->data = data;
	}
}

void DLL_Next( DLList *list ) {
	if(list->activeElement != NULL){
		list->activeElement = list->activeElement->nextElement;
	}
}

void DLL_Previous( DLList *list ) {
	if(list->activeElement != NULL){
		list->activeElement = list->activeElement->previousElement;
	}
}

int DLL_IsActive( DLList *list ) {
	return (list->activeElement != NULL);
}