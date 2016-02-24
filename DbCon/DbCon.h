#ifndef _SINGLES_H_
#define _SINGLES_H_

#include <stdio.h>
#include <sqlite3.h>

class DbSingles
{
public:
	static DbSingles *GetSingle();// 获取单例的指针
    int GetData(char *sql,sqlite3_callback pFun,void *pData);// 执行sql语句	
private:
	DbSingles();
	~DbSingles();
	static DbSingles *pS;
    sqlite3 *db;
	friend void ReleaseDb();   
	
};

void ReleaseDb();// 释放单例，关闭数据库

int Get_CallBack(void *pData,int cols,char **colvalu,char **colname);

#endif