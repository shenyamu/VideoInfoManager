#ifndef _MAINFORM_H_
#define _MAINFORM_H_

#include "../Control/Control.h"
#include "../List/List.h"


class MenuForm:public Form // 菜单界面
{
public:
	MenuForm(int height,int width,int starty,int startx,int contype,char *role);
	void show();
	void KeyListen(int &key);	
	int menu_sid;// 二级菜单编号
	static MenuForm *pForm;// 菜单界面this指针
};

class MenuBar:public Control // 菜单栏（一级菜单）
{
public:
	MenuBar(WINDOW *pFather,int height,int width,int starty,int startx,char *colvalu,char *data,int contype);
	~MenuBar();
	void show();
	void GetFocus();
	void AddAction(char *menu_fid);
	pList psecond;// 二级菜单链表头
	ActionListen *pAction;//属于主菜单的二级菜单事件

};



class MenuItem:public Control// 菜单项（二级菜单）
{
public:
	MenuItem(WINDOW *pFather,int height,int width,int starty,int startx,char *data,int contype);
	~MenuItem();
	void show();
	void GetFocus();
	int menu_sid;
    
};


#endif

