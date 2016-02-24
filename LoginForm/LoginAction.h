#ifndef _LOGINACTION_H_
#define _LOGINACTION_H_

#include <stdlib.h>
#include <string.h>
#include "../Control/Control.h"

class ActionEnter:public ActionListen
{
public:
    ActionEnter(Form *pWin);
    void DoAction(int &key);
};

class ActionCancel:public ActionListen
{
public:
    ActionCancel(Form *pWin);
    void DoAction(int &key);
};


#endif
