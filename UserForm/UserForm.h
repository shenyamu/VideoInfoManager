#ifndef _USERFORM_H_
#define _USERFORM_H_

#include "../UserForm/UserAction.h"


class UserForm:public Form//用户管理界面
{
public:
	UserForm(int height,int width,int starty,int startx,int contype);
	static Table *pTable;
};



class UserUpdata:public Form// 用户修改
{
public:
	UserUpdata(int height,int width,int starty,int startx,int contype);
	~UserUpdata();
	TableItem *pData;
	char *passwd;
};




class UserAdd:public Form// 用户增加
{
public:
	UserAdd(int height,int width,int starty,int startx,int contype);
	~UserAdd();
	TableItem *pData;
	char *passwd;
};



class UserRemove:public Form// 用户删除
{
public:
	UserRemove(int height,int width,int starty,int startx,int contype);
};




class UserPower:public Form //用户权限
{
public:
	UserPower(int height,int width,int starty,int startx,int contype);
	void show();	//重定义show
	char *role_id;	// 下来框选中的的角色ID
	static UserPower *pPower;
	static WINDOW *pWindow;	// 用户权限更改界面的窗口指针
protected:
	pList pMenu;			// 当前用户拥有的主菜单链表
};



class Power:public Control// 权限条目派生类
{
public:
	Power(WINDOW *pFather,int height,int width,int starty,int startx,char *data,char *fid,int contype);
	~Power();
	void show();
	void ShowList();
protected:
	pList pNode;// 一个主菜单拥有的子菜单链表
};




#endif