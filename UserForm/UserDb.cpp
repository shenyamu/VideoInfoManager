#include "../UserForm/UserDb.h"
#include "../UserForm/UserForm.h"
#include "../DbCon/DbCon.h"



int Search_CallBack(void *pData,int cols,char **colvalu,char **colname)
{
	pList head;// 存放记录的链表
	char sql[256] = "";
	char role[20] = "";// 角色ID
	TableItem *pTable;	
	static int c;
 	if (pData == NULL)
 	{
 		UserForm::pTable->sum = (UserForm::pTable->sum) +1;
		return 0;
 	}
 	else
	{

		head = (pList)pData;
		if (head->pNext == NULL)
		{
			c = 0;
		}
		sprintf(sql,"select role_id from Tbl_user_role where user_id = %s",colvalu[0]);
		(DbSingles::GetSingle())->GetData(sql,Get_CallBack,role);//获取角色ID
		pTable = new TableItem(UserForm::pTable->GetHandle(),1,(4*COLS)/5-1,c,0,4,colvalu[0],colvalu[1],colvalu[3],colvalu[5],role,(char*)"");
		List_add(head,pTable);
		c=c+1;
		return 0;
	}
}


static int c;
int Power_CallBack(void *pData,int cols,char **colvalu,char **colname)
{
	pList head = (pList)pData;
	Control *pCom;
	if (head->pNext == NULL)
	{
		c = 2;
	}
	pCom = new Power(UserPower::pWindow,1,15,11,c,colvalu[1],colvalu[0],1);
	List_add(head,pCom);
	c = c + 18;
	return 0;
}



int PowerItem_CallBack(void *pData,int cols,char **colvalu,char **colname)
{
	static int line;
	pList head = (pList)pData;
	Control *pCom;
	if (head->pNext == NULL)
	{
		line = 12;
	}
	pCom = new Power(UserPower::pWindow,1,15,line,c+2,colvalu[0],NULL,1);
	List_add(head,pCom);
	line = line + 1;
	return 0;
}