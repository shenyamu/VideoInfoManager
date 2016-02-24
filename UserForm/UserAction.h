#ifndef _USERACTION_H_
#define _USERACTION_H_

#include "../Control/Control.h"
#include "../UserForm/UserDb.h"

class ActionSearch:public ActionListen
{
public:
	ActionSearch(Form *pWin);
	void DoAction(int &key);
};


class ActionRemove:public ActionListen
{
public:
	ActionRemove(Form *pWin);
	void DoAction(int &key);
};

class RemoveEnter:public ActionListen
{
public:
	RemoveEnter(Form *pWin);
	void DoAction(int &key);
};

class ActionUpdata:public ActionListen
{
public:
	ActionUpdata(Form *pWin);
	void DoAction(int &key);
};

class UpdataEnter:public ActionListen
{
public:
	UpdataEnter(Form *pWin);
	void DoAction(int &key);
};


class ActionAdd:public ActionListen
{
public:
	ActionAdd(Form *pWin);
	void DoAction(int &key);
};


class AddEnter:public ActionListen
{
public:
	AddEnter(Form *pWin);
	void DoAction(int &key);
};


class ActionPower:public ActionListen
{
public:
	ActionPower(Form *pWin);
	void DoAction(int &key);
};


class PowerEnter:public ActionListen
{
public:
	PowerEnter(Form *pWin);
	void DoAction(int &key);
};


class ActionReturn:public ActionListen
{
public:
	ActionReturn(Form *pWin);
	void DoAction(int &key);
};



#endif
