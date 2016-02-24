#ifndef _CLIENTFORM_H_
#define _CLIENTFORM_H_

#include "../Control/Control.h"

/**********************************************客户端用户管理**********************************************/


class ClientForm:public Form//客户端用户管理界面
{
public:
	ClientForm(int height,int width,int starty,int startx,int contype);
	static Table *pTable1;
};



class ClientUserAdd:public Form// 客户端用户增加
{
public:
	ClientUserAdd(int height,int width,int starty,int startx,int contype);
	~ClientUserAdd();
	TableItem *pData;
	char *passwd;
};



class ClientUserUpdata:public Form// 客户端用户修改
{
public:
	ClientUserUpdata(int height,int width,int starty,int startx,int contype);
	~ClientUserUpdata();
	TableItem *pData;
	char *passwd;
};



class ClientUserRemove:public Form// 客户端用户假删除
{
public:
	ClientUserRemove(int height,int width,int starty,int startx,int contype);

};


#endif

