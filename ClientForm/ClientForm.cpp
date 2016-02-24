#include <string.h>
#include <malloc.h>
#include "../ClientForm/ClientForm.h"
#include "../ClientForm/ClientAction.h"
#include "../ClientForm/ClientDb.h"



Table *ClientForm::pTable1 = NULL;
ClientForm::ClientForm(int height,int width,int starty,int startx,int contype)
						:Form(height,width,starty,startx,contype)
{
	Control *pCom;
	ActionListen *pAction;
	mvwhline(this->pCon,5,0,0,(4*COLS)/5);
	mvwvline(this->pCon,0,(4*COLS)/5,0,LINES+1);
	mvwhline(this->pCon,7,0,0,(4*COLS)/5);
	mvwhline(this->pCon,LINES-5,0,0,(4*COLS)/5);
	// 画出三条横线和一条竖线
	pCom = new Table(this->pCon,10,(4*COLS)/5-1,8,1,4);
	((Table *)pCom)->flag = 8;
	ClientForm::pTable1 = (Table *)pCom;
	ClientForm::pTable1->tabtype = 2;
	List_add(pfirst,pCom);
	// 为用户管理界面建一个表控件，用来显示查询得到的记录
	pCom = new Label(this->pCon,3,8,1,1,(char *)"用户名",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,14,1,9,10,1,2,true);
	ClientForm::pTable1->user_name = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,1,24,(char *)"帐号",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,14,1,31,10,1,2,true);
	ClientForm::pTable1->user_account = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,1,50,(char *)" 查询 ",3);
 	pAction = new ActionClientSearch(this);
 	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,3,(4*COLS)/5+3,(char *)" 增加 ",3);
	pAction = new ActionClientAdd(this);
 	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,8,(4*COLS)/5+3,(char *)" 修改 ",3);
 	pAction = new ActionClientUpdata(this);
 	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,13,(4*COLS)/5+3,(char *)" 删除 ",3);
 	pAction = new ActionClientRemove(this);
 	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);  
	pCom = new Button(this->pCon,3,8,18,(4*COLS)/5+3,(char *)" 返回 ",3);
 	pAction = new ActionReturn(this);
 	((Button *)pCom)->AddAction(pAction);// 添加返回按钮事件
	List_add(pfirst,pCom);   
	pCom = new Label(this->pCon,3,8,5,0,(char *)"序号",1);
	List_add(pfirst,pCom);   
	pCom = new Label(this->pCon,3,8,5,12,(char *)"用户名",1);
	List_add(pfirst,pCom); 
	pCom = new Label(this->pCon,3,8,5,26,(char *)"帐号",1);
	List_add(pfirst,pCom);   
	pCom = new Label(this->pCon,3,12,5,39,(char *)"最后登录时间",1);
	List_add(pfirst,pCom);  
	pCom = new Label(this->pCon,3,8,5,54,(char *)"备注",1);
	List_add(pfirst,pCom);  
	pCom = new Label(this->pCon,1,60,LINES-2,1,(char *)"选择:Up/Down  翻页:PageUp/PageDown  确认:Enter  重选记录:Esc",1);
	List_add(pfirst,pCom); 
	mvwvline(this->pCon,6,9,0,1);
	mvwvline(this->pCon,6,23,0,1);
	mvwvline(this->pCon,6,36,0,1);
	mvwvline(this->pCon,6,53,0,1);
	
}

 

ClientUserAdd::ClientUserAdd(int height,int width,int starty,int startx,int contype)
					:Form(height,width,starty,startx,contype)
{
	this->pData = (TableItem *)malloc(sizeof(class TableItem));
	memset(pData,0,sizeof(class TableItem));
	Control *pCom;
	ActionListen *pAction;	
	
	pCom = new Label(this->pCon,1,21,0,20,(char *)"  用户增加  ",1);
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,2,2,(char *)"用 户 名",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,2,11,10,1,2,true);
	pData->user_name = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,5,2,(char *)"密    码",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,5,11,8,2,2);
	passwd = pCom->Getdata();
    List_add(pfirst,pCom);	
	pCom = new Label(this->pCon,3,8,8,2,(char *)"确认密码",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,8,11,8,2,2);
	pData->user_pwd = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,2,30,(char *)"帐    号",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,2,39,10,1,2,true);
	pData->user_account = pCom->Getdata();
    List_add(pfirst,pCom);	

	pCom = new Label(this->pCon,3,8,5,30,(char *)"备    注",1);
	List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,5,39,10,1,2,true);
	pData->user_remark = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,14,18,(char *)" 增加 ",3);
	pAction = new ActionAddEnter(this);
	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,14,35,(char *)" 取消 ",3);
	pAction = new ActionReturn(this);
	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Label(this->pCon,1,50,11,6,(char *)"要求:用户名不可为空，两次密码需一致，密码不为空",1);
	List_add(pfirst,pCom);
	pCom = new Label(this->pCon,1,50,12,5,(char *)"密码最长8位，其他最长10位",1);
	List_add(pfirst,pCom);
	
}

ClientUserAdd::~ClientUserAdd()
{
	free(pData);
}

ClientUserUpdata::ClientUserUpdata(int height,int width,int starty,int startx,int contype)
									:Form(height,width,starty,startx,contype)
{
	this->pData = (TableItem *)malloc(sizeof(class TableItem));
	memset(pData,0,sizeof(class TableItem));
	Control *pCom;
	ActionListen *pAction;
	
	pCom = new Label(this->pCon,1,21,0,20,(char *)"  用户修改  ",1);
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,2,2,(char *)"用 户 名",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,2,11,10,1,2,true);
	strcpy(pCom->Getdata(),ClientForm::pTable1->pNode->user_name);
	pData->user_name = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,5,2,(char *)"密    码",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,5,11,8,2,2);
	passwd = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,8,2,(char *)"确认密码",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,8,11,8,2,2);
	pData->user_pwd = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,2,30,(char *)"帐    号",1);
    List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,2,39,10,1,2,true);
	strcpy(pCom->Getdata(),ClientForm::pTable1->pNode->user_account);
	pData->user_account = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Label(this->pCon,3,8,5,30,(char *)"备    注",1);
	List_add(pfirst,pCom);
	pCom = new Edit(this->pCon,3,15,5,39,10,1,2,true);
	strcpy(pCom->Getdata(),ClientForm::pTable1->pNode->user_remark);
	pData->user_remark = pCom->Getdata();
    List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,14,18,(char *)" 修改 ",3);
 	pAction = new ActionUpdataEnter(this);
 	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,14,35,(char *)" 取消 ",3);
	pAction = new ActionReturn(this);
	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Label(this->pCon,1,50,11,6,(char *)"要求:用户名不可为空，两次密码需一致，密码不为空",1);
	List_add(pfirst,pCom);
	pCom = new Label(this->pCon,1,40,12,5,(char *)"密码最长8位，其他最长10位",1);
	List_add(pfirst,pCom);

}


ClientUserUpdata::~ClientUserUpdata()
{
	free(pData);
}



ClientUserRemove::ClientUserRemove(int height,int width,int starty,int startx,int contype)
							:Form(height,width,starty,startx,contype)
{	
	Control *pCom;
	ActionListen *pAction;
	
	pCom = new Label(this->pCon,3,12,1,8,(char *)"确认删除?",1);
    List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,5,3,(char *)" 确定 ",3);
	pAction = new ActionRemoveEnter(this);
    ((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
	pCom = new Button(this->pCon,3,8,5,18,(char *)" 取消 ",3);
	pAction = new ActionReturn(this);
	((Button *)pCom)->AddAction(pAction);
	List_add(pfirst,pCom);
}
