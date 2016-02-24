#ifndef _Control_H
#define _Control_H

#include <ncurses.h>
#include <sqlite3.h>
#include <iostream> //usleep头文件
#include "../List/List.h"

class ActionListen;//事件监听类的声明
class Control//组件基类
{
public:
	Control(WINDOW *pFather,int height,int width,int starty,int startx,int contype);
	virtual ~Control();
	virtual void show() = 0;//纯虚函数，多态显示不同的控件
	virtual void KeyListen(int &key);//控件键盘监听的多态
	virtual void GetFocus();//控件焦点停留的多态
	WINDOW* GetHandle();//获得控件指针
	int GetType();
	char *Getdata();
protected:
	WINDOW *pCon;//控件指针
	int height;//控件的高度
	int width;//控件的宽度
    int starty;//起始行坐标
	int startx;//起始列坐标
	char *data;//控件的内容
	int contype;// 控件的类型  1-标签、2-编辑框、3-按钮、4-表格、5-提示框、6-下拉框
    WINDOW *pFather;//父窗口指针

};



class Label:public Control//标签派生类
{
public:
	Label(WINDOW *pFather,int height,int width,int starty,int startx,char *data,int contype);
	~Label();
    void show();

};

class Notic:public Control//提示框
{
public:
	Notic(WINDOW *pFather,int height,int width,int starty,int startx,char *data,int contype);
	~Notic();
	void show();
};


class Edit:public Control//编辑框派生类
{
public:
	Edit(WINDOW *pFather,int height,int width,int starty,int startx,int len,int type,int contype,bool pwd = false);
	~Edit();
	void show();
	void KeyListen(int &key);
	void GetFocus();
private:
	int len;// 输入字符长度
	int type;// 输入字符类型
	bool pwd;// 暗文标志

};

class ComboxItem:public Control
{
public:
	ComboxItem(WINDOW *pFather,int height,int width,int starty,int startx,int contype,char *ID,char *Name);
	void show();
	void GetFocus();
	char ID[10];
	char Name[20];
};


class Combobox:public Control//下拉框
{
public:
	Combobox(WINDOW *pFather,int height,int width,int starty,int startx,int contype,char *sql);
	~Combobox();
	void show();
	void showmin();
	void GetFocus();
	void MenuClear();
	void KeyListen(int &key);
	static Combobox *pBox;
	static int Add_CallBack(void *pData,int cols,char **colvalu,char **colname);  
	char ID[10];// 下拉框内容的ID
protected:	
	pList pNode;// 下拉框的下拉菜单列表

};

class Button:public Control//按钮派生类
{
public:
	Button(WINDOW *pFather,int height,int width,int starty,int startx,char *data,int contype);
	~Button();
	void show();
	void KeyListen(int &key);
	void GetFocus();
    void AddAction(ActionListen *pAct);
private:
	WINDOW *pShadow;
	ActionListen *pAct;

};

class Form:public Control//窗口类
{
public:
    Form(int height,int width,int starty,int startx,int contype);
    ~Form();
    void show();
    void KeyListen(int &key);
	bool flag;   //退出keylisten的标志 
protected:
    pList pfirst;// 控件链表或者作为菜单界面的一级菜单链表
	WINDOW *pShadow;
	
};


class ActionListen//事件基类
{
public:
    ActionListen(Form *pWin);
    virtual void DoAction(int &key) = 0;
protected:
    Form *pWin;//窗口基类指针
};



class TableItem:public Control
{
public:
	TableItem(WINDOW *pFather,int height,int width,int starty,int startx,int contype,char *user_id,char *user_name,char *user_account,char *user_remark,char *role,char *logintime);
	~TableItem();
	void show();//系统用户表的显示函数
	void ClientShow();//客户端用户表的显示函数
	void TableShow();//报表统计的表格显示函数
	void GetFocus();
	void SelectFocus();
	char *user_id;
	char *user_name;
	char *user_pwd;
	char *user_account;
	char *user_remark;
	char *role_id;
	char *logintime;
};



class Table:public Control
{
public:
	Table(WINDOW *pFather,int height,int width,int starty,int startx,int contype);
	~Table();
	void show();
	void KeyListen(int &key);
	void UpdataTable();
	void RunSql(int flag);
	int flag;			// sql语句标志
	Control *pLable;	// 页数提示窗口
	char *user_name;	//查找条件的用户名
	char *user_account;//查找条件的账号
	int sum;			// 符合查询条件的记录条数
	TableItem *pNode;	// 表中某一条记录
	int n;				//从第几条结果开始显示在表里
	int count;			//指向记录链表的第几个结点
	int tabtype;		//表格类型 1-系统用户表、2-客户端用户表、3-报表统计表
protected:
	pList precord;		// 记录表中的记录链表
};



#endif
