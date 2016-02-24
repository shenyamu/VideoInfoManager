#ifndef _MENUACTION_H_
#define _MENUACTION_H_

#include "../Control/Control.h"

class ActionLogout:public ActionListen
{
public:
	ActionLogout(Form *pWin);
	void DoAction(int &key);
};

class ActionSystem:public ActionListen
{
public:
	ActionSystem(Form *pWin);
	void DoAction(int &key);
};

class ActionClient:public ActionListen
{
public:
	ActionClient(Form *pWin);
	void DoAction(int &key);
};


class ActionVideo:public ActionListen
{
public:
	ActionVideo(Form *pWin);
	void DoAction(int &key);
};


class ActionTable:public ActionListen
{
public:
	ActionTable(Form *pWin);
	void DoAction(int &key);
};


#endif