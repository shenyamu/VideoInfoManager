#include <stdlib.h>
#include <string.h>
#include "../DbCon/DbCon.h"



DbSingles * DbSingles::pS = NULL;

DbSingles *DbSingles::GetSingle()
{
	if (pS == NULL)
	{
		pS = new DbSingles;
		
	}
	return pS;
}

DbSingles::DbSingles()
{
	int errcode;
	errcode = sqlite3_open("MyDB/mydb.dat",&db);
	if (errcode != SQLITE_OK)
	{
		printf("打开数据库失败:%s\n",sqlite3_errmsg(db));
		exit(1);// 非正常退出
	}
}


DbSingles::~DbSingles()
{
	sqlite3_close(db);
	printf("已断开数据库的连接。\n");
}


int DbSingles::GetData(char *sql,sqlite3_callback pFun,void *pData)
{
	char *errmsg;
	return  sqlite3_exec(db,sql,pFun,pData,&errmsg);
}



void ReleaseDb()
{
	delete DbSingles::pS;
}


int Get_CallBack(void *pData,int cols,char **colvalu,char **colname)
{
	char *data = (char *)pData;
	strcpy(data,colvalu[0]);
	return 0;
	
}