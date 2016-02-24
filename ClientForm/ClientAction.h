#ifndef _CLIENTACTION_H_
#define _CLIENTACTION_H_

#include "../Control/Control.h"
#include "../UserForm/UserAction.h" //共同返回事件


class ActionClientSearch:public ActionListen
{
public:
	ActionClientSearch(Form *pWin);
	void DoAction(int &key);
};



class ActionClientAdd:public ActionListen
{
public:
	ActionClientAdd(Form *pWin);
	void DoAction(int &key);
};


class ActionAddEnter:public ActionListen
{
public:
	ActionAddEnter(Form *pWin);
	void DoAction(int &key);
};




class ActionClientUpdata:public ActionListen
{
public:
	ActionClientUpdata(Form *pWin);
	void DoAction(int &key);
};

class ActionUpdataEnter:public ActionListen
{
public:
	ActionUpdataEnter(Form *pWin);
	void DoAction(int &key);
};



class ActionClientRemove:public ActionListen
{
public:
	ActionClientRemove(Form *pWin);
	void DoAction(int &key);
};

class ActionRemoveEnter:public ActionListen
{
public:
	ActionRemoveEnter(Form *pWin);
	void DoAction(int &key);
};



#endif





