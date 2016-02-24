#include <string.h>
#include "../UserForm/UserAction.h"
#include "../UserForm/UserForm.h"
#include "../DbCon/DbCon.h"


/***********************************************************************
 返回或者取消按钮事件函数：void ActionReturn::DoAction(int &key)

*************************************************************************/
ActionReturn::ActionReturn(Form *pWin):ActionListen(pWin)
{

}


void ActionReturn::DoAction(int &key)
{
	pWin->flag = false;
}

/************************************************************************
 用户管理查询按钮事件函数：void ActionSearch::DoAction(int &key)

*************************************************************************/
ActionSearch::ActionSearch(Form *pWin):ActionListen(pWin)
{
	

}

void ActionSearch::DoAction(int &key)
{
	UserForm::pTable->KeyListen(key);	 
}


/************************************************************************
 用户管理删除按钮事件函数：void ActionRemove::DoAction(int &key)

*************************************************************************/
ActionRemove::ActionRemove(Form *pWin):ActionListen(pWin)
{
	
	
}

void ActionRemove::DoAction(int &key)
{
	Control *pRemove;
	Control *pNotic;
	if (UserForm::pTable->pNode == NULL || UserForm::pTable->sum ==0)
	{
		pNotic = new Notic(pWin->GetHandle(),5,30,9,17,(char *)"请先选定一条记录",5);
		pNotic->show();
		usleep(1000000);
		wclear(pNotic->GetHandle());
		wrefresh(pNotic->GetHandle());
		delete pNotic;
		return;
	}
	if (strcmp(UserForm::pTable->pNode->user_id,"1") == 0)
	{
		pNotic = new Notic(pWin->GetHandle(),5,30,9,17,(char *)"非法操作，此用户不可删",5);
		pNotic->show();
		usleep(1000000);
		delete pNotic;
		UserForm::pTable->show();
		UserForm::pTable->pNode->SelectFocus();
	}
	else
	{
		pRemove = new UserRemove(10,30,8,21,1);
		pRemove->show();
	    pRemove->KeyListen(key);// 是否确定删除记录的键盘监听,key返回值来判断确定与否
		if (key == 1)
		{
			pNotic = new Notic(pRemove->GetHandle(),3,18,1,6,(char *)"删除成功，请稍候",5);
			pNotic->show();
			usleep(1000000);
			delete pNotic;
			pWin->show();
			UserForm::pTable->count = UserForm::pTable->count-1;
			UserForm::pTable->sum = UserForm::pTable->sum-1;//总记录数减少一条
			if(UserForm::pTable->count == 0)
			{
				UserForm::pTable->count=1;
			}
			UserForm::pTable->UpdataTable();// 更新表中的记录
		}
		else
		{
			pWin->show();
			UserForm::pTable->show();
			UserForm::pTable->pNode->SelectFocus();
		}
			key = 10;
			delete pRemove;
	}	
    
}


/************************************************************************
 确认删除事件函数：void RemoveEnter::DoAction(int &key)

*************************************************************************/
RemoveEnter::RemoveEnter(Form *pWin):ActionListen(pWin)
{

}


void RemoveEnter::DoAction(int &key)
{
	char sql[256] = "";
	sprintf(sql,"update Tbl_user set user_stat = 0 where user_id = %s",UserForm::pTable->pNode->user_id);
	(DbSingles::GetSingle())->GetData(sql,Search_CallBack,NULL);
	key = 1;
	pWin->flag = false;
}

/************************************************************************
 用户管理修改按钮事件函数：void ActionUpdata::DoAction(int &key)

*************************************************************************/
ActionUpdata::ActionUpdata(Form *pWin):ActionListen(pWin)
{

}

void ActionUpdata::DoAction(int &key)
{
	Control *pUpdata;
	Control *pNotic;
	if (UserForm::pTable->pNode == NULL)
	{
		pNotic = new Notic(pWin->GetHandle(),5,30,9,17,(char *)"请先选定一条记录",5);
		pNotic->show();
		usleep(1000000);
		wclear(pNotic->GetHandle());
		wrefresh(pNotic->GetHandle());
		delete pNotic;
		return;
	}
	if (strcmp(UserForm::pTable->pNode->user_id,"1") == 0)
	{
		pNotic = new Notic(pWin->GetHandle(),5,30,9,17,(char *)"非法操作，此用户不可修改",5);
		pNotic->show();
		usleep(1000000);
		delete pNotic;
		UserForm::pTable->show();
		UserForm::pTable->pNode->SelectFocus();
	}
	else
	{
		pUpdata = new UserUpdata(19,61,2,4,1);
		pUpdata->show();
		pUpdata->KeyListen(key);
		if (key == 1)
		{
			pNotic = new Notic(pUpdata->GetHandle(),5,26,8,18,(char *)"修改成功，请稍候",5);
			pNotic->show();
			usleep(1000000);
			delete pNotic;
		}
		pWin->show();
	    UserForm::pTable->UpdataTable();
		key = 10;
	    delete pUpdata;
	}

}


/************************************************************************
确认修改事件函数：void UpdataEnter::DoAction(int &key)

*************************************************************************/
UpdataEnter::UpdataEnter(Form *pWin):ActionListen(pWin)
{
	
}

void UpdataEnter::DoAction(int &key)
{
	Control *pNotic;
	char sql[512] = "";
	UserUpdata *pUpdata;
	pUpdata = (UserUpdata *)pWin;
	if (strcmp(pUpdata->pData->user_pwd,pUpdata->passwd) != 0 || strcmp(pUpdata->passwd,"") == 0 || strcmp(pUpdata->pData->user_name,"") == 0)
		// 验证密码的一致性，密码不为空，用户名不为空
	{
		pNotic = new Notic(pUpdata->GetHandle(),5,26,8,18,(char *)"不符合要求，请重新输入",5);
		pNotic->show();
		usleep(1000000);
		wclear(pNotic->GetHandle());
		delete pNotic;
		memset(pUpdata->pData->user_pwd,0,sizeof(pUpdata->pData->user_pwd));
		memset(pUpdata->passwd,0,sizeof(pUpdata->pData->user_pwd));
		pUpdata->show();
		key = 0;
		return;
	}
	sprintf(sql,"update Tbl_user set user_name = \"%s\",user_pwd = \"%s\",user_account = \"%s\",user_remark = \"%s\" where user_id = %s",pUpdata->pData->user_name,pUpdata->pData->user_pwd,pUpdata->pData->user_account,pUpdata->pData->user_remark,UserForm::pTable->pNode->user_id);
	(DbSingles::GetSingle())->GetData(sql,NULL,NULL);
	sprintf(sql,"update Tbl_user_role set role_id = %s where user_id = %s",pUpdata->pData->role_id,UserForm::pTable->pNode->user_id);
	(DbSingles::GetSingle())->GetData(sql,NULL,NULL);
	key = 1;
	pWin->flag = false;
}

/************************************************************************
 用户管理增加按钮事件函数：void ActionAdd::DoAction(int &key)

*************************************************************************/
ActionAdd::ActionAdd(Form *pWin):ActionListen(pWin)
{

}


void ActionAdd::DoAction(int &key)
{
	Control *pAdd;
	Control *pNotic;
	pAdd = new UserAdd(19,61,2,4,1);
	pAdd->show();
	pAdd->KeyListen(key);
	if (key == 1)
	{
		pNotic = new Notic(pAdd->GetHandle(),5,26,8,18,(char *)"增加成功，请稍候",5);
		pNotic->show();
		usleep(1000000);
		delete pNotic;
		if (UserForm::pTable->sum != 0)
		{
			UserForm::pTable->sum = UserForm::pTable->sum + 1;
		}
	
	}
	pWin->show();
	UserForm::pTable->UpdataTable();
	key = 10;
	delete pAdd;	
}

/************************************************************************
确认增加事件函数：void AddEnter::DoAction(int &key)

*************************************************************************/
AddEnter::AddEnter(Form *pWin):ActionListen(pWin)
{

}


void AddEnter::DoAction(int &key)
{
	Control *pNotic;
	UserAdd *pAdd = (UserAdd *)pWin;
	char ID[10] = "";
	char sql[512] = "";
	int user_id;
	if (strcmp(pAdd->pData->user_pwd,pAdd->passwd) != 0 || strcmp(pAdd->passwd,"") == 0 || strcmp(pAdd->pData->user_name,"") == 0 || strcmp(pAdd->pData->role_id,"") ==0)
		// 验证密码的一致性，不可为空，角色不为空，用户名不为空
	{
		pNotic = new Notic(pAdd->GetHandle(),5,26,8,18,(char *)"不符合要求，请重新输入",5);
		pNotic->show();
		usleep(1000000);
		wclear(pNotic->GetHandle());
		delete pNotic;
		memset(pAdd->pData->user_pwd,0,sizeof(pAdd->pData->user_pwd));
		memset(pAdd->passwd,0,sizeof(pAdd->pData->user_pwd));
		pAdd->show();
		key = 0;
		return;
	}
	sprintf(sql,"select count(*) as sum from Tbl_user");
	(DbSingles::GetSingle())->GetData(sql,Get_CallBack,ID);// 获取当前有多少用户
	sscanf(ID,"%d",&user_id);
	user_id++;// 总的用户加一就是新增后的用户总数
	sprintf(sql,"insert into Tbl_user values(%d,\"%s\",\"%s\",\"%s\",1,\"%s\")",user_id,pAdd->pData->user_name,pAdd->pData->user_pwd,pAdd->pData->user_account,pAdd->pData->user_remark);
	(DbSingles::GetSingle())->GetData(sql,NULL,NULL);// 插入新增数据到用户表
	sprintf(sql,"insert into Tbl_user_role values(%d,%s)",user_id,pAdd->pData->role_id);
	(DbSingles::GetSingle())->GetData(sql,NULL,NULL);// 插入新增用户的角色号
	key = 1;
	pWin->flag = false;
}


/****************************************************************************
用户管理权限事件函数：ActionPower::ActionPower(Form *pWin):ActionListen(pWin)

******************************************************************************/
ActionPower::ActionPower(Form *pWin):ActionListen(pWin)
{
	
	
}


void ActionPower::DoAction(int &key)
{
	UserPower *pCom;
	Control *pNotic;
	if (UserForm::pTable->pNode == NULL)
	{
		pNotic = new Notic(pWin->GetHandle(),5,30,9,17,(char *)"请先选定一条记录",5);
		pNotic->show();
		usleep(1000000);
		wclear(pNotic->GetHandle());
		wrefresh(pNotic->GetHandle());
		delete pNotic;
		return;
	}
	pCom = new UserPower(19,73,2,4,1);
	pCom->show();
	pCom->KeyListen(key);// 是否确定删除记录的键盘监听,key返回值来判断确定与否
	if (key == 1)
	{
		pNotic = new Notic(pCom->GetHandle(),5,26,6,18,(char *)"修改成功，请稍候",5);
		pNotic->show();
		usleep(1500000);
		delete pNotic;
	}
	key = 10;
	pWin->show();
	UserForm::pTable->UpdataTable();// 更新表中的记录
	delete pCom;
	UserPower::pPower = NULL;
}

/****************************************************************************
 确认权限修改事件函数：PowerEnter::PowerEnter(Form *pWin):ActionListen(pWin)

******************************************************************************/
PowerEnter::PowerEnter(Form *pWin):ActionListen(pWin)
{
	
}

void PowerEnter::DoAction(int &key)
{
	char sql[256] = "";
	Notic *pNotic;
	if (strcmp(UserForm::pTable->pNode->user_id,"1") ==0)// 不可更改系统管理的权限
	{
		pNotic = new Notic(pWin->GetHandle(),5,26,6,18,(char *)"管理员权限不可修改",5);
		pNotic->show();
		usleep(1000000);
		delete pNotic;
	}
	else
	{	
		sprintf(sql,"update Tbl_user_role set role_id = %s where user_id = %s",((UserPower *)pWin)->role_id,UserForm::pTable->pNode->user_id);
		(DbSingles::GetSingle())->GetData(sql,NULL,NULL);
		key = 1;
	}
	pWin->flag = false;
}