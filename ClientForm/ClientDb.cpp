#include "../ClientForm/ClientDb.h"
#include "../List/List.h"
#include "../Control/Control.h"
#include "../ClientForm/ClientForm.h"

int Client_CallBack(void *pData,int cols,char **colvalu,char **colname)
{
	
	pList head;
	TableItem *pTable;	
	static int c;
	if (pData == NULL)
	{
		ClientForm::pTable1->sum = (ClientForm::pTable1->sum) +1;
		return 0;
	}
	else
	{	
		head = (pList)pData;
		if (head->pNext == NULL)
		{
			c = 0;
		}
		pTable = new TableItem(ClientForm::pTable1->GetHandle(),1,(4*COLS)/5-1,c,0,4,colvalu[0],colvalu[1],colvalu[3],colvalu[6],(char*)"",colvalu[5]);
		List_add(head,pTable);
		c=c+1;
		return 0;
	}
}
