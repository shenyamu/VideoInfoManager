#include <string.h>
#include "../DbCon/DbCon.h"
#include "../TableForm/TableDb.h"
#include "../TableForm/TableForm.h"

int Census_CallBack(void *pData,int cols,char **colvalu,char **colname)// 表格统计回调函数
{
	pList head;
	TableItem *pTable;
	char sql[512] = "";
	static int c;
	int c1;
	char ID[10];
	char video_name[20];
	char video_channel[10];
	char video_area[10];
	char video_type[10];
	if (pData == NULL)
	{
		TableForm::pTable->sum = (TableForm::pTable->sum) +1;
		return 0;
	}
	else
	{	
		head = (pList)pData;
		if (head->pNext == NULL)
		{
			c = 0;
		}
		c1 = c+1;
		sprintf(ID,"%d",c1);
		sprintf(sql,"select video_name from Tbl_video_message where video_id = %s",colvalu[0]);
		(DbSingles::GetSingle())->GetData(sql,Get_CallBack,video_name);
		sprintf(sql,"select channel_name from Tbl_video_channel where channel_id =(select channel_id from Tbl_video_message where video_id = %s)",colvalu[0]);
		(DbSingles::GetSingle())->GetData(sql,Get_CallBack,video_channel);
		sprintf(sql,"select area_name from Tbl_video_area where area_id =(select area_id from Tbl_video_message where video_id = %s)",colvalu[0]);
		(DbSingles::GetSingle())->GetData(sql,Get_CallBack,video_area);
		sprintf(sql,"select type_name from Tbl_video_type where type_id =(select type_id from Tbl_video_message where video_id = %s)",colvalu[0]);
		(DbSingles::GetSingle())->GetData(sql,Get_CallBack,video_type);		
		pTable = new TableItem(TableForm::pTable->GetHandle(),1,COLS-2,c,0,4,ID,video_name,colvalu[1],video_channel,video_area,video_type);
		List_add(head,pTable);
		c=c+1;
		return 0;
	}

}
