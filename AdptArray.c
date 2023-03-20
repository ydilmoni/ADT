#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC PrintFunc;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_,PRINT_FUNC PrintFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if ((pArr == NULL)||(copyFunc_==NULL)||(delFunc_==NULL)||(PrintFunc_==NULL)){
		return NULL;
	}
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->PrintFunc = PrintFunc_;
	return pArr;
}

int GetAdptArraySize(PAdptArray pArr){
	if (pArr == NULL)
		return -1;
	
	return pArr->ArrSize;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if ((pArr == NULL)||(idx<0)){
		return FAIL;
	}
		
	if (idx >= pArr->ArrSize)//The index given by the user is greater than the length of the array
	// so I need to copy the array to memory large enough to make this reference valid
	{	
// Extend Array
		newpElemArr = (PElement*)calloc((idx+1), sizeof(PElement));
		if(newpElemArr == NULL){
			return FAIL;
		}
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem if need to...
	if ((pArr->pElemArr)[idx]!=NULL)
	{
		pArr->delFunc((pArr->pElemArr)[idx]);
	}
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size if need to...
	if (idx >=pArr->ArrSize)
		pArr->ArrSize = idx+1;

	return SUCCESS;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if ((pArr->pElemArr)[i]!=NULL){
			pArr->delFunc((pArr->pElemArr)[i]);
		}
		
	}
	free(pArr->pElemArr);
	free(pArr);
}
void PrintDB(PAdptArray pArr){
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if((pArr->pElemArr)[i]!=NULL){
			pArr->PrintFunc((pArr->pElemArr)[i]);
		}
	}
}
PElement GetAdptArrayAt(PAdptArray pArr, int i){
	if (pArr == NULL){
		return NULL;
	}
	if (i>pArr->ArrSize){
		return NULL;
	}
	if (pArr->pElemArr[i]==NULL)
	{
		return NULL;
	}
	
	PElement copiedElm = pArr->copyFunc(pArr->pElemArr[i]);
	return copiedElm;
}


	
	
