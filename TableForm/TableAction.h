#include "../Control/Control.h"
#include "../UserForm/UserAction.h"


class TableAction:public ActionListen
{
public:
	TableAction(Form *pWin);
	void DoAction(int &key);
};